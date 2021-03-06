#include "csapp.h"

// doit은 무엇을 하는 함수일까요? 트랜잭션 처리함수. 들어온 요청을 읽고 분석.
// GETrequest가 들어오면 정적인지 동적인지 파악하여서 각각에 맞는 함수를 실행시킴. 오류시 에러표시도 포함.

void doit(int fd);

// rio -> ROBUST I/O
void read_requesthdrs(rio_t *rp); // rio_t는 csapp.h에 정의되어있습니다 40줄쯤..

// parse_uri는 무엇을 하는 함수일까요? 폴더안에서 특정 이름을 찾아서 파일이 동적인건지 정적인건지 알려줌.
int parse_uri(char *uri, char *filename, char *cgiargs);

// serve_static은 무엇을 하는 함수일까요? 정적인 파일일때 파일을 클라이언트로 응답
void serve_static(int fd, char *filename, int filesize);

// get_filetype은 무엇을 하는 함수일까요? http,text,jpg,png,gif파일을 찾아서 serve_static에서 사용
void get_filetype(char *filename, char *filetype);

// serve_dynamic은 무엇을 하는 함수일까요? 동적인 파일을 받았을때 fork 함수로 자식프로세스를 만든후에 거기서 CGI프로그램 실행한다. s
void serve_dynamic(int fd, char *filename, char *cgiargs);

void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);

// main이 받는 변수 argc 와 argv는 무엇일까 -> 배열 길이, filename, port
// main에서 하는 일은? 무한 루프를 돌면서 대기하는 역할
int main(int argc, char **argv)
{
    int listenfd, connfd;                  // 여기서의 fd는 도대체 무슨 약자인걸까? -> file description
    char hostname[MAXLINE], port[MAXLINE]; // hostname:port -> localhost:4000
    // socklen_t 는 소켓 관련 매개 변수에 사용되는 것으로 길이 및 크기 값에 대한 정의를 내려준다
    socklen_t clientlen;                //client가 몇개나 있는가에 대한 것
    struct sockaddr_storage clientaddr; //SOCKADDR_STORAGE  구조체는 소켓 주소 정보를 저장한다.
    // SOCKADDR_STORAGE 구조체는  sockaddr 구조체가 쓰이는 곳에 사용할 수 있다.

    /* Check command-line args */
    if (argc != 2) // 프로그램 실행 시 port를 안썼으면,
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]); //다른 클라이언트가 사용중이다!!
        exit(1);
    }
    // listenfd -> 이 포트에 대한 듣기 소켓 오픈~
    listenfd = Open_listenfd(argv[1]);
    // 무한 서버루프 실행
    while (1)
    {
        clientlen = sizeof(clientaddr);
        // 연결 요청 접수
        // 연결 요청 큐에 아무것도 없을 경우 기본적으로 연결이 생길때까지 호출자를 막아둔다.
        // 소켓이 non-blocking 모드일 경우엔 에러를 띄운다.
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);

        // 트랜잭션 수행
        doit(connfd);

        // 연결 끝 닫기
        Close(connfd);
    }
}

void doit(int fd)
{
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    //buf > GET /sample2.mpeg HTTP/1.1
    //uri > /sample2.mpeg
    //filename > ./Linux.png(왜 앞에꺼가 출력되지?)
    //cgiargs > 공백

    char filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;

    // 요청 라인 읽고 분석하기...
    /* Read request line and headers */
    Rio_readinitb(&rio, fd);           //rio 구조체 초기화..
    Rio_readlineb(&rio, buf, MAXLINE); //buf에 읽은 것 담겨있음.
    printf("Request headers: \n");
    printf("%s", buf);
    sscanf(buf, "%s %s %s", method, uri, version);
    printf("buf = %s         uri = %s         filename = %s        cgiargs = %s\n", buf, uri, filename, cgiargs);


    // 메소드가 get이 아니면 에러 띄우고 끝내기
    if (strcasecmp(method, "GET"))
    {
        clienterror(fd, method, "501", "Not implemented", "Tiny does not implement this method");
        return;
    }
    // get인 경우 다른 요청 헤더 무시.
    read_requesthdrs(&rio);

    // URI 분석하기
    // 파일이 없는 경우 에러 띄우기
    /* Parse URI from GET request */
    is_static = parse_uri(uri, filename, cgiargs);
    if (stat(filename, &sbuf) < 0) // filename 값이 없으면 -1값이 반환된다.
    {
        clienterror(fd, filename, "404", "Not found", "Tiny couldn't find this file");
        return;
    }

    // 정적 컨텐츠를 요구하는 경우
    if (is_static)
    {
        // 파일이 읽기권한이 있는지 확인하기
        /* Serve static content */
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode))
        {
            clienterror(fd, filename, "403", "Forbidden", "Tiny couldn't read the file");
        }
        // 그렇다면 클라이언트에게 파일 제공
        serve_static(fd, filename, sbuf.st_size);
    }
    else
    {
        // 파일이 실행가능한 것인지
        /* Serve dynamic content */
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode))
        {
            clienterror(fd, filename, "403", "Forbidden", "Tiny couldn't run the CGI program");
            return;
        }
        //그렇다면 클라이언트에게 파일 제공.
        serve_dynamic(fd, filename, cgiargs);
    }
}

// 클라이언트에게 오류 보고하기
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg)
{
    char buf[MAXLINE], body[MAXBUF];

    /* Build the HTTP response body */
    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body, "%s<body bgcolor="
                  "ffffff"
                  ">\r\n",
            body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

    /* Print the HTTP response */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
}

// 요청헤더 읽기
void read_requesthdrs(rio_t *rp)
{
    char buf[MAXLINE];

    Rio_readlineb(rp, buf, MAXLINE); // rp 한줄 buf에 저장, 다 읽고 나면 rp는 다음 줄의 처음을 가리키는 듯.
    while (strcmp(buf, "\r\n"))      // buf가 요청 헤더의 마지막이 되면 0 반환하고 끝.
    {
        Rio_readlineb(rp, buf, MAXLINE); // 계속 한줄씩 읽고 아무것도 안한다.
        printf("%s", buf);
    }
    return;
}

int parse_uri(char *uri, char *filename, char *cgiargs)
{
    char *ptr;
    if (!strstr(uri, "cgi-bin")) /* Static content */
    {
        strcpy(cgiargs, "");   //cgiargs =""
        printf("cgiargs : %d\n", cgiargs);
        strcpy(filename, "."); //filename = "."
        printf("filename : %d\n", filename);
        strcat(filename, uri); //filename = ".uri"
        printf("filename : %d\n", filename);

        if (uri[strlen(uri) - 1] == '/') //2.2.2.2
            strcat(filename, "home.html");
        return 1;
    }
    else /* Dynamic content */
    {
        ptr = index(uri, '?');
        //CGI 인자 추출
        if (ptr)
        {
            //물음표 뒤에 인자 다 같다 붙인다.
            strcpy(cgiargs, ptr + 1);
            // 포인터는 문자열 마지막으로 바꾼다.
            *ptr = '\0';
        }
        else
            strcpy(cgiargs, "");

        // 나머지 부분 상대 URI로 바꿈, 나중에 이 서버의 uri가 뭔지 확실히 알아보자
        strcpy(filename, ".");
        strcat(filename, uri);
        return 0;
    }
}

// fd 응답받는 소켓(연결식별자), 파일 이름, 파일 사이즈
void serve_static(int fd, char *filename, int filesize)
{
    int srcfd;
    char *srcp, filetype[MAXLINE], buf[MAXBUF];
    /* Send response headers to client */
    // 파일 접미어 검사해서 파일 타입 결정
    get_filetype(filename, filetype);

    //클라이언트에게 응답 보내기     //굳이 버퍼를 쓰는 이유가 무엇일까? 한번도 출력이 되지 않는다
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    sprintf(buf, "%sConnection: close\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);

    //
    Rio_writen(fd, buf, strlen(buf));
    printf("Response header:\n");
    printf("%s", buf);
    /* Send response body to client */
    srcfd = Open(filename, O_RDONLY, 0);
    srcp = (char*) malloc(filesize);
    Rio_readn(srcfd, srcp, filesize);
    Close(srcfd);
    Rio_writen(fd, srcp, filesize);
    free(srcp);
}

/* get_filetype - Derive file type from filename */
void get_filetype(char *filename, char *filetype)
{
    if (strstr(filename, ".html"))
        strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
        strcpy(filetype, "image/gif");
    else if (strstr(filename, ".png"))
        strcpy(filetype, "image/png");
    else if (strstr(filename, ".jpg"))
        strcpy(filetype, "image/jpeg");
    else if (strstr(filename, ".mpg"))
        strcpy(filetype, "video/mpeg");
    else if (strstr(filename, ".mp4"))
        strcpy(filetype, "video/mpeg");        
    else
        strcpy(filetype, "text/plain");
}

void serve_dynamic(int fd, char *filename, char *cgiargs)
{
    char buf[MAXLINE], *emptylist[] = {NULL};
    /* Return first part of HTTP response */
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Server: Tiny Web Server\r\n");
    Rio_writen(fd, buf, strlen(buf));
    if (Fork() == 0) // Child
    /* Real server would set all CGI vars here */
    {
        setenv("QUERY_STRING", cgiargs, 1);
        Dup2(fd, STDOUT_FILENO);              /* Redirect stdout to client */
        Execve(filename, emptylist, environ); /* Run CGI program */
    }
    Wait(NULL); /* Parent waits for and reaps child */
}
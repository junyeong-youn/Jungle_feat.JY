#include "csapp.h"

// doit�� ������ �ϴ� �Լ��ϱ��? Ʈ����� ó���Լ�. ���� ��û�� �а� �м�.
// GETrequest�� ������ �������� �������� �ľ��Ͽ��� ������ �´� �Լ��� �����Ŵ. ������ ����ǥ�õ� ����.

void doit(int fd);

// rio -> ROBUST I/O
void read_requesthdrs(rio_t *rp); // rio_t�� csapp.h�� ���ǵǾ��ֽ��ϴ� 40����..

// parse_uri�� ������ �ϴ� �Լ��ϱ��? �����ȿ��� Ư�� �̸��� ã�Ƽ� ������ �����ΰ��� �����ΰ��� �˷���.
int parse_uri(char *uri, char *filename, char *cgiargs);

// serve_static�� ������ �ϴ� �Լ��ϱ��? ������ �����϶� ������ Ŭ���̾�Ʈ�� ����
void serve_static(int fd, char *filename, int filesize);

// get_filetype�� ������ �ϴ� �Լ��ϱ��? http,text,jpg,png,gif������ ã�Ƽ� serve_static���� ���
void get_filetype(char *filename, char *filetype);

// serve_dynamic�� ������ �ϴ� �Լ��ϱ��? ������ ������ �޾����� fork �Լ��� �ڽ����μ����� �����Ŀ� �ű⼭ CGI���α׷� �����Ѵ�.
void serve_dynamic(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);

// main�� �޴� ���� argc �� argv�� �����ϱ�...
// main���� �ϴ� ����? ���� ������ ���鼭 ����ϴ� ����
int main(int argc, char **argv)
{
    int listenfd, connfd;                  // ���⼭�� fd�� ����ü ���� �����ΰɱ�?
    char hostname[MAXLINE], port[MAXLINE]; // hostname:port -> localhost:4000
    // socklen_t �� ���� ���� �Ű� ������ ���Ǵ� ������ ���� �� ũ�� ���� ���� ���Ǹ� �����ش�
    socklen_t clientlen;                //client�� ��� �ִ°��� ���� ��
    struct sockaddr_storage clientaddr; //SOCKADDR_STORAGE  ����ü�� ���� �ּ� ������ �����Ѵ�.
    // SOCKADDR_STORAGE ����ü��  sockaddr ����ü�� ���̴� ���� ����� �� �ִ�.

    // argc�� �ϳ��� Ŀ�ǵ��� �� ����.
    /* Check command-line args */
    if (argc != 2) //2���� �ƴ϶�� �Ǿ��ִµ� 2���� �ǹ̸� �𸣰ڴ� 2���� �ȵǸ� 3���� �ȵɰ� ������
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }
    // listenfd -> ��� ���� ����~
    // argv�� port�� ����ִµ�~
    listenfd = Open_listenfd(argv[1]);
    // ���� �������� ����
    while (1)
    {
        clientlen = sizeof(clientaddr);
        // ���� ��û ����
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);

        // Ʈ����� ����
        doit(connfd);

        // ���� �� �ݱ�
        Close(connfd);
    }
}

void doit(int fd)
{
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];

    char filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;

    // ��û ���� �а� �м��ϱ�...
    /* Read request line and headers */
    Rio_readinitb(&rio, fd);
    Rio_readlineb(&rio, buf, MAXLINE);
    printf("Request headers: \n");
    printf("%s", buf);
    sscanf(buf, "%s %s %S", method, uri, version);

    // �޼ҵ尡 get�� �ƴϸ� ���� ���� ������
    if (strcasecmp(method, "GET"))
    {
        clienterror(fd, method, "501", "Not implemented", "Tiny does not implement this method");
        return;
    }
    // get�� ��� �ٸ� ��û ��� ����.
    read_requesthdrs(&rio);

    // URI �м��ϱ�
    // ������ ���� ��� ���� ����
    /* Parse URI from GET request */
    is_static = parse_uri(uri, filename, cgiargs);
    if (stat(filename, &sbuf) < 0)
    {
        clienterror(fd, filename, "404", "Not found", "Tiny couldn't find this file");
        return;
    }

    // ���� �������� �䱸�ϴ� ���
    if (is_static)
    {
        // ������ �б������ �ִ��� Ȯ���ϱ�
        /* Serve static content */
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode))
        {
            clienterror(fd, filename, "403", "Forbidden", "Tiny couldn't read the file")
        }
        // �׷��ٸ� Ŭ���̾�Ʈ���� ���� ����
        serve_static(fd, filename, sbuf.st_size);
    }
    else
    {
        // ������ ���డ���� ������
        /* Serve dynamic content */
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode))
        {
            clienterror(fd, filename, "403", "Forbidden", "Tiny couldn't run the CGI program") return;
        }
        //�׷��ٸ� Ŭ���̾�Ʈ���� ���� ����.
        serve_dynamic(fd, filename, cgiargs);
    }
}

// Ŭ���̾�Ʈ���� ���� �����ϱ�
void clienterror(int fd, char *cause, char *errnum, char *chortmsg, char *longmsg)
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

// ��û��� �б�
void read_requesthdrs(rio_t *rp)
{
    char buf[MAXLINE];

    // /* �� �پ� �о���δ�. */
    // ssize_t rio_readlineb(rio_t * rp, void *usrbuf, size_t maxlen)
    // {
    //     int n, rc;
    //     char c, *bufp = usrbuf;

    //     for (n = 1; n < maxlen; ++n)
    //     {
    //         if ((rc = rio_read(rp, &c, 1)) == 1)
    //         { /* rio_read()�� 1 byte�� �д´�. */
    //             *bufp++ = c;
    //             if (c == '\n') /* newline�� ���, �� ���� �о��� ������ ���� */
    //                 break;
    //         }
    //         else if (rc == 0)
    //         {
    //             if (n == 1)
    //                 return 0; /* EOF -> ����, ���� �����Ͱ� ���� ��� */
    //             else
    //                 break; /* EOF */
    //         }
    //         else
    //             return -1;
    //     }
    //     *bufp = 0;
    //     return n;
    // }

    Rio_readlineb(rp, buf, MAXLINE); // rp ���� buf�� ����, �� �а� ���� rp�� ���� ���� ó���� ����Ű�� ��.
    while (strcmp(buf, "\r\n"))      // buf�� ��û ����� �������� �Ǹ� 0 ��ȯ�ϰ� ��.
    {
        Rio_readlineb(rp, buf, MAXLINE); // ��� ���پ� �а� �ƹ��͵� ���Ѵ�.
        printf("%s", buf);
    }
    return;
}

int parse_uri(char *uri, char *filename, char *cgiargs)
{
    char *ptr;
    if (!strstr(uri, "cgi-bin")) /* Static content */
    {
        strcpy(cgiargs, "");
        strcpy(filename, "."); //if���� ������ ��� �Ǵ°��� �� �𸣰���. �Լ�ã�Ƽ�  �ôµ��� ���� �ȿ�.
        strcat(filename, uri);
        if (uri[strlen(uri) - 1] == '/')
            strcat(filename, "home.html");
        return 1;
    }
    else /* Dynamic content */
    {
        ptr = index(uri, '?');
        //CGI ���� ����
        if (ptr)
        {
            //����ǥ �ڿ� ���� �� ���� ���δ�.
            strcpy(cgiargs, ptr + 1);
            // �����ʹ� ���ڿ� ���������� �ٲ۴�.
            *ptr = '\0';
        }
        else
            strcpy(cgiargs, "");

        // ������ �κ� ��� URI�� �ٲ�
        strcpy(filename, ".");
        strcat(filename, uri);
        return 0;
    }
}

void serve_static(int fd, char *filename, int filesize)
{
    int srcfd;
    char *srcp, filetype[MAXLINE], buf[MAXBUF];
    /* Send response headers to client */
    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    sprintf(buf, "%sConnection: close\r\n", buf);
    sprintf(buf, "%Content-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
    Rio_writen(fd, buf, strlen(buf));
    printf("Response header:\n");
    printf("%s", buf);
    /* Send response body to client */
    srcfd = Open(filename, O_RDONLY, 0);
    srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    Close(srcfd);
    Rio_writen(fd, srcp, filesize);
    Munmap(srcp, filesize);
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
#include "csapp.h"

// doit은 무엇을 하는 함수일까요? 트랜잭션 처리함수. 들어온 요청을 읽고 분석.
// GETrequest가 들어오면 정적인지 동적인지 파악하여서 각각에 맞는 함수를 실행시킴. 오류시 에러표시도 포함.

void doit(int fd);

void echo(int fd);

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
        
        echo(connfd);
        
        Close(connfd);
    }
}
void echo(int fd)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;
    Rio_readinitb(&rio, fd);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0){
        if(strcmp(buf, "\r\n") == 0)
            break;
        Rio_writen(fd, buf, n);
    }
}

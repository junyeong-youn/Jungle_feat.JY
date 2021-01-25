#include "csapp.h"

// doit�� ������ �ϴ� �Լ��ϱ��? Ʈ����� ó���Լ�. ���� ��û�� �а� �м�.
// GETrequest�� ������ �������� �������� �ľ��Ͽ��� ������ �´� �Լ��� �����Ŵ. ������ ����ǥ�õ� ����.

void doit(int fd);

void echo(int fd);

// main�� �޴� ���� argc �� argv�� �����ϱ� -> �迭 ����, filename, port
// main���� �ϴ� ����? ���� ������ ���鼭 ����ϴ� ����
int main(int argc, char **argv)
{
    int listenfd, connfd;                  // ���⼭�� fd�� ����ü ���� �����ΰɱ�? -> file description
    char hostname[MAXLINE], port[MAXLINE]; // hostname:port -> localhost:4000
    // socklen_t �� ���� ���� �Ű� ������ ���Ǵ� ������ ���� �� ũ�� ���� ���� ���Ǹ� �����ش�
    socklen_t clientlen;                //client�� ��� �ִ°��� ���� ��
    struct sockaddr_storage clientaddr; //SOCKADDR_STORAGE  ����ü�� ���� �ּ� ������ �����Ѵ�.
    // SOCKADDR_STORAGE ����ü��  sockaddr ����ü�� ���̴� ���� ����� �� �ִ�.

    /* Check command-line args */
    if (argc != 2) // ���α׷� ���� �� port�� �Ƚ�����,
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]); //�ٸ� Ŭ���̾�Ʈ�� ������̴�!!
        exit(1);
    }
    // listenfd -> �� ��Ʈ�� ���� ��� ���� ����~
    listenfd = Open_listenfd(argv[1]);
    // ���� �������� ����
    while (1)
    {
        clientlen = sizeof(clientaddr);
        // ���� ��û ����
        // ���� ��û ť�� �ƹ��͵� ���� ��� �⺻������ ������ ���涧���� ȣ���ڸ� ���Ƶд�.
        // ������ non-blocking ����� ��쿣 ������ ����.
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

#include <stdio.h>
#include <unistd.h>

int main(void) {
    int MAXLINE = 100;
    char *p;
    char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
    int n1=0, n2=0;

    char* buf = "a=5000&b=5000";

    p = strchr(buf, '&');
    *p = '\0';
    strcpy(arg1, buf);
    printf("%s\n", arg1);
    strcpy(arg2, p+1);
    printf("%s\n", arg2);
    n1 = atoi(arg1);
    printf("%d\n", n1);
    n2 = atoi(arg2);
    printf("%d\n", n2);

}
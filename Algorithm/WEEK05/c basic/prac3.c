#include <stdio.h>

int main(void)
{
    //배열
    int s_arr[11] = {};
    for(int i=0; i<=10; i++)
    {
        s_arr[i] = i*10;
    }
    for(int x=0; x < sizeof(s_arr) / sizeof(int); x++)
    {
        printf("%d\n", s_arr[x]);
    }
    char str[10] = "coding";

    printf("%s\n", str);

    char kor[256] = "SW정글";

    printf("%s\n", kor);
    printf("%d\n", sizeof(kor));

    return 0;
}
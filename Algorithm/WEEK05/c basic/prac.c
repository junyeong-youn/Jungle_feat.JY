#include <stdio.h>

int main(void)
{   
    int stair;
    printf("���� �Է��ϼ���");
    scanf_s("%d", &stair);

    for(int i = 0; i<=stair; i++)
    {
        for(int j = i ; j<stair; j++)
        {
            printf(" ");
        }

        for(int k = 0; k<i; k++)
        {
            printf("**");
        }
        printf("*");

        for(int m = i; m<stair; m++)
        {
            printf(" ");
        }
        printf("\n");
    }


}
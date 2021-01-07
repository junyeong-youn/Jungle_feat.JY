#include <stdio.h>

int main(void)
{
    for(int i = 0; i<=4; i++)
    {
        for(int j = i ; j<=3; j++)
        {
            printf(" ");
        }

        for(int k = 0; k<i; k++)
        {
            printf("**");
        }
        printf("*");

        for(int m = i; m<=3; m++)
        {
            printf(" ");
        }
        printf("\n");
    }




}
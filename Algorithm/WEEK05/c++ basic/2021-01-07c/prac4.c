#include <stdio.h>

int main(void){

    for (int i = 0; i<5; i++)
    {
       
        for (int j = i; j <= 3; j++)
        {
            printf(" ");
        }
        for (int k = 4-i; k <= 4; k++)
        {
            printf("*");
        }
        printf("\n");    
    }

}
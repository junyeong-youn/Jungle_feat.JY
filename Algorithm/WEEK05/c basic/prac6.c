
#include <stdio.h>

void main()

{

     int *arScore;

     int i,stNum;

     int sum;

 

     printf("학생수를 입력하세요 : ");

     scanf("%d",&stNum);

     arScore=(int *)malloc(stNum*sizeof(int));

     if (arScore == NULL) {

          printf("메모리가 부족합니다.\n");

          exit(0);

     }

 

     for (i=0;i<stNum;i++) {

          printf("%d번 학생의 성적을 입력하세요 : ",i+1);

          scanf("%d",&arScore[i]);

     }

 

     sum=0;

     for (i=0;i<stNum;i++) {

          sum+=arScore[i];

     }

 

     printf("\n총점은 %d점이고 평균은 %d점입니다.\n",

          sum,sum/stNum);

 

     free(arScore);

}
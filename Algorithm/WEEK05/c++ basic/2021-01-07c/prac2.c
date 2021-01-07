#include <stdio.h>

int main(void)
{
    //예제
    char name[256];
    char crime[256];
    int age;
    float weight;
    double height;

    printf("이름 : \n");
    scanf_s("%s", &name, sizeof(name));
    printf("나이 : \n");
    scanf_s("%d", &age);
    printf("몸무게 : \n");
    scanf_s("%f", &weight);
    printf("키 : \n");
    scanf_s("%lf", &height);
    printf("범죄 : \n");
    scanf_s("%s", crime, sizeof(crime));

    printf("``````````````````````````````````````````\n");
    printf("이름 : %s\n", name);
    printf("나이 : %d\n", age);
    printf("몸무게 : %f\n", weight);
    printf("키 : %lf\n", height);
    printf("범죄 : %s\n", crime);

    return 0;

}
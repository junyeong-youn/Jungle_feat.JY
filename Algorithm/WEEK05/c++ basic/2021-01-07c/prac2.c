#include <stdio.h>

int main(void)
{
    //����
    char name[256];
    char crime[256];
    int age;
    float weight;
    double height;

    printf("�̸� : \n");
    scanf_s("%s", &name, sizeof(name));
    printf("���� : \n");
    scanf_s("%d", &age);
    printf("������ : \n");
    scanf_s("%f", &weight);
    printf("Ű : \n");
    scanf_s("%lf", &height);
    printf("���� : \n");
    scanf_s("%s", crime, sizeof(crime));

    printf("``````````````````````````````````````````\n");
    printf("�̸� : %s\n", name);
    printf("���� : %d\n", age);
    printf("������ : %f\n", weight);
    printf("Ű : %lf\n", height);
    printf("���� : %s\n", crime);

    return 0;

}
#include <stdio.h>

struct Info{
    char* name;
    int year;
    int price;
    char* company;

    //����ü���� ����ü
    struct Info* finfo;
};

// typedef struct Info{
//     char* name;
//     int year;
//     int price;                 //typedef�� �Ἥ struct Info�� ���°� ��� IF�� ġȯ�� ����
//     char* company;

//     struct Info* finfo;
// } IF;



int main(void)
{
    struct Info Info1;         //�����ٷ� ���� �ֱ�
    Info1.name = "��������";
    Info1.year = 2017;
    Info1.price = 50;
    Info1.company = "����ȸ��";

    printf("%d\n", Info1.price);

    struct  Info Info2 = {"�ʵ�����", 2017, 100, "�ʵ�ȸ��"}; //���ٷ� ���� �ʱ�ȭ�� �ֱ�

    printf("%d\n", Info2.price);

    // ����ü �迭
    struct Info arr[2] = {
    {"��������", 2015, 50, "����ȸ��"},
    {"�ʵ�����", 2015, 100, "�ʵ�ȸ��"}
    };

    // ����ü ������
    struct Info* ptr;
    ptr = &Info1;
    printf("�� �� �� : %s\n", (*ptr).name);
    printf("�߸ų⵵ : %d\n", (*ptr).year);
    printf("��    �� : %d\n", (*ptr).price);
    printf("�� �� �� : %s\n", (*ptr).company);

    struct Info* ptrr;                             //����� �����ε� (*).�� ���°ź���  ->�� ����.
    ptrr = &Info2;
    printf("�� �� �� : %s\n", ptrr->name);
    printf("�߸ų⵵ : %d\n", ptrr->year);
    printf("��    �� : %d\n", ptrr->price);
    printf("�� �� �� : %s\n", ptrr->company);

    //����ü ���� ����ü
    Info1.finfo = &Info2;
    printf("�� �� �� : %s\n", Info1.finfo->name);
    printf("�߸ų⵵ : %d\n", Info1.finfo->year);
    printf("��    �� : %d\n", Info1.finfo->price);
    printf("�� �� �� : %s\n", Info1.finfo->company);


    //typedef(�ڷ����� ���� ����)

    // IF info3;
    // info3.name = "�ٺ�����"

    return 0;    
}
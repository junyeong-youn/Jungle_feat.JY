#include <stdio.h>

struct Info{
    char* name;
    int year;
    int price;
    char* company;

    //구조체안의 구조체
    struct Info* finfo;
};

// typedef struct Info{
//     char* name;
//     int year;
//     int price;                 //typedef를 써서 struct Info를 쓰는것 대신 IF로 치환이 가능
//     char* company;

//     struct Info* finfo;
// } IF;



int main(void)
{
    struct Info Info1;         //여러줄로 값을 넣기
    Info1.name = "나도게임";
    Info1.year = 2017;
    Info1.price = 50;
    Info1.company = "나도회사";

    printf("%d\n", Info1.price);

    struct  Info Info2 = {"너도게임", 2017, 100, "너도회사"}; //한줄로 값을 초기화로 넣기

    printf("%d\n", Info2.price);

    // 구조체 배열
    struct Info arr[2] = {
    {"나도게임", 2015, 50, "나도회사"},
    {"너도게임", 2015, 100, "너도회사"}
    };

    // 구조체 포인터
    struct Info* ptr;
    ptr = &Info1;
    printf("게 임 명 : %s\n", (*ptr).name);
    printf("발매년도 : %d\n", (*ptr).year);
    printf("가    격 : %d\n", (*ptr).price);
    printf("제 작 사 : %s\n", (*ptr).company);

    struct Info* ptrr;                             //방식의 차이인데 (*).을 쓰는거보다  ->가 좋다.
    ptrr = &Info2;
    printf("게 임 명 : %s\n", ptrr->name);
    printf("발매년도 : %d\n", ptrr->year);
    printf("가    격 : %d\n", ptrr->price);
    printf("제 작 사 : %s\n", ptrr->company);

    //구조체 안의 구조체
    Info1.finfo = &Info2;
    printf("게 임 명 : %s\n", Info1.finfo->name);
    printf("발매년도 : %d\n", Info1.finfo->year);
    printf("가    격 : %d\n", Info1.finfo->price);
    printf("제 작 사 : %s\n", Info1.finfo->company);


    //typedef(자료형에 별명 지정)

    // IF info3;
    // info3.name = "바보게임"

    return 0;    
}
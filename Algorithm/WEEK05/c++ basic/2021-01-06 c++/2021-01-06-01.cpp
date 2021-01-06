#include <iostream>
#include <time.h>

int main()
{
    const int A = 0x00000001          //       1(2진수)
    const int B = 0x00000002          //      10(2진수)
    const int C = 0x00000004          //     100(2진수)
    const int D = 0x00000008          //    1000(2진수)
    const int E = 0x00000010          //   10000(2진수)

    int MIX = A | B | C; // 00111
    //MIX에 ABC를 다 조합

    MIX & A // 00111 &00001 = 00001
                    // 이것으로 MIX에 A가 있는지 확인가능. 1이 나오면 있고 0이면 없는것

    MIX ^= A; // 00111 ^ 00001 = 00110 A부분만 off함
    MIX ^= A; // 00110 ^ 00001 = 00111 A부분만 on함 

    int iHigh = 187;  //aa(16)
    int iLow = 13560; //34f8(16)

    int iNumber = iHigh;

    iNumber <<= 16; //aa0000(16)

    iNumber |= iLow; // aa34f8(16)

    iNumber >> 16; // aa(16) > 187(10)
    iNumber & 0x0000ffff // 34f8(16) > 13560(10)

    ++iNumber; // 전치는 1증가시키고 출력

    iNumber++; // 후치는 출력시키고 1증가

    if (A != 0)
    {
        cout << "abc" << endl; //실행문
    }
        
    

    srand((unsigned int)time(0));  //unsigned int > 오류 발생 줄이기 위해서 씀
    rand();
    (rand() % 101);                // 100까지 랜덤
    ((rand() % 101 + 100));        // 100-200 랜덤 

    switch(number)
    {
    case 1:
        cout<<
        break;
    case 2:
        cout<<
        break;
    case 3:
        cout<<
        break;
    default:
        cout<<
        break;
    };


    enum NUM
    {
        NUM_0, = 10
        NUM_1, // 11
        NUM_2, // 12
        NUM_3  // 13
    };

    #define NUM_4 4

}
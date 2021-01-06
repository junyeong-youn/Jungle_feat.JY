#include <iostream>

int main()
{
    num = 0;
    while(num <10)   //while문
    {
        cout << num << endl;
        ++num;
        if(num == 4)
            break;
    }

    int i = 0;

    do                //do while문
    {
        printf("Hello, world! %d\n", i);    
        i++;     
    } while (i < 100);

    for(int i=0; i<10; ++i) // for문
    {
        cout << i << endl;  // 0~9까지 출력 된다. for문을 다 돌고 나서 i값이 +1되는 구조인듯
    }


    //배열

    int array[10] = {1,2,3,4,5,6,7,8,9}; // 값을 넣어서 초기화 가능

    int array[10] = {1,2,3,4,5}; // 5까지만 들어가고 나머진 0

    int array[10] = {}; // 모든 값이 0

    array[1] = 1; //직접 입력


    //2차원 배열

    int array2[10][10];

}
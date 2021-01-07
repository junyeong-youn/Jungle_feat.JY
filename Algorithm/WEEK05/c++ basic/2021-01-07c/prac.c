#include <stdio.h>

int main(){





}

struct rec{
    int key;
    ...


}A[N+1];

int seqsearch1(int k){

    int i = 1;
    while((i<N+1) && (A[i].key != k)) i++;
    return(i);
}
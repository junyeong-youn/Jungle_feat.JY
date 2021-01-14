// 삽입은 구현했는데 값이 10개쯤 넘어가서 테스트를 해보니 없는값을 읽어야된다고 세그먼트 뜹니다.
// 삭제는 구현하다가 못했습니다.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 3
#define t 2

typedef struct node{
    bool leaf;
    int size;
    int key[M];
    struct node* ptr[M+1]; 
}node;

typedef struct Bptree{
    node* root;
}Bptree;

void insertkey(Bptree* T, int key);
void split(node* x, int index);
void nonfull_insert(node* x, int key);
void delete(node* x, int key);
void bind(node *x, int i, int key);


int main(void){
    Bptree* T =  malloc(sizeof(Bptree));
    node* x = malloc(sizeof(node));
    x->leaf = true;
    x->size = 0;
    T->root = x;

    insertkey(T, 10);
    insertkey(T, 20);
    insertkey(T, 30);
    insertkey(T, 40);
    insertkey(T, 50);
    insertkey(T, 60);
    insertkey(T, 70);
    insertkey(T, 80);
    insertkey(T, 90);
    insertkey(T, 100);
    insertkey(T, 110);
    insertkey(T, 120);
    insertkey(T, 130);
    insertkey(T, 140);
    insertkey(T, 150);
    insertkey(T, 160);
    insertkey(T, 170);
    insertkey(T, 180);
    insertkey(T, 190);
    insertkey(T, 200);
    insertkey(T, 210);
    insertkey(T, 220);
    insertkey(T, 230);
    insertkey(T, 240);
    insertkey(T, 250);
    insertkey(T, 260);
    insertkey(T, 9);
    insertkey(T, 39);
    insertkey(T, 101);
    insertkey(T, 102);
    insertkey(T, 103);
    insertkey(T, 104);
    insertkey(T, 161);
    insertkey(T, 191);
    insertkey(T, 251);
    
    print_for_exam(T->root);

    printf("프로그램이 정상적으로 종료 되었음.");
    system("pause");

    return 0;
}

void print_for_exam(node* x) {
    if (x->leaf) {
        for (int i = 0; i < x->size; i++) {
            printf("[%5d]\n", x->key[i]);
        }
    }
    else {
        for (int i = 0; i < x->size; i++) {
            print_for_exam(x->ptr[i]);
            printf("[%5d]\n", x->key[i]);
        }
        print_for_exam(x->ptr[x->size]);
    }
}



void insertkey(Bptree* T, int key){
    node *r = T->root;
    if(r->size == M){
        node *s = malloc(sizeof(node));
        T->root = s;
        s->leaf = false;
        s->size = 0;
        s->ptr[0] = r;
        split(s, 0);
        nonfull_insert(s, key);
    }
    else{
        nonfull_insert(r, key);
    }
}

void split(node* x, int index){
    node* right_ch = malloc(sizeof(node));
    node* left_ch = x->ptr[index];
    if (left_ch->leaf == true){
        right_ch->leaf = left_ch->leaf;
        right_ch->size = t-1;
        for(int j=0; j<=t-2; j++){
            right_ch->key[j] = left_ch->key[j+t];
        }
        left_ch->size = t;
        for(int j = x->size; j>=index+1; j--){
            x->ptr[j+1] = x->ptr[j];
        }
        x->ptr[index+1] = right_ch;
        for(int j = x->size-1; j>=index; j--){
            x->key[j+1] = x->key[j];            
        }
        x->key[index] = x->ptr[index+1]->key[0];
        x->size = x->size + 1;
    }
    else
    {
        right_ch->leaf = left_ch->leaf;
        right_ch->size = 1;
        left_ch->size = 1;
        right_ch->key[0] = left_ch->key[2];
        x->key[index] = left_ch->key[1];
        right_ch->ptr[0] = left_ch->ptr[2];
        right_ch->ptr[1] = left_ch->ptr[3];
        for(int j = x->size; j>=index+1; j--){
            x->ptr[j+1] = x->ptr[j];
        }
        x->ptr[index+1] = right_ch;
        
        for(int j = x->size-1; j>=index; j--){
            x->key[j+1] = x->key[j];            
        }
        x->key[index] = left_ch->key[t-1];
        x->size = x->size + 1;
    }
    
}

void nonfull_insert(node* x, int key){
    int i =  x->size-1;
    if (x->leaf == true){
        while(i>=0 && key<x->key[i]){
            x->key[i+1] = x->key[i];
            i--;
        }
        x->key[i+1] = key;
        x->size = x->size + 1;
    }
    else
    {
        if(key>x->key[i]){
            i = x->size;
        }
        else{
            while(i>=0 && key<x->key[i]){
                i--;
            }
            i=i+1;
        }
        if(x->ptr[i]->size == M){
            split(x, i);
            if (key>x->key[i]){i++;}
        }
        nonfull_insert(x->ptr[i], key);  
    }
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
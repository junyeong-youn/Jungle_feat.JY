#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 5
#define t 3

void insertkey(Bptree* T, int key);
void split(node* x, int index);
void nonfull_insert(node* x, int key);


typedef struct node{
    bool leaf;
    int size;
    int key[M];
    struct node* ptr[M+1]; 
}node;

typedef struct Bptree{
    struct Bptree* root;
}Bptree;

int main(void){
    Bptree* T =  malloc(sizeof(Bptree));
    node* x = malloc(sizeof(node));
    x->leaf = true;
    x->size = 0;
    T->root = x;


    insertkey(T, 2);

    return 0;
}

void insertkey(Bptree* T, int key){
    node *r = T->root;
    if(r->size == 2*t-1){
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
    if (right_ch->leaf == true){
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
        right_ch->size = t-1;
        for(int j=0; j<=t-2; j++){
            right_ch->key[j] = left_ch->key[j+t];
        }
        for(int j =0; j<=t-1; j++){
            right_ch->ptr[j]=left_ch->ptr[j+t];
        }
        left_ch->size = t-1;
        for(int j = x->size; j>=index+1; j--){
            x->ptr[j+1] = x->ptr[j];
        }
        x->ptr[index+1] = right_ch;
        for(int j = x->size-1; j>=index; j--){
            x->key[j+1] = x->key[j];            
        }
        x->key[index] = x->ptr[index+1]->key[t-1];
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
        while(i>=0 && key<x->key[i]){
            i--;
        }
        i=i+1;
        if(x->ptr[i]->size == M){
            split(x, i);
            if (key>x->key[i]){i++;}
        }
        nonfull_insert(x->ptr[i], key);  
    }
    
}
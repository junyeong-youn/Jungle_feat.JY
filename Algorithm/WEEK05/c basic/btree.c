#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <Windows.h>

#define wait_time 2000
#define M 5
#define t 3
typedef struct node{
    bool leaf;
    int size;
    int key[M]; 
    struct node* p_arr[M+1];
} node;
typedef struct Btree{
    node* root;
} Btree;

void Btree_insert(Btree* T, int k);
void Btree_split(node* x, int i);
void Btree_insert_non(node* x, int k);



int main(void){

    Btree* T = malloc(sizeof(Btree));
    node* x = malloc(sizeof(node));
    x->leaf = true;
    x->size = 0;
    T->root = x;
    Btree_insert(T, 5);
    Btree_insert(T, 8);
    Btree_insert(T, 2);
    Btree_insert(T, 3);
    Btree_insert(T, 4);
    Btree_insert(T, 10);
    Btree_insert(T, 1);
    Btree_insert(T, 9);
    Btree_insert(T, 6);
    Btree_insert(T, 16);
    Btree_insert(T, 13);
    Btree_insert(T, 11);
    Btree_insert(T, 19);



    free(T);
    free(x);
    return 0;
}


void Btree_insert(Btree* T, int k){
    node* r = T->root;
    if ((r->size) == M){
        node* s = malloc(sizeof(node));
        T->root = s;
        s->leaf = false;
        s->size = 0;
        s->p_arr[0] = r;
        Btree_split(s, 0);
        Btree_insert_non(s, k); // node *s
    }
    else
    {
        Btree_insert_non(r, k); //
    }
}

void Btree_split(node* x, int i){
    node* z = malloc(sizeof(node));
    node* y = x->p_arr[i];
    z->leaf = y->leaf;
    z->size = t-1;
    for(int j = 0; j<= t-2; j++){
        z->key[j] = y->key[j+t];
    }
    if ((y->leaf) == false){
        for(int j=0; j <= t-1; j++){
            z->p_arr[j] = y->p_arr[j+t];
        }
    }
    y->size = t-1;
    for(int j=(x->size); i<=j; j--){
        x->p_arr[j+1] = x->p_arr[j];
        }
    x->p_arr[i+1] = z;
    for(int j=(x->size); i<=j; j--){
        x->key[j] = x->key[j-1];
    }
    x->key[i] = y->key[t-1];
    x->size = x->size + 1;
}

void Btree_insert_non(node* x, int k){
    int i = x->size-1;
    if (x->leaf == true){
        while(i >= 0 && k < x->key[i]){
            x->key[i+1] = x->key[i];
            i--;
        }
        x->key[i+1] = k;
        x->size = x->size + 1;
    }
    else{
        while(i >= 0 && k < x->key[i]){
            i--;}
        i = i+1;
        if (x->p_arr[i]->size == M){
            Btree_split(x, i);
            if (k> x->key[i]){
                i++;
            }
        }
        Btree_insert_non(x->p_arr[i], k); 
    }
}

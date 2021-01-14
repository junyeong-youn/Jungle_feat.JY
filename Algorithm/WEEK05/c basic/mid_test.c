#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#define M 3
#define t 2
#define TEST { 10,1,3,63,82,6,31,8,2,16,11,77,96,14,92,21,47,23,24,78,26,97,15,4,30,69,37,38,76,90,17,87,53,44,45,46,9,41,54,43,22,84,58,39,65,28,42,59,99,70,71,72,29,74,73,68,13,60,79,80,81,85,83,64,94,86,66,88,93,40,91,62,25,20,36,95,19,52,55,100 }


typedef struct node{
    bool leaf;
    int size;
    int data[M];
    int key[M];
    struct node* ptr[M+1]; 
}node;

typedef struct Bptree{
    node* root;
}Bptree;

void insertkey(Bptree* T, int key, int data);
void split(node* x, int index);
void nonfull_insert(node* x, int key, int data);
void delete(node* x, int key);
// void bind(node *x, int i, int key);
void print_for_exam(node* x);


int main()
{
    int arr[80] = TEST;
    Bptree* T = malloc(sizeof(Bptree));
    node* x = malloc(sizeof(node));
    x->leaf = true;
    x->size = 0;
    T->root = x;

    insertkey(T, 10, 1);
    insertkey(T, 20, 2);
    insertkey(T, 30, 3);
    insertkey(T, 40, 4);
    insertkey(T, 50, 5);
    insertkey(T, 60, 6);
    insertkey(T, 70, 7);
    insertkey(T, 80, 8);
    insertkey(T, 90, 9);
    insertkey(T, 100, 10);
    insertkey(T, 110, 11);
    insertkey(T, 120, 12);



		// TEST 1 CASE
    // insertkey(T, 4, 4000);
    // insertkey(T, 1, 1000);
    // insertkey(T, 3, 3000);
    // insertkey(T, 2, 2000);

    // delete(T->root, 4);
    // delete(T->root, 2);
    // delete(T->root, 3);

    // printf("---- TEST1 ----\n");
    // print_for_exam(T->root);

		// TEST 2 CASE
    // for (int i = 2; i <= 100; i++) {
    //     InsertToTree(T, i, i * 1000);
    // }
    // for (int i = 50; i <= 70; i++) {
    //     DeleteFromTree(T, T->root, i);
    // }

    // printf("\n\n\n\n\n\n");
    // printf("---- TEST2 ----");
    // print_for_exam(T->root);

		// TEST3 CASE
    // for (int i = 50; i <= 70; i++) {
    //     InsertToTree(T, i, i * 1000);
    // }

    // for (int i = 0; i <80; i++) {
    //     DeleteFromTree(T, T->root, arr[i]);
    // }

    // printf("\n\n\n\n\n\n");
    // printf("---- TEST3 ----");
    print_for_exam(T->root);

    printf("프로그램이 정상적으로 종료 되었음.");
    system("pause");
    return 0;
}


///////////////////////////////////////////////////////////////////////
void print_for_exam(node* x) {
    if (x->leaf) {
        for (int i = 0; i < x->size; i++) {
            printf("[%5d, %5d]\n", x->key[i], x->data[i]);
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

/////////////////////////////////////////////////////////////////////////
void insertkey(Bptree* T, int key, int data){
    node *r = T->root;
    if(r->size == M){
        node *s = malloc(sizeof(node));
        T->root = s;
        s->leaf = false;
        s->size = 0;
        s->ptr[0] = r;
        split(s, 0);
        nonfull_insert(s, key, data);
    }
    else{
        nonfull_insert(r, key, data);
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
            right_ch->data[j] = left_ch->data[j+t];
        }
        left_ch->size = t;
        for(int j = x->size; j>=index+1; j--){
            x->ptr[j+1] = x->ptr[j];
        }
        x->ptr[index+1] = right_ch;
        for(int j = x->size-1; j>=index; j--){
            x->key[j+1] = x->key[j]; 
            x->data[j+1] = x->data[j];         
        }
        x->key[index] = x->ptr[index+1]->key[0];
        x->data[index] = x->ptr[index+1]->data[0];
        
        x->size = x->size + 1;
    }
    else
    {
        right_ch->leaf = left_ch->leaf;
        right_ch->size = 1;
        left_ch->size = 1;
        right_ch->key[0] = left_ch->key[2];
        right_ch->data[0] = left_ch->data[2];
        x->key[index] = left_ch->key[1];
        x->data[index] = left_ch->data[1];
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

void nonfull_insert(node* x, int key, int data){
    int i =  x->size-1;
    if (x->leaf == true){
        while(i>=0 && key<x->key[i]){
            x->key[i+1] = x->key[i];
            x->data[i+1] = x->data[i];
            
            i--;
        }
        x->key[i+1] = key;
        x->data[i+1] = data;

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
        nonfull_insert(x->ptr[i], key, data);  
    }
    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

// void delete(node* x, int key){

//     if (x->leaf == true)
//     {
//         for (int i = 0; i <= x->size; i++)
//         {
//             if (x->key[i] == key)
//             {
//                 if (x->ptr[i]->size >= t){
//                     for (int j = i;  j<= x->size - 2; j++)
//                     {
//                         x->key[i] = x->key[i + 1];
//                     }
//                     x->size = x->size - 1;
//                     break;
//                 }
//             }
//         }
//     }
//     else{
//         int i = 0;
//         while (x->key[i] < key)
//         {
//             i++;
//             if(i > x->size){
//                 i = x->size;
//                 break;
//             }
//         }
        
//         if(x->ptr[i]->leaf == true){
//             if(i < x->size){
//                 if(x->ptr[i+1]->size >= t){
//                     x->key[i] = x->ptr[i+1]->key[0];
//                     x->ptr[i]->key[x->ptr[i]->size] = x->ptr[i+1]->key[0];
//                     for (int j = 0; j<= x->ptr[i+1]->size-2; j++){
//                         x->ptr[i+1]->key[j] = x->ptr[i+1]->key[j+1];
//                     }
//                     x->ptr[i]->size = x->ptr[i]->size + 1;
//                     x->ptr[i+1]->size = x->ptr[i+1]->size - 1;
//                 }
//             }
//             if(x->ptr[i-1]->size >= t){
//                 x->key[i] = x->ptr[i-1]->key[x->ptr[i-1]->size-1];
//                 for (int j = x->ptr[i]->size; j >= i-1; j--){
//                     x->ptr[i]->key[j] = x->ptr[i]->key[j-1];
//                 }
//                 x->ptr[i]->key[0] = x->ptr[i-1]->key[x->ptr[i-1]->size-1];
//                 x->ptr[i]->size = x->ptr[i]->size + 1;
//                 x->ptr[i-1]->size = x->ptr[i-1]->size - 1;
//             }
//             else{
//                 for(int j=x->ptr[i]->size; j<x->ptr[i]->size + x->ptr[i+1]->size; j++){
//                     x->ptr[i]->key[j] = x->ptr[i+1]->key[j-x->ptr[i]->size];
//                 }
//                 x->ptr[i]->size = x->ptr[i]->size + x->ptr[i+1]->size;
//                 x->key[i] = x->ptr[i]->key[0];
     
//             }
//         }
//         else{
//             if ((x->ptr[i + 1]->size >= t) && (x->ptr[i]->size == t - 1))
//             {
//                 x->ptr[i]->key[t - 1] = x->key[i];
//                 x->key[i] = x->ptr[i + 1]->key[0];
//                 x->ptr[i]->ptr[t] = x->ptr[i + 1]->ptr[0];

//                 x->ptr[i]->size = x->ptr[i]->size + 1;
//                 x->ptr[i + 1]->size = x->ptr[i + 1]->size - 1;

//                 for (int j = 0; x->ptr[i + 1]->size - 1; j++)
//                 {
//                     x->ptr[i + 1]->key[j] = x->ptr[i + 1]->key[j + 1];
//                 }
//                 for (int j = 0; x->ptr[i + 1]->size; j++)
//                 {
//                     x->ptr[i + 1]->ptr[j] = x->ptr[i + 1]->ptr[j + 1];
//                 }
//                 delete(x->ptr[i], key);
//             }

//             if (i == x->size && x->ptr[i - 1] >= t)
//             {
            
//                 for (int j = x->ptr[i]->size - 1; j >= 0; j--)
//                 {
//                     x->ptr[i]->key[j + 1] = x->ptr[i]->key[j];
//                 }
               
//                 for (int j = x->ptr[i]->size; j >= 0; j--)
//                 {
//                     x->ptr[i]->ptr[j + 1] = x->ptr[i]->ptr[j];
//                 }
             
//                 x->ptr[i]->key[0] = x->key[i - 1];
               
//                 x->ptr[i]->ptr[0] = x->ptr[i - 1]->ptr[t - 1];
            
//                 x->key[i - 1] = x->ptr[i - 1]->key[t - 1];
       
//                 x->ptr[i]->size = x->ptr[i]->size + 1;
//                 x->ptr[i - 1]->size = x->ptr[i - 1]->size - 1;
//                 delete(x->ptr[i], key);
//             }
//             else{
//                 bind(x, i, key);
//             }
//             if (x->size == 0)
//             {
//                 free(x);  
//             }    
//         }
//     }
// }

// void bind(node *x, int i, int key)
// {
//     node *y = x->ptr[i];
//     node *z = x->ptr[i + 1];
//     int m = y->size;
//     int p = z->size;
//     y->key[m] = x->key[i];
//     for (int j = 0; p - 1 <= j; j++)
//     {
//         y->key[m + j + 1] = z->key[j];
//     }
//     y->size = m + p + 1;
//     for (int j = i + 1; x->size - 1 <= j; j++)
//     {
//         x->ptr[j] = x->ptr[j + 1];
//     }
//     x->size = x->size - 1;
//     free(z);
//     delete(y, key);
// }
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define M 5
#define t 3

typedef struct node{
    int key[M];
    int size;
    bool leaf;
    struct node* ptr[M+1];
} node;
typedef struct Bplustree{
    node*root;
} Bplustree;

void Bplustree_insert(Bplustree *T, int k);
void Bplustree_split(node *x, int i);
void Bplustree_insert_non(node *x, int k);

void Bplustree_delete(node* x, int k);
void Bplustree_bind(node *x, int i, int k);


int main(void)
{
    Bplustree *T = malloc(sizeof(Bplustree));
    node *x = malloc(sizeof(node));
    x->leaf = true;
    x->size = 0;
    T->root = x;

    Bplustree_insert(T, 10);
    Bplustree_insert(T, 20);
    Bplustree_insert(T, 30);
    Bplustree_insert(T, 40);
    Bplustree_insert(T, 50);
    Bplustree_insert(T, 60);
    Bplustree_insert(T, 70);
    Bplustree_insert(T, 80);
    Bplustree_insert(T, 90);
    Bplustree_insert(T, 100);
    Bplustree_insert(T, 110);
    Bplustree_insert(T, 120);
    Bplustree_insert(T, 130);
    Bplustree_insert(T, 140);
    Bplustree_insert(T, 150);
    Bplustree_insert(T, 160);
    Bplustree_insert(T, 170);
    Bplustree_insert(T, 180);
    Bplustree_insert(T, 190);
    Bplustree_insert(T, 200);
    Bplustree_insert(T, 210);
    Bplustree_insert(T, 220);
    Bplustree_insert(T, 230);
    Bplustree_insert(T, 240);
    Bplustree_insert(T, 250);
    Bplustree_insert(T, 260);
    Bplustree_insert(T, 9);
    Bplustree_insert(T, 39);
    Bplustree_insert(T, 101);
    Bplustree_insert(T, 102);
    Bplustree_insert(T, 103);
    Bplustree_insert(T, 104);
    Bplustree_insert(T, 161);
    Bplustree_insert(T, 191);
    Bplustree_insert(T, 251);


    printf("%d", T->root->ptr[2]->key[2]);

    return 0;
}


void Bplustree_insert(Bplustree *T, int k)
{
    node *r = T->root;
    if ((r->size) == M)
    {
        node *s = malloc(sizeof(node));
        T->root = s;
        s->leaf = false;
        s->size = 0;
        s->ptr[0] = r;
        Bplustree_split(s, 0);
        Bplustree_insert_non(s, k);
    }
    else
    {
        Bplustree_insert_non(r, k);
    }
}

void Bplustree_split(node *x, int i)
{
    node *z = malloc(sizeof(node));
    node *y = x->ptr[i];

    if (y->leaf = true){
        z->leaf = y->leaf;
        z->size = t - 1;
        for (int j = 0; j <= t - 2; j++)
        {
            z->key[j] = y->key[j + t];
        }
        if ((y->leaf) == false)
        {
            for (int j = 0; j <= t - 1; j++)
            {
                z->ptr[j] = y->ptr[j + t];
            }
        }
        y->size = t;
        for (int j = (x->size+1); i+1 <= j; j--)
        {
            x->ptr[j + 1] = x->ptr[j];
        }
        x->ptr[i + 1] = z;
        for (int j = (x->size+1); i+1 <= j; j--)
        {
            x->key[j+1] = x->key[j];
        }
        x->key[i] = y->key[t - 1];
        x->size = x->size + 1;
    } 
    else{
        z->leaf = y->leaf;
        z->size = t - 1;
        for (int j = 0; j <= t - 2; j++)
        {
            z->key[j] = y->key[j + t];
        }
        if ((y->leaf) == false)
        {
            for (int j = 0; j <= t - 1; j++)
            {
                z->ptr[j] = y->ptr[j + t];
            }
        }
        y->size = t - 1;
        for (int j = (x->size); i <= j; j--)
        {
            x->ptr[j + 1] = x->ptr[j];
        }
        x->ptr[i + 1] = z;
        for (int j = (x->size); i <= j; j--)
        {
            x->key[j] = x->key[j - 1];
        }
        x->key[i] = y->key[t - 1];
        x->size = x->size + 1;
    }
}

void Bplustree_insert_non(node *x, int k)
{
    int i = x->size - 1;
    if (x->leaf == true)
    {
        while (i >= 0 && k < x->key[i])
        {
            x->key[i + 1] = x->key[i];
            i--;
        }
        x->key[i + 1] = k;
        x->size = x->size + 1;
    }
    else
    {
        while (i >= 0 && k < x->key[i])
        {
            i--;
        }
        i = i + 1;
        if (x->ptr[i]->size == M)
        {
            Bplustree_split(x, i);
            if (k > x->key[i])
            {
                i++;
            }
        }
        Bplustree_insert_non(x->ptr[i], k);
    }
}

////////////////////////////////////////////////////////////////////////////////

void Bplustree_delete(node* x, int k)
{
    if (x->leaf == true)
    {
        for (int i = 0; i <= x->size; i++)
        {
            if (x->key[i] == k)
            {
                if (x->ptr[i]->size >= t){
                    for (int j = i;  j<= x->size - 2; j++)
                    {
                        x->key[i] = x->key[i + 1];
                    }
                    x->size = x->size - 1;
                    break;
                }
            }
        }
    }
    else{
        int i = 0;
        while (x->key[i] < k)
        {
            i++;
            if(i > x->size){
                i = x->size;
                break;
            }
        }
        
        if(x->ptr[i]->leaf == true){
            if(i < x->size){
                if(x->ptr[i+1]->size >= t){
                    x->key[i] = x->ptr[i+1]->key[0];
                    x->ptr[i]->key[x->ptr[i]->size] = x->ptr[i+1]->key[0];
                    for (int j = 0; j<= x->ptr[i+1]->size-2; j++){
                        x->ptr[i+1]->key[j] = x->ptr[i+1]->key[j+1];
                    }
                    x->ptr[i]->size = x->ptr[i]->size + 1;
                    x->ptr[i+1]->size = x->ptr[i+1]->size - 1;
                }
            }
            if(x->ptr[i-1]->size >= t){
                x->key[i] = x->ptr[i-1]->key[x->ptr[i-1]->size-1];
                for (int j = x->ptr[i]->size; j >= i-1; j--){
                    x->ptr[i]->key[j] = x->ptr[i]->key[j-1];
                }
                x->ptr[i]->key[0] = x->ptr[i-1]->key[x->ptr[i-1]->size-1];
                x->ptr[i]->size = x->ptr[i]->size + 1;
                x->ptr[i-1]->size = x->ptr[i-1]->size - 1;
            }
            else{
                for(int j=x->ptr[i]->size; j<x->ptr[i]->size + x->ptr[i+1]->size; j++){
                    x->ptr[i]->key[j] = x->ptr[i+1]->key[j-x->ptr[i]->size];
                }
                x->ptr[i]->size = x->ptr[i]->size + x->ptr[i+1]->size;
                x->key[i] = x->ptr[i]->key[0];
     
            }
        }
        else{
            if ((x->ptr[i + 1]->size >= t) && (x->ptr[i]->size == t - 1))
            {
                x->ptr[i]->key[t - 1] = x->key[i];
                x->key[i] = x->ptr[i + 1]->key[0];
                x->ptr[i]->ptr[t] = x->ptr[i + 1]->ptr[0];

                x->ptr[i]->size = x->ptr[i]->size + 1;
                x->ptr[i + 1]->size = x->ptr[i + 1]->size - 1;

                for (int j = 0; x->ptr[i + 1]->size - 1; j++)
                {
                    x->ptr[i + 1]->key[j] = x->ptr[i + 1]->key[j + 1];
                }
                for (int j = 0; x->ptr[i + 1]->size; j++)
                {
                    x->ptr[i + 1]->ptr[j] = x->ptr[i + 1]->ptr[j + 1];
                }
                Bplustree_delete(x->ptr[i], k);
            }

            if (i == x->size && x->ptr[i - 1] >= t)
            {
                //오른쪽 키값 밀기
                for (int j = x->ptr[i]->size - 1; j >= 0; j--)
                {
                    x->ptr[i]->key[j + 1] = x->ptr[i]->key[j];
                }
                //오른쪽 포인터값 밀기
                for (int j = x->ptr[i]->size; j >= 0; j--)
                {
                    x->ptr[i]->ptr[j + 1] = x->ptr[i]->ptr[j];
                }
                //부모노드에 있는 값을 오른쪽으로 옮긴다
                x->ptr[i]->key[0] = x->key[i - 1];
                //부모노드에 있는 값의 포인터를 왼쪽 끝 값의 포인터로 바꾼다.
                x->ptr[i]->ptr[0] = x->ptr[i - 1]->ptr[t - 1];
                //왼쪽 노드 끝값을 부모노드로 옮긴다.
                x->key[i - 1] = x->ptr[i - 1]->key[t - 1];
                //사이즈 바꾸기
                x->ptr[i]->size = x->ptr[i]->size + 1;
                x->ptr[i - 1]->size = x->ptr[i - 1]->size - 1;
                Bplustree_delete(x->ptr[i], k);
            }
            else{
                Bplustree_bind(x, i, k);
            }
            if (x->size == 0)
            {
                free(x);  
            }    
        }
    }
}

//                 else{
//                     if(x->ptr[i+1]->size >= t){
//                         x->key[i] = x->ptr[i+1]->key[0];
//                         x->ptr[i]->key[x->ptr[i]->size] = x->ptr[i+1]->key[0];
//                         for (int j = 0; j<= x->ptr[i+1]->size-2; j++){
//                             x->ptr[i+1]->key[j] = x->ptr[i+1]->key[j+1];
//                         }
//                         x->ptr[i]->size = x->ptr[i]->size + 1;
//                         x->ptr[i+1]->size = x->ptr[i+1]->size - 1;
//                         break;
//                     }
//                     if(x->ptr[i-1]->size >= t){
//                         x->key[i] = x->ptr[i-1]->key[x->ptr[i-1]->size-1];
//                         for (int j = x->ptr[i]->size; j >= i-1; j--){
//                             x->ptr[i]->key[j] = x->ptr[i]->key[j-1];
//                         }
//                         x->ptr[i]->key[0] = x->ptr[i-1]->key[x->ptr[i-1]->size-1];
//                         x->ptr[i]->size = x->ptr[i]->size + 1;
//                         x->ptr[i-1]->size = x->ptr[i-1]->size - 1;
//                         break;
//                     }
//                     else{
//                         for(int j=x->ptr[i]->size; j<x->ptr[i]->size + x->ptr[i+1]->size; j++){
//                             x->ptr[i]->key[j] = x->ptr[i+1]->key[j-x->ptr[i]->size];
//                         }
//                         x->ptr[i]->size = x->ptr[i]->size + x->ptr[i+1]->size;
//                         x->key[i] = x->ptr[i]->key[0];
                        


//                         break;
//                     }

//                 }
//             }
//         }
//     }
//     else{
//         int i = 0;
//         while (x->key[i] < k)
//         {
//             i++;
//         }
//         if ((x->ptr[i + 1]->size >= t) && (x->ptr[i]->size == t - 1))
//         {
//             x->ptr[i]->key[t - 1] = x->key[i];
//             x->key[i] = x->ptr[i + 1]->key[0];
//             x->ptr[i]->ptr[t] = x->ptr[i + 1]->ptr[0];

//             x->ptr[i]->size = x->ptr[i]->size + 1;
//             x->ptr[i + 1]->size = x->ptr[i + 1]->size - 1;

//             for (int j = 0; x->ptr[i + 1]->size - 1; j++)
//             {
//                 x->ptr[i + 1]->key[j] = x->ptr[i + 1]->key[j + 1];
//             }
//             for (int j = 0; x->ptr[i + 1]->size; j++)
//             {
//                 x->ptr[i + 1]->ptr[j] = x->ptr[i + 1]->ptr[j + 1];
//             }
//             Bplustree_delete(x->ptr[i], k);
//         }

//         if (i == x->size && x->ptr[i - 1] >= t)
//         {
//             //오른쪽 키값 밀기
//             for (int j = x->ptr[i]->size - 1; j >= 0; j--)
//             {
//                 x->ptr[i]->key[j + 1] = x->ptr[i]->key[j];
//             }
//             //오른쪽 포인터값 밀기
//             for (int j = x->ptr[i]->size; j >= 0; j--)
//             {
//                 x->ptr[i]->ptr[j + 1] = x->ptr[i]->ptr[j];
//             }
//             //부모노드에 있는 값을 오른쪽으로 옮긴다
//             x->ptr[i]->key[0] = x->key[i - 1];
//             //부모노드에 있는 값의 포인터를 왼쪽 끝 값의 포인터로 바꾼다.
//             x->ptr[i]->ptr[0] = x->ptr[i - 1]->ptr[t - 1];
//             //왼쪽 노드 끝값을 부모노드로 옮긴다.
//             x->key[i - 1] = x->ptr[i - 1]->key[t - 1];
//             //사이즈 바꾸기
//             x->ptr[i]->size = x->ptr[i]->size + 1;
//             x->ptr[i - 1]->size = x->ptr[i - 1]->size - 1;
//             Bplustree_delete(x->ptr[i], k);
//         }
//         else
//             Bplustree_bind(x, i, k);

//         if (x->size == 0)
//         {
//             free(x);  
//         }    
//     }
// }

void Bplustree_bind(node *x, int i, int k)
{
    node *y = x->ptr[i];
    node *z = x->ptr[i + 1];
    int m = y->size;
    int p = z->size;
    y->key[m] = x->key[i];
    for (int j = 0; p - 1 <= j; j++)
    {
        y->key[m + j + 1] = z->key[j];
    }
    y->size = m + p + 1;
    for (int j = i + 1; x->size - 1 <= j; j++)
    {
        x->ptr[j] = x->ptr[j + 1];
    }
    x->size = x->size - 1;
    free(z);
    Bplustree_delete(y, k);
}
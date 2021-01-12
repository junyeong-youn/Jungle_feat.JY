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

    Bplustree_insert(T, 1);
    Bplustree_insert(T, 2);
    Bplustree_insert(T, 3);
    Bplustree_insert(T, 4);
    Bplustree_insert(T, 5);
    Bplustree_insert(T, 6);
    Bplustree_insert(T, 7);
    Bplustree_insert(T, 8);
    Bplustree_insert(T, 9);
    Bplustree_insert(T, 10);
    


    printf("%d", T->root->ptr[1]->key[0]);

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

/////////////////////////////////////////////////////////////////////////////

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
            else{
                if(x->ptr[i+1]->size >= t){
                    

                }
                 if(x->ptr[i-1]->size >= t){
                    

                }
                else{



                }

            }
            }
        }
    }
    else{
        int i = 0;
        while (x->key[i] < k)
        {
            i++;
        }
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
        else
            Bplustree_bind(x, i, k);

        if (x->size == 0)
        {
            free(x);  
        }    
    }
}

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
    Btree_delete(y, k);
}
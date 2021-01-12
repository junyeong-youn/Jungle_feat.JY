#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <Windows.h>

#define M 5
#define t 3
typedef struct node
{
    bool leaf;
    int size;
    int key[M];
    struct node *p_arr[M + 1];
} node;
typedef struct Btree
{
    node *root;
} Btree;

void Btree_insert(Btree *T, int k);
void Btree_split(node *x, int i);
void Btree_insert_non(node *x, int k);
void Btree_delete(node* x, int k);
void Btree_bind(node *x, int i, int k);
void Btree_move(node *x, int i);
int find_predecessor(node *x);
int find_successor(node *x);

int main(void)
{

    Btree *T = malloc(sizeof(Btree));
    node *x = malloc(sizeof(node));
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
    Btree_delete(T->root, 4);

    printf("%d", T->root->key[0]);
    

    free(T);
    free(x);
    return 0;
}

void Btree_insert(Btree *T, int k)
{
    node *r = T->root;
    if ((r->size) == M)
    {
        node *s = malloc(sizeof(node));
        T->root = s;
        s->leaf = false;
        s->size = 0;
        s->p_arr[0] = r;
        Btree_split(s, 0);
        Btree_insert_non(s, k);
    }
    else
    {
        Btree_insert_non(r, k);
    }
}

void Btree_split(node *x, int i)
{
    node *z = malloc(sizeof(node));
    node *y = x->p_arr[i];
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
            z->p_arr[j] = y->p_arr[j + t];
        }
    }
    y->size = t - 1;
    for (int j = (x->size); i <= j; j--)
    {
        x->p_arr[j + 1] = x->p_arr[j];
    }
    x->p_arr[i + 1] = z;
    for (int j = (x->size); i <= j; j--)
    {
        x->key[j] = x->key[j - 1];
    }
    x->key[i] = y->key[t - 1];
    x->size = x->size + 1;
}

void Btree_insert_non(node *x, int k)
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
        if (x->p_arr[i]->size == M)
        {
            Btree_split(x, i);
            if (k > x->key[i])
            {
                i++;
            }
        }
        Btree_insert_non(x->p_arr[i], k);
    }
}
int find_predecessor(node *x)
{
    int predecessor = -1;
    while (!x->leaf)
    {
        x = x->p_arr[x->size];
    }
    predecessor = x->key[x->size - 1];
    return predecessor;
}

int find_successor(node *x)
{
    int successor = -1;
    while (!x->leaf)
    {
        x = x->p_arr[0];
    }
    successor = x->key[0];
    return successor;
}

void Btree_bind(node *x, int i, int k)
{
    node *y = x->p_arr[i];
    node *z = x->p_arr[i + 1];
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
        x->p_arr[j] = x->p_arr[j + 1];
    }
    x->size = x->size - 1;
    free(z);
    Btree_delete(y, k);
}

void Btree_delete(node* x, int k)
{
    if (x->leaf == true)
    {
        for (int i = 0; i <= x->size; i++)
        {
            if (x->key[i] == k)
            {
                for (int j = i;  j<= x->size - 2; j++)
                {
                    x->key[i] = x->key[i + 1];
                }
                x->size = x->size - 1;
                break;
            }
        }
    }
    else{
        int i = 0;
        while (x->key[i] < k)
        {
            i++;
        }
        if (x->key[i] == k)
        {
            if (x->p_arr[i]->size >= t)
            {
                int key_pre;
                key_pre = find_predecessor(x->p_arr[i]);
                x->key[i] = key_pre;
                Btree_delete(x->p_arr[i], key_pre);
            }

            if (x->p_arr[i + 1]->size >= t)
            {
                int key_next;
                key_next = find_successor(x->p_arr[i + 1]);
                x->key[i] = key_next;
                Btree_delete(x->p_arr[i + 1], key_next);
            }
            else
                Btree_bind(x, i, k);
        }

        if (x->p_arr[i]->size >= t)
        {
            Btree_delete(x->p_arr[i], k);
        }
        else
        {
            if ((x->p_arr[i + 1]->size >= t) && (x->p_arr[i]->size == t - 1))
            {
                x->p_arr[i]->key[t - 1] = x->key[i];
                x->key[i] = x->p_arr[i + 1]->key[0];
                x->p_arr[i]->p_arr[t] = x->p_arr[i + 1]->p_arr[0];

                x->p_arr[i]->size = x->p_arr[i]->size + 1;
                x->p_arr[i + 1]->size = x->p_arr[i + 1]->size - 1;

                for (int j = 0; x->p_arr[i + 1]->size - 1; j++)
                {
                    x->p_arr[i + 1]->key[j] = x->p_arr[i + 1]->key[j + 1];
                }
                for (int j = 0; x->p_arr[i + 1]->size; j++)
                {
                    x->p_arr[i + 1]->p_arr[j] = x->p_arr[i + 1]->p_arr[j + 1];
                }
                Btree_delete(x->p_arr[i], k);
            }

            if (i == x->size && x->p_arr[i - 1] >= t)
            {
                //오른쪽 키값 밀기
                for (int j = x->p_arr[i]->size - 1; j >= 0; j--)
                {
                    x->p_arr[i]->key[j + 1] = x->p_arr[i]->key[j];
                }
                //오른쪽 포인터값 밀기
                for (int j = x->p_arr[i]->size; j >= 0; j--)
                {
                    x->p_arr[i]->p_arr[j + 1] = x->p_arr[i]->p_arr[j];
                }
                //부모노드에 있는 값을 오른쪽으로 옮긴다
                x->p_arr[i]->key[0] = x->key[i - 1];
                //부모노드에 있는 값의 포인터를 왼쪽 끝 값의 포인터로 바꾼다.
                x->p_arr[i]->p_arr[0] = x->p_arr[i - 1]->p_arr[t - 1];
                //왼쪽 노드 끝값을 부모노드로 옮긴다.
                x->key[i - 1] = x->p_arr[i - 1]->key[t - 1];
                //사이즈 바꾸기
                x->p_arr[i]->size = x->p_arr[i]->size + 1;
                x->p_arr[i - 1]->size = x->p_arr[i - 1]->size - 1;
                Btree_delete(x->p_arr[i], k);
            }
            else
                Btree_bind(x, i, k);

            if (x->size == 0)
            {
                free(x);
            }
        }    
    }
}
#include <stdio.h> //입력은 다 구현했고, 삭제에서 인덱스가 이상해서 삭제 구현 못했습니다.
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#define M 3
#define t 2
#define TEST                                                                                                                                                                                                                                                                                                                     \
    {                                                                                                                                                                                                                                                                                                                            \
        10, 1, 3, 63, 82, 6, 31, 8, 2, 16, 11, 77, 96, 14, 92, 21, 47, 23, 24, 78, 26, 97, 15, 4, 30, 69, 37, 38, 76, 90, 17, 87, 53, 44, 45, 46, 9, 41, 54, 43, 22, 84, 58, 39, 65, 28, 42, 59, 99, 70, 71, 72, 29, 74, 73, 68, 13, 60, 79, 80, 81, 85, 83, 64, 94, 86, 66, 88, 93, 40, 91, 62, 25, 20, 36, 95, 19, 52, 55, 100 \
    }

typedef struct node
{
    bool leaf;
    int size;
    int data[M];
    int key[M];
    struct node *ptr[M + 1];
} node;

typedef struct Bptree
{
    node *root;
} Bptree;

void insertkey(Bptree *T, int key, int data);
void split(node *x, int index);
void nonfull_insert(node *x, int key, int data);
int find_index(node *cur, int key);
bool delete (Bptree *T, int key);
void print_for_exam(node *x);
bool bind_node(Bptree *T, node *x, int i);
void borrow_key_from_right(node *x, int i);
void borrow_key_from_left(node *x, int i);

int main()
{
    int arr[80] = TEST;
    Bptree *T = malloc(sizeof(Bptree));
    node *x = malloc(sizeof(node));
    x->leaf = true;
    x->size = 0;
    T->root = x;

    // insertkey(T, 10, 1);
    // insertkey(T, 20, 2);
    // insertkey(T, 30, 3);
    // insertkey(T, 40, 4);
    // insertkey(T, 50, 5);
    // insertkey(T, 60, 6);
    // insertkey(T, 70, 7);
    // insertkey(T, 80, 8);
    // insertkey(T, 90, 9);
    // insertkey(T, 100, 10);
    // insertkey(T, 110, 11);
    // insertkey(T, 120, 12);
    // delete (T, 50);

    // TEST 1 CASE

    insertkey(T, 4, 4000);
    insertkey(T, 1, 1000);
    insertkey(T, 3, 3000);
    insertkey(T, 2, 2000);

    // delete(T, 4);
    // delete(T, 2);
    // delete(T, 3);

    printf("---- TEST1 ----\n");
    print_for_exam(T->root);

    // // TEST 2 CASE
    for (int i = 2; i <= 100; i++)
    {
        insertkey(T, i, i * 1000);
    }
    // for (int i = 50; i <= 70; i++) {
    //     delete(T, i);
    // }

    // printf("\n\n\n\n\n\n");
    printf("---- TEST2 ----\n");
    print_for_exam(T->root);

    // // TEST3 CASE
    for (int i = 50; i <= 70; i++)
    {
        insertkey(T, i, i * 1000);
    }

    // for (int i = 0; i <80; i++) {
    //     delete(T, arr[i]);
    // }

    printf("\n\n\n\n\n\n");
    printf("---- TEST3 ----");
    print_for_exam(T->root);

    printf("프로그램이 정상적으로 종료 되었음.");
    system("pause");
    return 0;
}

///////////////////////////////////////////////////////////////////////
void print_for_exam(node *x)
{
    if (x->leaf)
    {
        for (int i = 0; i < x->size; i++)
        {
            printf("[%5d, %5d]\n", x->key[i], x->data[i]);
        }
    }
    else
    {
        for (int i = 0; i < x->size; i++)
        {
            print_for_exam(x->ptr[i]);
            printf("[%5d]\n", x->key[i]);
        }
        print_for_exam(x->ptr[x->size]);
    }
}

/////////////////////////////////////////////////////////////////////////
void insertkey(Bptree *T, int key, int data)
{
    node *r = T->root;
    if (r->size == M)
    {
        node *s = malloc(sizeof(node));
        T->root = s;
        s->leaf = false;
        s->size = 0;
        s->ptr[0] = r;
        split(s, 0);
        nonfull_insert(s, key, data);
    }
    else
    {
        nonfull_insert(r, key, data);
    }
}

void split(node *x, int index)
{
    node *right_ch = malloc(sizeof(node));
    node *left_ch = x->ptr[index];
    if (left_ch->leaf == true)
    {
        right_ch->leaf = left_ch->leaf;
        right_ch->size = t - 1;
        for (int j = 0; j <= t - 2; j++)
        {
            right_ch->key[j] = left_ch->key[j + t];
            right_ch->data[j] = left_ch->data[j + t];
        }
        left_ch->size = t;
        for (int j = x->size; j >= index + 1; j--)
        {
            x->ptr[j + 1] = x->ptr[j];
        }
        x->ptr[index + 1] = right_ch;
        for (int j = x->size - 1; j >= index; j--)
        {
            x->key[j + 1] = x->key[j];
            x->data[j + 1] = x->data[j];
        }
        x->key[index] = x->ptr[index + 1]->key[0];
        x->data[index] = x->ptr[index + 1]->data[0];

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
        for (int j = x->size; j >= index + 1; j--)
        {
            x->ptr[j + 1] = x->ptr[j];
        }
        x->ptr[index + 1] = right_ch;

        for (int j = x->size - 1; j >= index; j--)
        {
            x->key[j + 1] = x->key[j];
        }
        x->key[index] = left_ch->key[t - 1];
        x->size = x->size + 1;
    }
}

void nonfull_insert(node *x, int key, int data)
{
    int i = x->size - 1;
    if (x->leaf == true)
    {
        while (i >= 0 && key < x->key[i])
        {
            x->key[i + 1] = x->key[i];
            x->data[i + 1] = x->data[i];

            i--;
        }
        x->key[i + 1] = key;
        x->data[i + 1] = data;

        x->size = x->size + 1;
    }
    else
    {
        if (key > x->key[i])
        {
            i = x->size;
        }
        else
        {
            while (i >= 0 && key < x->key[i])
            {
                i--;
            }
            i = i + 1;
        }
        if (x->ptr[i]->size == M)
        {
            split(x, i);
            if (key > x->key[i])
            {
                i++;
            }
        }
        nonfull_insert(x->ptr[i], key, data);
    }
}

// int find_index(node *x, int key)
// {
//     int index = x->size;
//     while (0 < index && key <= x->key[index - 1])
//     {
//         index--;
//     }
//     return index;
// }

// bool delete (Bptree *T, int key)
// {
//     printf("start delete\n");
//     node *x = T->root;
//     int i = 0;
//     while (!x->leaf)
//     {
//         i = find_index(x, key);
//         if (x->ptr[i]->size < t)
//         {
//             printf("underflow\n");
//             if (i < x->size)
//             {
//                 if (x->ptr[i + 1]->size >= t)
//                 {
//                     printf("borrow right\n");
//                     borrow_key_from_right(x, i);
//                 }
//                 else
//                 {
//                     printf("bind\n");
//                     if (bind_node(T, x, i))
//                     {
//                         x = T->root;
//                         continue;
//                     }
//                 }
//             }
//             else
//             {
//                 if (x->ptr[i - 1]->size >= t)
//                 {
//                     printf("borrow left\n");
//                     borrow_key_from_left(x, i - 1);
//                 }
//                 else
//                 {
//                     i -= 1;
//                     printf("bind\n");
//                     if (bind_node(T, x, i))
//                     {
//                         x = T->root;
//                         continue;
//                     }
//                 }
//             }
//         }
//         x = x->ptr[i];
//     }

//     i = find_index(x, key);
//     if (i < x->size && x->key[i] == key)
//     {
//         for (int j = i; j < x->size - 1; i++)
//         {
//             x->key[i] = x->key[i + 1];
//             x->data[i] = x->data[i + 1];
//         }
//         x->size -= 1;
//     }
//     else
//     {
//         return false;
//     }
//     return true;
// }

// bool bind_node(Bptree *T, node *x, int i)
// {

//     node *left_child = x->ptr[i];
//     node *right_child = x->ptr[i + 1];
//     int left_size = left_child->size;
//     int right_size = right_child->size;

//     if (!left_child->leaf)
//     {

//         left_child->key[left_size] = x->key[i];
//         left_child->data[left_size] = x->data[i];

//         for (int i = 0; i < right_size; i++)
//         {
//             left_child->key[left_size + 1 + i] = right_child->key[i];
//             left_child->data[left_size + 1 + i] = right_child->data[i];
//         }
//         for (int i = 0; i < right_size + 1; i++)
//         {
//             left_child->ptr[left_size + 1 + i] = right_child->ptr[i];
//         }

//         left_child->size = left_size + 1 + right_size;
//     }
//     else
//     {
//         for (int i = 0; i < right_size; i++)
//         {
//             left_child->key[left_size + i] = right_child->key[i];
//             left_child->data[left_size + i] = right_child->data[i];
//         }
//         for (int i = 0; i < right_size; i++)
//         {
//             left_child->ptr[left_size + i] = right_child->ptr[i];
//         }
//         left_child->size = left_size + right_size;
//     }
//     for (int j = i; j < x->size - 1; j++)
//     {
//         x->key[j] = x->key[j + 1];
//         x->data[j] = x->data[j + 1];
//     }
//     for (int j = i + 1; j < x->size; j++)
//     {
//         x->ptr[j] = x->ptr[j + 1];
//     }
//     x->size -= 1;

//     free(right_child);

//     if (x->size == 0)
//     {
//         free(T->root);
//         T->root = left_child;
//         return true;
//     }
//     return false;
// }

// void borrow_key_from_right(node *x, int index)
// {
//     node *left_child = x->ptr[index];
//     node *right_child = x->ptr[index + 1];

//     if (!left_child->leaf)
//     {
//         left_child->key[left_child->size] = x->key[index];
//         left_child->data[left_child->size] = x->data[index];

//         left_child->size += 1;

//         x->key[index] = right_child->key[0];
//         x->data[index] = right_child->data[0];

//         left_child->ptr[left_child->size] = right_child->ptr[0];
//         right_child->size -= 1;

//         for (int i = 0; i < right_child->size; i++)
//         {
//             right_child->key[i] = right_child->key[i + 1];
//             right_child->data[i] = right_child->data[i + 1];
//         }
//         for (int i = 0; i < right_child->size + 1; i++)
//         {
//             right_child->ptr[i] = right_child->ptr[i + 1];
//         }
//     }
//     else
//     {
//         left_child->key[left_child->size] = right_child->key[0];
//         left_child->data[left_child->size] = right_child->data[0];

//         left_child->ptr[left_child->size] = right_child->ptr[0];
//         left_child->size += 1;
//         x->key[index] = right_child->key[0];
//         x->data[index] = right_child->data[0];

//         right_child->size -= 1;
//         for (int i = 0; i < right_child->size; i++)
//         {
//             right_child->key[i] = right_child->key[i + 1];
//             right_child->data[i] = right_child->data[i + 1];
//         }
//         for (int i = 0; i < right_child->size; i++)
//         {
//             right_child->ptr[i] = right_child->ptr[i + 1];
//         }
//     }
// }

// void borrow_key_from_left(node *parent, int index)
// {
//     node *left_child = parent->ptr[index];
//     node *right_child = parent->ptr[index + 1];

//     for (int i = right_child->size; 0 < i; i--)
//     {
//         right_child->key[i] = right_child->key[i - 1];
//         right_child->data[i] = right_child->data[i - 1];
//     }
//     if (!right_child->leaf)
//     {
//         for (int i = right_child->size + 1; 0 < i; i--)
//         {
//             right_child->ptr[i] = right_child->ptr[i - 1];
//         }
//         right_child->key[0] = parent->key[index];
//         right_child->data[0] = parent->data[index];
//         right_child->size += 1;
//         parent->key[index] = left_child->key[left_child->size - 1];
//         parent->data[index] = left_child->data[left_child->size - 1];
//         right_child->ptr[0] = left_child->ptr[left_child->size];
//     }
//     else
//     {
//         for (int i = right_child->size; 0 < i; i--)
//         {
//             right_child->ptr[i] = right_child->ptr[i - 1];
//         }
//         right_child->key[0] = left_child->key[left_child->size - 1];
//         right_child->data[0] = left_child->data[left_child->size - 1];
//         right_child->ptr[0] = left_child->ptr[left_child->size - 1];
//         parent->key[index] = left_child->key[left_child->size - 2];
//         parent->data[index] = left_child->data[left_child->size - 2];
//     }

//     left_child->size -= 1;
// }
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node *pt;
    int key;
} node;
void add(node* x, node* end, int addkey);
void delete(node* x, int delkey);


void add(node* x, node* end, int addkey){
    node* add = malloc(sizeof(node));
    x = end->pt;
    add->key = addkey;
    add->pt = x->pt;
    x->pt = add;
    end->pt = add;
}
void delete(node* x, int delkey){
    while(x != NULL){
        if (x->pt->key == delkey){
            x->pt = x->pt->pt;
            break;
        }
        x = x->pt;
    }
}
int main(){
    
    node* start = malloc(sizeof(node));
    node* end = malloc(sizeof(node));

    start->pt = NULL;
    end->pt = start;
    
    add(start, end, 20);
    add(start, end, 30);
    add(start, end, 204);
    add(start, end, 24);
    delete(start, 30);
    

    node* x = start->pt;

    while(x != NULL){
        printf("%d\n", x->key);
        x = x->pt;
    }
  
    return 0;
    
}

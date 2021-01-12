#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node *pt;
    int key;
} node;
void add(node* x, int addkey);
void delete(node* x, int delkey);


void add(node* x, int addkey){
    node* add = malloc(sizeof(node));
    add->key = addkey;
    add->pt = x->pt;
    x->pt = add;
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
   
    start->pt = NULL;
    
    add(start, 20);
    add(start, 30);
    add(start, 204);
    add(start, 24);
    delete(start, 30);
    

    node* x = start->pt;

    while(x != NULL){
        printf("%d\n", x->key);
        x = x->pt;
    }
  
    return 0;
    
}

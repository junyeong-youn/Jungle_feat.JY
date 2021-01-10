#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#define wait_time 2000
#define T 3
#define M (T*2)-1


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

// Btree ���� �Լ�

Btree* create_Btree(void);
void free_all_node(node* cur);
bool delete_Btree(Btree* bt);
void dfs(node* cur, int cnt);
void print_tree(node* cur, int cnt);
bool search_key(Btree* bt, int key);
bool insert_key(Btree* bt, int key);
bool delete_key(Btree* bt, int key);


// ���α׷� ���� ���� �Լ�

int get_key(char* action);
int select_menu(void);
void exit_program(void);
void start_program();



int main(void) {
	start_program();
	return true;
}


// �׽�Ʈ �Լ�


// ��� ���� �Լ�


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



// Btree ���� �Լ�

void free_all_node(node* cur) {
	if (!cur->leaf) {
		for (int i = 0; i < cur->size+1; i++) {
			free_all_node(cur->p_arr[i]);
		}
	}
	delete_node(cur);
}

void dfs(node* cur, int cnt) {
	if (cur->leaf) {
		for (int i = 0; i < cnt; i++) {
			printf("--------------------|");
		}
		for (int i = 0; i < cur->size; i++) {
			printf("%4d", cur->keys[i]);
		}
		printf("\n");
	}
	else {
		for (int i = 0; i < cur->size; i++) {
			if (!cur->isLeaf) {
				dfs(cur->p_arr[i], cnt + 1);
			}
			for (int i = 0; i < cnt; i++) {
				printf("--------------------|");
			}
			printf("%4d            \n", cur->keys[i]);
		}
		dfs(cur->p_arr[cur->size], cnt + 1);
	}
}

void print_tree(node* cur, int cnt) {
	dfs(cur, cnt);
	printf("\n");
}

bool search_key(Btree* bt, int key) {
	node* cur = bt->root;
	int index = find_index(cur, key);
	while (index <= cur->size) {
		if (cur->keys[index] == key) {
			printf("\n----- key \"%d\" exist in tree.  -----\n\n", key);
			return true;
		}

		if (cur->isLeaf) break;

		cur = cur->p_arr[index];
		index = find_index(cur, key);
	}
	printf("\n----- key \"%d\" does not exist in tree. -----\n\n", key);
	return false;
}


// ���α׷� ���� ���� �Լ�

int get_key(char* action) {
	int key = 0;
	int cnt = 0;
	while (true) {
		printf("   %s�� �����͸� �Է��ϼ���      : ", action);
		scanf_s("%d", &key);
		cnt = 0;
		while (getchar() != '\n') {	// �Է� ���� ����
			cnt++;
		}
		if (cnt > 0) {	// �Է� ���ۿ� ���� ���� ���� �־��ٸ� �ٽ� �Է�
			system("cls");
			printf("   ���ڸ� ��Ȯ�ϰ� �Է����ּ���(���鵵 X)\n");
			continue;
		}
		break;
	}
	return key;
}

int select_menu(void) {
	int menu = 0;
	char cnt = 0;	// �Է� ���� Ȯ���� ���� ����
	while (true) {
		cnt = 0;	// cnt �ʱ�ȭ
		system("cls");
		printf("   --------------------------------------------------------\n");
		printf("   --------------------------------------------------------\n");
		printf("   --------                                        --------\n");
		printf("   --------                                        --------\n");
		printf("   --------             B Ʈ�� �����ϱ�            --------\n");
		printf("   --------                                        --------\n");
		printf("   --------                                        --------\n");
		printf("   --------------------------------------------------------\n");
		printf("   --------------------------------------------------------\n");
		printf("   ---------                                       --------\n");
		printf("   ---------             1. Ʈ�� ��ȸ              --------\n");
		printf("   ---------             2. ������ ��ȸ            --------\n");
		printf("   ---------             3. ������ ����            --------\n");
		printf("   ---------             4. ������ ����            --------\n");
		printf("   ---------             0. ���α׷� ����          --------\n");
		printf("   ---------                                       --------\n");
		printf("   --------------------------------------------------------\n");
		printf("   --------------------------------------------------------\n");
		printf("   ---------<<           �޴� ���� :              >>-------");
		printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		// �޴� ���� �� �Է�
		scanf_s("%d", &menu);
		// �Է� ���� ����
		while (getchar() != '\n') {
			cnt++;
		}
		if (cnt > 0) {	// �Է� ���ۿ� ���� ���� �־��ٸ� 
			printf("       �޴��� �ش��ϴ� ���� �ϳ��� �Է��ϼ���(���鵵 X)\n");
			system("pause");
			continue;	// �ݺ��� �ٽ� ����
		}
		else break;		// �Է� ���ۿ� ���� ���� �������� break
	}
	return menu;		// �ݺ������� ����� �Է¹��� menu �� ��ȯ
}

void exit_program(void) {
	printf("   --------------------------------------------------------\n");
	printf("   -----------   ��� �� ���α׷��� �����մϴ�  -----------\n");
	printf("   --------------------------------------------------------\n");
}

void start_program() {
	Btree* T = malloc(sizeof(Btree));
    node* x = malloc(sizeof(node));
    x->leaf = true;
    x->size = 0;
    T->root = x;

	int key = 0;
	while (true) {
		switch (select_menu()) {
			// �Է� ���� 1�� ��� ���� tree�� ����Ѵ�
		case 1:
			system("cls");
			printf(" [Ʈ���� ���� ����] \n");
			print_tree(bt->root, 0);
			break;
			// �Է� ���� 2�� ��� �����͸� �޾Ƽ� Ʈ������ ��ȸ�Ѵ�
		case 2:
			system("cls");
			key = get_key("��ȸ");
			printf(" [Ʈ���� Ȯ��] \n");
			search_key(bt, key);
			print_tree(bt->root, 0);
			break;
			// �Է� ���� 3�� ��� �����͸� �޾Ƽ� Ʈ���� �����Ѵ�
		case 3:
			system("cls");
			key = get_key("����");
			printf("\n [���� �� Ʈ��] \n");
			print_tree(bt->root, 0);
			insert_key(bt, key);
			printf("\n [���� �� Ʈ��] \n");
			print_tree(bt->root, 0);
			break;
			//�Է� ���� 4�� ��� �����͸� �޾Ƽ� Ʈ������ �����Ѵ�
		case 4:
			system("cls");
			printf("\n [���� �� Ʈ��] \n");
			print_tree(bt->root, 0);
			key = get_key("����");
			delete_key(bt, key);
			printf("\n [���� �� Ʈ��] \n");
			print_tree(bt->root, 0);
			break;
			//�Է� ���� 0�� ��� ���α׷��� �����Ѵ�
		case 0:
			exit_program();
			delete_Btree(bt);
			Sleep(wait_time * 2);
			exit(1);		// ���α׷� ����
		default:	// �� �ܿ� �Է��� ��� ���� �޽��� ��� �ٽ� �޴� �Է�
			printf("       �޴��� �߸� �Է��ϼ̽��ϴ�\n");
		}
		system("pause");
	}
}


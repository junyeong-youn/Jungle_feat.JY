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

// Btree 관련 함수

Btree* create_Btree(void);
void free_all_node(node* cur);
bool delete_Btree(Btree* bt);
void dfs(node* cur, int cnt);
void print_tree(node* cur, int cnt);
bool search_key(Btree* bt, int key);
bool insert_key(Btree* bt, int key);
bool delete_key(Btree* bt, int key);


// 프로그램 실행 관련 함수

int get_key(char* action);
int select_menu(void);
void exit_program(void);
void start_program();



int main(void) {
	start_program();
	return true;
}


// 테스트 함수


// 노드 관련 함수


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



// Btree 관련 함수

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


// 프로그램 실행 관련 함수

int get_key(char* action) {
	int key = 0;
	int cnt = 0;
	while (true) {
		printf("   %s할 데이터를 입력하세요      : ", action);
		scanf_s("%d", &key);
		cnt = 0;
		while (getchar() != '\n') {	// 입력 버퍼 비우기
			cnt++;
		}
		if (cnt > 0) {	// 입력 버퍼에 남은 값이 남아 있었다면 다시 입력
			system("cls");
			printf("   숫자를 정확하게 입력해주세요(공백도 X)\n");
			continue;
		}
		break;
	}
	return key;
}

int select_menu(void) {
	int menu = 0;
	char cnt = 0;	// 입력 버퍼 확인을 위한 변수
	while (true) {
		cnt = 0;	// cnt 초기화
		system("cls");
		printf("   --------------------------------------------------------\n");
		printf("   --------------------------------------------------------\n");
		printf("   --------                                        --------\n");
		printf("   --------                                        --------\n");
		printf("   --------             B 트리 구현하기            --------\n");
		printf("   --------                                        --------\n");
		printf("   --------                                        --------\n");
		printf("   --------------------------------------------------------\n");
		printf("   --------------------------------------------------------\n");
		printf("   ---------                                       --------\n");
		printf("   ---------             1. 트리 조회              --------\n");
		printf("   ---------             2. 데이터 조회            --------\n");
		printf("   ---------             3. 데이터 삽입            --------\n");
		printf("   ---------             4. 데이터 삭제            --------\n");
		printf("   ---------             0. 프로그램 종료          --------\n");
		printf("   ---------                                       --------\n");
		printf("   --------------------------------------------------------\n");
		printf("   --------------------------------------------------------\n");
		printf("   ---------<<           메뉴 선택 :              >>-------");
		printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		// 메뉴 선택 값 입력
		scanf_s("%d", &menu);
		// 입력 버퍼 비우기
		while (getchar() != '\n') {
			cnt++;
		}
		if (cnt > 0) {	// 입력 버퍼에 남은 값이 있었다면 
			printf("       메뉴에 해당하는 숫자 하나만 입력하세요(공백도 X)\n");
			system("pause");
			continue;	// 반복문 다시 시작
		}
		else break;		// 입력 버퍼에 남은 값이 없었으면 break
	}
	return menu;		// 반복문에서 벗어나면 입력받은 menu 값 반환
}

void exit_program(void) {
	printf("   --------------------------------------------------------\n");
	printf("   -----------   잠시 후 프로그램을 종료합니다  -----------\n");
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
			// 입력 값이 1인 경우 현재 tree를 출력한다
		case 1:
			system("cls");
			printf(" [트리의 현재 상태] \n");
			print_tree(bt->root, 0);
			break;
			// 입력 값이 2인 경우 데이터를 받아서 트리에서 조회한다
		case 2:
			system("cls");
			key = get_key("조회");
			printf(" [트리의 확인] \n");
			search_key(bt, key);
			print_tree(bt->root, 0);
			break;
			// 입력 값이 3인 경우 데이터를 받아서 트리에 삽입한다
		case 3:
			system("cls");
			key = get_key("삽입");
			printf("\n [삽입 전 트리] \n");
			print_tree(bt->root, 0);
			insert_key(bt, key);
			printf("\n [삽입 후 트리] \n");
			print_tree(bt->root, 0);
			break;
			//입력 값이 4인 경우 데이터를 받아서 트리에서 삭제한다
		case 4:
			system("cls");
			printf("\n [삭제 전 트리] \n");
			print_tree(bt->root, 0);
			key = get_key("삭제");
			delete_key(bt, key);
			printf("\n [삭제 후 트리] \n");
			print_tree(bt->root, 0);
			break;
			//입력 값이 0인 경우 프로그램을 종료한다
		case 0:
			exit_program();
			delete_Btree(bt);
			Sleep(wait_time * 2);
			exit(1);		// 프로그램 종료
		default:	// 그 외에 입력인 경우 에러 메시지 출력 다시 메뉴 입력
			printf("       메뉴를 잘못 입력하셨습니다\n");
		}
		system("pause");
	}
}


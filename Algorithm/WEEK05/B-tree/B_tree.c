#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#define wait_time 2000
#define M 5
#define T M/2
typedef struct node {				// 노드 구조체 정의
	bool isLeaf;					// 노드가 리프인지 확인
	int size;						// 노드에 저장된 키 개수
	int keys[M];					// 노드에 저장된 키 배열
	struct node* p_arr[M + 1];	// 노드에 저장된 포인터 배열
} node;
typedef struct Btree {				// B트리 구조체 정의
	node* root;						// B트리의 루트 주소
} Btree;
// Btree 관련 함수
Btree* create_Btree(void);
bool delete_Btree(Btree* bt);
// 노드 관련 함수
node *create_node(void);
void split_node(node* parent, int index);
// 프로그램 실행 관련 함수
int get_key(char* action);
int select_menu(void);
void print_tree(void);
bool search_key(void);
void insert_key(Btree* bt);
void delete_key(void);
void exit_program(void);
void start_program(Btree* bt);
int main() {
	Btree* bt = create_Btree();
	start_program(bt);
	delete_Btree(bt);
}

// Btree 관련 함수
Btree* create_Btree(void) {
	Btree* t = malloc(sizeof(Btree));
	t->root = create_node();
	t->root->isLeaf = true;
	t->root->size = 0;
	return t;
}
bool delete_Btree(Btree* bt) {
	free(bt->root);
	free(bt);
	return true;
}
// 노드 관련 함수
node* create_node(void) {
	node* new_node = malloc(sizeof(node));
	return new_node;
}
void split_node(node* parent, int index) {
	// 오른쪽 자식이 될 노드를 생성한다
	node* right_child = create_node();
	// 현재 노드는 왼쪽 자식이 된다
	node* left_child = parent->p_arr[index];
	// 오른쪽 자식의 리프노드 여부는 왼쪽 자식의 값과 동일하다
	right_child->isLeaf = left_child->isLeaf;
	// 오른쪽 자식의 크기는 M/2 or T 가 되고
	right_child->size = T;
	// 왼쪽 자식의 중간값 오른쪽에 있는 값을 오른쪽 노드로 옮긴다
	for (int i = 0; i < T; i++) {
		right_child->keys[i] = left_child->keys[i + T + 1];
	}
	if (!(left_child->isLeaf)) {
		for (int i = 0; i <= T; i++) {
			right_child->p_arr[i] = left_child->p_arr[i + T + 1];
		}
	}
	left_child->size = T;
	for (int i = parent->size - 1; i > index; i--) {
		parent->keys[i] = parent->keys[i - 1];
	}
	for (int i = parent->size; i > index ; i--) {
		parent->p_arr[i] = parent->p_arr[i - 1];
	}
	parent->p_arr[index + 1] = right_child;
	parent->keys[index] = left_child->keys[T];
	parent->p_arr[index] = left_child->p_arr[T];
	parent->size += 1;
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
void print_tree(void) {
	printf("-----------------------------\n");
	printf("-----------------------------\n");
	printf("---------- TREE -------------\n");
	printf("-----------------------------\n");
	printf("-----------------------------\n");
}
bool search_key(void) {
	char action[5] = "조회";
	int key = get_key(action);
	printf("       %d %s\n", key, action);
}
void insert_key(Btree *bt) {
	char action[5] = "삽입";
	int key = get_key(action);
	node* cur = bt->root;
	// 루트의 크기가 M이라면 (루트 노드가 꽉 찼다면)
	if (cur->size == M) {
		// 새 노드를 하나 생성한다
		node* new_root = create_node();
		// 새 노드를 Btree의 새 루트로 저장한다
		bt->root = new_root;
		// 새 루트의 값을 초기화 해주고 포인터의 맨 앞에 이전 루트 주소를 저장한다
		new_root->isLeaf = false;
		new_root->size = 0;
		new_root->p_arr[0] = cur;
		// 새 루트의 포인터 배열의 0 번째로 저장한 이전 루트 노드를 분할한다
		split_node(new_root, 0);
		// 현재 노드를 new_root로 갱신한다
		cur = new_root;
	}
	// 값의 삽입은 무조건 리프노드에 하기 때문에
	// 리프노드까지 내려간다
	while (!cur->isLeaf) {
		// 키 값과 현재 노드에 있는 값을 비교하여 다음에 방문해야하는 노드 주소를 구한다
		int i = cur->size;
		while (i > 0 && key < cur->keys[i-1]) {
			i--;
		}
		// 다음에 방문해야 하는 노드가 꽉 차있으면
		if (cur->p_arr[i]->size == M) {
			// 다음에 방문할 노드를 분할한다
			split_node(cur, i);
			// 분할하면서 현재 노드의 키 배열의 i번째 값이 변경되는데
			// 이 때 변경된 값보다 삽입할 키 값이 크면 다음 노드를 변경한다
			if (key > cur->keys[i]) {
				i++;
			}
		}
		// 방문 노드를 다음 노드로 변경한다
		cur = cur->p_arr[i];
	}
	// 리프노드에 도착한 후 K를 삽입
	int i = cur->size;
	while (i > 0 && key < cur->keys[i-1]) {
		cur->keys[i] = cur->keys[i-1];
		i--;
	}
	cur->keys[i] = key;
	cur->size += 1;
}
void delete_key(void) {
	char action[5] = "삭제";
	int key = get_key(action);
	printf("       %d %s\n", key, action);
}
void exit_program(void) {
	printf("   --------------------------------------------------------\n");
	printf("   -----------   잠시 후 프로그램을 종료합니다  -----------\n");
	printf("   --------------------------------------------------------\n");
}
void start_program(Btree* bt) {
	while (true) {
		switch (select_menu()) {
			// 입력 값이 1인 경우 현재 tree를 출력한다
		case 1:
			system("cls");
			print_tree();
			break;
			// 입력 값이 2인 경우 데이터를 받아서 트리에서 조회한다
		case 2:
			system("cls");
			search_key();
			break;
			// 입력 값이 3인 경우 데이터를 받아서 트리에 삽입한다
		case 3:
			system("cls");
			insert_key(bt);
			break;
			//입력 값이 4인 경우 데이터를 받아서 트리에서 삭제한다
		case 4:
			system("cls");
			delete_key();
			break;
			//입력 값이 0인 경우 프로그램을 종료한다
		case 0:
			exit_program();
			Sleep(wait_time * 2);
			exit(1);		// 프로그램 종료
		default:	// 그 외에 입력인 경우 에러 메시지 출력 다시 메뉴 입력
			printf("       메뉴를 잘못 입력하셨습니다\n");
		}
		system("pause");
	}
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>

#define wait_time 2000
#define T 3
#define M (T*2)-1
#define testcase 100
#define random_cnt 200

typedef struct node {	
	bool isLeaf;					// 노드가 리프인지 확인
	int size;						// 노드에 저장된 키 개수
	int keys[M];					// 노드에 저장된 키 배열
	struct node* prev;				// 이전 노드가 저장된 배열
	struct node* next;				// 다음 노드가 저장된 배열
	struct node* p_arr[M + 1];		// 노드에 저장된 포인터 배열
} node;

typedef struct BPlusTree {			// B+트리 구조체 정의
	node* root;						// B+트리의 루트 주소
	node* head;						// 정렬 데이터의 맨 앞 주소
	node* tail;						// 정렬 데이터의 맨 뒤 주소
} BPtree;

// 테스트 함수

void test_insert_key_data(BPtree* bpt);
void test_delete(BPtree* bpt);
void test_random(BPtree* bpt);

// 노드 관련 함수

node* create_node(bool isLeaf);
int find_index(node* cur, int key);
void split_node(BPtree* bpt, node* parent, int index);
bool bind_node(BPtree* bpt, node* parent, int index);
void borrow_key_from_right(node* parent, int index);
void borrow_key_from_left(node* parent, int index);
void delete_node(node*);

// BPtree 관련 함수

BPtree* create_BPtree(void);
void free_all_node(node* cur);
bool delete_BPtree(BPtree* bpt);
void print_by_dfs(node* cur, int cnt);
void print_tree(node* cur, int cnt);
void print_data_ascending(node* cur);
void print_data_descending(node* cur);
bool search_key(BPtree* bpt, int key);
bool insert_key_data(BPtree* bpt, int key, int* data);
bool delete_key(BPtree* bpt, int key);

// 프로그램 실행 관련 함수

int get_key(char* action);
int* get_data(char* action);
int select_menu(void);
void exit_program(void);
void start_program();


// 메인 함수

int main(void) {
	BPtree* bpt = create_BPtree();
	//test_random(bpt);
	//delete_BPtree(bpt);
	start_program();
	return true;
}

// 테스트 함수

void test_insert_key_data(BPtree* bpt) {
	int* test_arr[1000];

	for (int i = 1; i < 40; i++) {
		int key = i * 10;
		test_arr[key] = (int*)malloc(sizeof(int));
		*test_arr[key] = key;
		insert_key_data(bpt, key, test_arr[key]);
		print_tree(bpt->root, 0);
		print_data_ascending(bpt->head);
		print_data_descending(bpt->tail);
	}

	for (int i = 1; i < 40; i++) {
		int key = (i * 10) + 5; 
		test_arr[key] = (int*)malloc(sizeof(int));
		*test_arr[key] = key;
		insert_key_data(bpt, key, test_arr[key]);
		print_tree(bpt->root, 0);
		print_data_ascending(bpt->head);
		print_data_descending(bpt->tail);
	}

	print_tree(bpt->root, 0);
}

void test_delete(BPtree* bpt) {
	print_tree(bpt->root, 0);
	delete_key(bpt, 40);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 50);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 60);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 130);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 280);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 290);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 210);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 150);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 160);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 170);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 180);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 220);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 230);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 240);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 75);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 85);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 95);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 105);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 200);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 140);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 190);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 270);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 250);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 260);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 115);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 10);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 20);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 30);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 125);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 135);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 315);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 325);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 365);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 375);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 145);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 155);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 300);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 310);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 345);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 355);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 295);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 305);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 385);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 395);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 340);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 350);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 100);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 110);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 120);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 215);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 225);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 235);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 245);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 360);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 370);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 70);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 80);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 90);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 255);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 380);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 390);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 15);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 25);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 35);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 45);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 320);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 330);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 335);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 55);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 65);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 165);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 175);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 185);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 195);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 205);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 265);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 275);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
	delete_key(bpt, 285);
	print_tree(bpt->root, 0);
	print_data_ascending(bpt->head);
	print_data_descending(bpt->tail);
}

void test_random(BPtree* bpt) {
	int key_arr1[testcase];
	int key_arr2[testcase];
	srand(time(NULL));

	// 값 생성
	for (int i = 0; i < testcase; i++) {
		key_arr1[i] = i + 1;
		key_arr2[i] = i + 1;
	}

	int cnt = random_cnt;
	int temp = 0;
	// 키 섞기
	while (cnt-- > 0) {
		int i = (rand() % testcase);
		int j = (rand() % testcase);

		temp = key_arr1[i];
		key_arr1[i] = key_arr1[j];
		key_arr1[j] = temp;

		i = (rand() % testcase);
		j = (rand() % testcase);

		temp = key_arr1[i];
		key_arr1[i] = key_arr1[j];
		key_arr1[j] = temp;
	}

	int key_arr1_cnt = 0;
	int key_arr2_cnt = 0;
	int index = 0;
	while (key_arr1_cnt < testcase && key_arr2_cnt < testcase) {
		index = (rand() % testcase);
		if (rand() % 2) {
			while (key_arr1[index] == -1) {
				index = (index + 1) % testcase;
			}

			int* data = (int*)malloc(sizeof(int*));
			*(data) = (rand() % testcase);
			insert_key_data(bpt, key_arr1[index], data);
			key_arr1[index] = -1;
			printf("%d 삽입 완료\n\n", index);
			key_arr1_cnt++;
		}
		else {
			while (key_arr2[index] == -1) {
				index = (index + 1) % testcase;
			}
			if (search_key(bpt, key_arr2[index])) {
				delete_key(bpt, key_arr2[index]);
				printf("%d 삭제 완료\n\n", index);
				key_arr2[index] = -1;
				key_arr2_cnt++;
			}
		}

		//print_tree(bpt->root, 0);
		//print_data_ascending(bpt->head);
		//print_data_descending(bpt->tail);
		printf("\n");
	}


	while (key_arr2_cnt < testcase) {
		index = (rand() % testcase);
		while (key_arr2[index] == -1) {
			index = (index + 1) % testcase;
		}
		delete_key(bpt, key_arr2[index]);
		printf("삭제 완료\n\n");
		key_arr2[index] = -1;
		key_arr2_cnt++;
		//print_tree(bpt->root, 0);
		//print_data_ascending(bpt->head);
		//print_data_descending(bpt->tail);
		printf("\n");
	}

	printf("테스트 완료\n\n");
	system("pause");
}


// 노드 관련 함수

node* create_node(bool isLeaf) {
	node* new_node = (node*)malloc(sizeof(node));
	new_node->isLeaf = isLeaf;
	new_node->size = 0;
	new_node->prev = NULL;
	new_node->next = NULL;
	for (int i = 0; i < M; i++) {
		new_node->keys[i] = 0;
	}
	for (int i = 0; i < M + 1; i++) {
		new_node->p_arr[i] = NULL;
	}
	return new_node;
}

int find_index(node* cur, int key) {
	int index = cur->size;
	while (0 < index && key <= cur->keys[index - 1]) {
		index--;
	}
	return index;
}

void split_node(BPtree* bpt, node* parent, int index) {

	node* left_child = parent->p_arr[index];
	node* right_child = create_node(left_child->isLeaf);

	// 오른쪽 자식의 크기는 T-1 이 되고
	right_child->size = T - 1;

	// 왼쪽 자식의 키 배열에서 중간값 오른쪽에 있는 값을 오른쪽 노드로 옮긴다
	for (int i = 0; i < T - 1; i++) {
		right_child->keys[i] = left_child->keys[i + T];
	}

	int end = T;

	if (left_child->isLeaf) {
		end -= 1;
	}

	for (int i = 0; i < end; i++) {
		right_child->p_arr[i] = left_child->p_arr[i + T];
	}
	// 왼쪽 노드에서 값과 포인터를 옮기고 남은 공간으로 크기를 조정한다
	left_child->size = T-1;

	if (left_child->isLeaf) {
		left_child->size += 1;
	}

	// 분할한 노드의 중간 값이 들어갈 자리를 만든다
	// 부모의 키 배열에서 자식 노드를 가리키던 위치 뒤의 값을 한 칸씩 뒤로 옮긴다
	for (int i = parent->size; i > index; i--) {
		parent->keys[i] = parent->keys[i - 1];
	}
	if (parent->size != 0) {
		// 부모의 포인터 배열에서 자식 노드를 가리키던 위치 뒤의 값을 한 칸씩 뒤로 옮긴다 
		for (int i = parent->size + 1; i > index; i--) {
			parent->p_arr[i] = parent->p_arr[i - 1];
		}
	}

	// 분할한 노드의 키 배열의 중간 값을 부모 노드에 저장한다
	if (left_child->isLeaf) {
		parent->keys[index] = left_child->keys[left_child->size - 1];
	}
	else {
		parent->keys[index] = left_child->keys[left_child->size];
	}

	// 중간 값이 들어간 위치의 오른쪽 포인터는 분할된 오른쪽 노드를 가리킨다
	// (왼쪽 포인터는 이미 분할한 왼쪽 노드를 가리키고 있다)
	parent->p_arr[index + 1] = right_child;

	// 부모에 키 값이 추가되었으니 크기를 1 증가한다
	parent->size += 1;

	if (right_child->isLeaf) {
		if (left_child->next != NULL) {
			left_child->next->prev = right_child;
			right_child->next = left_child->next;
		}
		else {
			bpt->tail = right_child;
		}
		left_child->next = right_child;
		right_child->prev = left_child;
	}
}

bool bind_node(BPtree* bpt, node* parent, int index) {

	node* left_child = parent->p_arr[index];
	node* right_child = parent->p_arr[index + 1];
	int left_size = left_child->size;
	int right_size = right_child->size;

	if(!left_child->isLeaf){
	// key를 왼쪽 자식에게 내려주고
		left_child->keys[left_size] = parent->keys[index];

		// 오른쪽 자식의 키 값을 왼쪽 자식으로 옮긴다
		// 여기서 값이 모두 왼쪽 자식으로 옮겨지고 오른쪽 자식은 가리킬 필요가 없어진다
		for (int i = 0; i < right_size; i++) {
			left_child->keys[left_size + 1 + i] = right_child->keys[i];
		}
		for (int i = 0; i < right_size + 1; i++) {
			left_child->p_arr[left_size + 1 + i] = right_child->p_arr[i];
		}

		// 왼쪽 자식의 키가 늘어났기 때문에 크기를 조정해준다
		left_child->size = left_size + 1 + right_size;
	}
	else {
		for (int i = 0; i < right_size; i++) {
			left_child->keys[left_size + i] = right_child->keys[i];
		}
		for (int i = 0; i < right_size; i++) {
			left_child->p_arr[left_size + i] = right_child->p_arr[i];
		}
		left_child->size = left_size + right_size;

		left_child->next = right_child->next;
		if (left_child->next != NULL) {
			left_child->next->prev = left_child;
		}
		else {
			bpt->tail = left_child;
		}
	}

	// 부모 노드에서 오른쪽 자식을 가리키던 포인터를 없애고 한 칸씩 앞으로 당긴다
	for (int i = index; i < parent->size - 1; i++) {
		parent->keys[i] = parent->keys[i + 1];
	}
	for (int i = index + 1; i < parent->size; i++) {
		parent->p_arr[i] = parent->p_arr[i + 1];
	}
	parent->size -= 1;

	// 오른쪽 노드는 저장된 값이 없기 때문에 메모리를 반환해준다
	delete_node(right_child);

	// 부모의 크기가 0 이면(루트일 때만 발생) 
	if (parent->size == 0) {
		free(bpt->root);
		bpt->root = left_child;
		return true;
	}
	return false;
}

void borrow_key_from_right(node* parent, int index) {
	node* left_child = parent->p_arr[index];
	node* right_child = parent->p_arr[index + 1];

	if (!left_child->isLeaf) {
		// 왼쪽 노드의 끝에 부모 노드의 현재 위치 값을 저장한다
		left_child->keys[left_child->size] = parent->keys[index];
		left_child->size += 1;

		// 부모 노드의 키 값은 오른쪽 자식의 맨 앞의 값을 가져온다
		parent->keys[index] = right_child->keys[0];
		left_child->p_arr[left_child->size] = right_child->p_arr[0];

		// 오른쪽 노드의 크기는 1 줄어든다
		right_child->size -= 1;

		// 오른쪽 노드의 맨 앞에서 뺀 키 값을 차례로 채워준다
		for (int i = 0; i < right_child->size; i++) {
			right_child->keys[i] = right_child->keys[i + 1];
		}
		for (int i = 0; i < right_child->size + 1; i++) {
			right_child->p_arr[i] = right_child->p_arr[i + 1];
		}
	}
	else {
		left_child->keys[left_child->size] = right_child->keys[0];
		left_child->p_arr[left_child->size] = right_child->p_arr[0];

		left_child->size += 1;

		parent->keys[index] = right_child->keys[0];

		// 오른쪽 노드의 크기는 1 줄어든다
		right_child->size -= 1;

		// 오른쪽 노드의 맨 앞에서 뺀 키 값을 차례로 채워준다
		for (int i = 0; i < right_child->size; i++) {
			right_child->keys[i] = right_child->keys[i + 1];
		}
		for (int i = 0; i < right_child->size; i++) {
			right_child->p_arr[i] = right_child->p_arr[i + 1];
		}
	}
}

void borrow_key_from_left(node* parent, int index) {
	node* left_child = parent->p_arr[index];
	node* right_child = parent->p_arr[index + 1];

	for (int i = right_child->size; 0 < i; i--) {
		right_child->keys[i] = right_child->keys[i - 1];
	}

	if (!right_child->isLeaf) {
		// 오른쪽 노드의 맨 앞에 포인터가 들어갈 자리를 만들기 위해 값을 한 칸씩 뒤로 옮긴다
		for (int i = right_child->size + 1; 0 < i; i--) {
			right_child->p_arr[i] = right_child->p_arr[i - 1];
		}

		// 오른쪽 노드의 맨 앞에 부모 노드의 현재 위치 값을 저장한다
		right_child->keys[0] = parent->keys[index];
		// 오른쪽 노드의 크기를 1 증가 시킨다
		right_child->size += 1;

		// 부모 노드의 키 값은 왼쪽 자식의 끝 값을 가져온다
		parent->keys[index] = left_child->keys[left_child->size - 1];
		right_child->p_arr[0] = left_child->p_arr[left_child->size];
	}
	else {
		for (int i = right_child->size; 0 < i; i--) {
			right_child->p_arr[i] = right_child->p_arr[i - 1];
		}
		right_child->keys[0] = left_child->keys[left_child->size - 1];
		right_child->p_arr[0] = left_child->p_arr[left_child->size - 1];
		parent->keys[index] = left_child->keys[left_child->size - 2];
	}

	left_child->size -= 1;
}

void delete_node(node* cur) {
	free(cur);
}


// BPtree 관련 함수

BPtree* create_BPtree(void) {
	BPtree* bpt = (BPtree*)malloc(sizeof(BPtree));
	bpt->root = create_node(true);
	bpt->head = bpt->root;
	bpt->tail = bpt->root;
	return bpt;
}

void free_all_node(node* cur) {
	if (!cur->isLeaf) {
		for (int i = 0; i < cur->size + 1; i++) {
			free_all_node(cur->p_arr[i]);
		}
	}
	for (int i = 0; i < cur->size; i++) {
		free_all_node(cur->p_arr[i]);
	}
	delete_node(cur);
}

bool delete_BPtree(BPtree* bpt) {
	free_all_node(bpt->root);
	free(bpt);
	return true;
}

void print_by_dfs(node* cur, int cnt) {
	if (cur->isLeaf) {
		for (int i = 0; i < cnt; i++) {
			printf("--------------------|");
		}
		for (int i = 0; i < cur->size; i++) {
			printf("[%4d, %4d]", cur->keys[i], *(int*)cur->p_arr[i]);
		}
		printf("\n");
	}
	else {
		for (int i = 0; i < cur->size; i++) {
			print_by_dfs(cur->p_arr[i], cnt + 1);
			for (int i = 0; i < cnt; i++) {
				printf("--------------------|");
			}
			printf("%4d            \n", cur->keys[i]);
		}
		print_by_dfs(cur->p_arr[cur->size], cnt + 1);
	}
}

void print_tree(node* cur, int cnt) {
	print_by_dfs(cur, cnt);
	printf("\n\n");
}

void print_data_ascending(node* cur) {
	while (cur->next != NULL) {
		for (int i = 0; i < cur->size; i++) {
			printf(" [%4d, %4d] ", cur->keys[i], *(int*)cur->p_arr[i]);
		}
		cur = cur->next;
	}
	for (int i = 0; i < cur->size; i++) {
		printf(" [%4d, %4d] ", cur->keys[i], *(int*)cur->p_arr[i]);
	}
	printf("\n\n");
}

void print_data_descending(node* cur) {
	while (cur->prev != NULL) {
		for (int i = cur->size - 1; 0 <= i; i--) {
			printf(" [%4d, %4d] ", cur->keys[i], *(int*)cur->p_arr[i]);
		}
		cur = cur->prev;
	}
	for (int i = cur->size - 1; 0 <= i; i--) {
		printf(" [%4d, %4d] ", cur->keys[i], *(int*)cur->p_arr[i]);
	}
	printf("\n\n");
}

bool search_key(BPtree* bpt, int key) {
	node* cur = bpt->root;
	int index = find_index(cur, key);
	while (!cur->isLeaf) {
		cur = cur->p_arr[index];
		index = find_index(cur, key);
	}
	if (index < cur->size && cur->keys[index] == key) {
		printf("\n----- [key \"%d\", data \"%d\"] exist in tree.  -----\n\n", key, *(cur->p_arr[index]));
		return true;
	}

	printf("\n----- key \"%d\" does not exist in tree. -----\n\n", key);
	return false;
}

bool insert_key_data(BPtree* bpt, int key, int* data) {
	node* cur = bpt->root;

	// 루트의 크기가 M이라면 (루트 노드가 꽉 찼다면)
	if (cur->size == M) {
		// 새 노드를 하나 생성한다
		node* new_root = create_node(false);
		// 새 노드를 BPtree의 새 루트로 저장한다
		bpt->root = new_root;
		// 새 루트의 값을 초기화 해주고 포인터의 맨 앞에 이전 루트 주소를 저장한다
		new_root->p_arr[0] = cur;
		// 새 루트의 포인터 배열의 0 번째로 저장한 이전 루트 노드를 분할한다
		split_node(bpt, new_root, 0);
		// 현재 노드를 new_root로 갱신한다
		cur = new_root;
	}

	// 값의 삽입은 무조건 리프노드에 하기 때문에
	// 리프 노드까지 내려간다
	while (!cur->isLeaf) {
		// 키 값과 현재 노드에 있는 값을 비교하여 다음에 방문해야하는 노드 주소를 구한다
		int i = cur->size;
		while (i > 0 && key < cur->keys[i - 1]) {
			i--;
		}
		// 다음에 방문해야 하는 노드가 꽉 차있으면
		if (cur->p_arr[i]->size == M) {
			// 다음에 방문할 노드를 분할한다
			split_node(bpt, cur, i);
			// 분할하면서 현재 노드의 키 배열의 i번째 값이 변경되는데
			// 이 때 변경된 값보다 삽입할 키 값이 크면 다음 노드를 변경한다  
			if (key > cur->keys[i]) {
				i++;
			}
		}
		// 방문 노드를 다음 노드로 변경한다
		cur = cur->p_arr[i];
	}

	// 리프노드에 도착한 후 키를 삽입
	int i = cur->size;
	while (i > 0 && key < cur->keys[i - 1]) {
		cur->keys[i] = cur->keys[i - 1];
		cur->p_arr[i] = cur->p_arr[i - 1];
		i--;
	}
	cur->keys[i] = key;
	cur->p_arr[i] = (void*)data;
	cur->size += 1;
	return true;
}

bool delete_key(BPtree* bpt, int key) {
	node* cur = bpt->root;
	int index = 0;
	// 방문한 노드가 리프 노드가 될 때 까지 반복문을 수행한다
	while (!cur->isLeaf) {
		index = find_index(cur, key);
		// 다음에 방문할 노드의 크기가 T보다 작다면
		if (cur->p_arr[index]->size < T) {
			// 다음 방문할 노드가 가장 오른쪽이 아니면
			if (index < cur->size) {
				// 다음 방문할 노드의 오른쪽 노드의 크기가 T보다 크거나 같으면
				if (cur->p_arr[index + 1]->size >= T) {
					// 오른쪽 노드에서 빌린다
					borrow_key_from_right(cur, index);
				}
				// 다음 방문할 노드의 형제(오른쪽)노드의 크기도 T보다 작으면
				else {
					if (bind_node(bpt, cur, index)) {
						cur = bpt->root;
						continue;
					}
				}
			}
			// 다음 방문할 노드가 가장 오른쪽이면
			else {
				// 다음 방문할 노드의 왼쪽 노드의 크기가 T보다 크거나 같으면
				if (cur->p_arr[index - 1]->size >= T) {
					// 왼쪽 노드에서 빌린다
					borrow_key_from_left(cur, index - 1);
				}
				// 다음 방문할 노드의 형제 왼쪽 노드의 크기도 T보다 작으면
				else {
					index -= 1;
					if (bind_node(bpt, cur, index)) {
						cur = bpt->root;
						continue;
					}
				}
			}
		}
		cur = cur->p_arr[index];
	}

	// 리프노드에 도착한 후 키가 있으면 삭제
	index = find_index(cur, key);
	if (index < cur->size && cur->keys[index] == key) {
		for (int i = index; i < cur->size - 1; i++) {
			cur->keys[i] = cur->keys[i + 1];
			cur->p_arr[i] = cur->p_arr[i + 1];
		}
		cur->size -= 1;
	}
	else {
		return false;
	}
	return true;
}


// 프로그램 실행 관련 함수

int get_key(char* action) {
	int key = 0;
	int cnt = 0;
	while (true) {
		printf("   %s할 키를 입력하세요      : ", action);
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

int* get_data(char* action) {
	int* data = (int*) malloc(sizeof(int));
	int cnt = 0;
	while (true) {
		printf("   %s할 데이터를 입력하세요      : ", action);
		scanf_s("%d", data);
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
	return data;
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
		printf("   --------             B+트리 구현하기            --------\n");
		printf("   --------                                        --------\n");
		printf("   --------                                        --------\n");
		printf("   --------------------------------------------------------\n");
		printf("   --------------------------------------------------------\n");
		printf("   ---------                                       --------\n");
		printf("   ---------             1. 트리 조회              --------\n");
		printf("   ---------             2. 키, 데이터 조회        --------\n");
		printf("   ---------             3. 키, 데이터 삽입        --------\n");
		printf("   ---------             4. 키 삭제                --------\n");
		printf("   ---------             5. 데이터 순차 조회       --------\n");
		printf("   ---------             6. 데이터 역순 조회       --------\n");
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
	BPtree* bpt = create_BPtree();
	//test_insert_key_data(bpt);
	//test_delete(bpt);
	int key = 0;
	int* data = NULL;
	while (true) {
		switch (select_menu()) {
			// 입력 값이 1인 경우 현재 tree를 출력한다
		case 1:
			system("cls");
			printf(" [트리의 현재 상태] \n");
			print_tree(bpt->root, 0);
			break;
			// 입력 값이 2인 경우 데이터를 받아서 트리에서 조회한다
		case 2:
			system("cls");
			key = get_key("조회");
			printf(" [트리의 확인] \n");
			search_key(bpt, key);
			print_tree(bpt->root, 0);
			break;
			// 입력 값이 3인 경우 데이터를 받아서 트리에 삽입한다
		case 3:
			system("cls");
			key = get_key("삽입");
			data = get_data("삽입");
			printf("\n [삽입 전 트리] \n");
			print_tree(bpt->root, 0);
			insert_key_data(bpt, key, data);
			printf("\n [삽입 후 트리] \n");
			print_tree(bpt->root, 0);
			break;
			//입력 값이 4인 경우 데이터를 받아서 트리에서 삭제한다
		case 4:
			system("cls");
			printf("\n [삭제 전 트리] \n");
			print_tree(bpt->root, 0);
			key = get_key("삭제");
			delete_key(bpt, key);
			printf("\n [삭제 후 트리] \n");
			print_tree(bpt->root, 0);
			break;
			// 입력 값이 5인 경우 정렬된 순서대로 데이터를 보여준다
		case 5:
			system("cls");
			printf("\n [트리 구조] \n");
			print_tree(bpt->root, 0);
			print_data_ascending(bpt->head);
			break;
			// 입력 값이 6인 경우 정렬된 순서대로 데이터를 보여준다
		case 6:
			system("cls");
			printf("\n [트리 구조] \n");
			print_tree(bpt->root, 0);
			print_data_descending(bpt->tail);
			break;
		case 0:
			exit_program();
			delete_BPtree(bpt);
			Sleep(wait_time * 2);
			exit(1);		// 프로그램 종료
		default:	// 그 외에 입력인 경우 에러 메시지 출력 다시 메뉴 입력
			printf("       메뉴를 잘못 입력하셨습니다\n");
		}
		system("pause");
	}
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#define wait_time 2000
#define M 5
#define T M/2
typedef struct node {				// ��� ����ü ����
	bool isLeaf;					// ��尡 �������� Ȯ��
	int size;						// ��忡 ����� Ű ����
	int keys[M];					// ��忡 ����� Ű �迭
	struct node* p_arr[M + 1];	// ��忡 ����� ������ �迭
} node;
typedef struct Btree {				// BƮ�� ����ü ����
	node* root;					// BƮ���� ��Ʈ �ּ�
} Btree;
// Btree ���� �Լ�
Btree* create_Btree(void);
bool delete_Btree(Btree* bt);
// ��� ���� �Լ�
node *create_node(void);
void split_node(node* parent, int index);
// ���α׷� ���� ���� �Լ�
int get_key(char* action);
int select_menu(void);
void print_tree(void);
bool search_key(void);
bool insert_key(Btree* bt, int key);
bool find_key(node* cur, int key);
bool delete_key(Btree* bt, int key);
void exit_program(void);
void start_program(Btree* bt);
int main() {
	Btree* bt = create_Btree();
	/*start_program(bt);*/
	delete_Btree(bt);
}

void test_insert(){
	Btree* bt = create_Btree();
	insert_key(bt, 10);
	insert_key(bt, 11);
	insert_key(bt, 12);
	insert_key(bt, 13);
	insert_key(bt, 14);
	insert_key(bt, 22);
	insert_key(bt, 23);
	insert_key(bt, 4);
	insert_key(bt, 5);
	insert_key(bt, 6);
	insert_key(bt, 15);
	insert_key(bt, 21);
	insert_key(bt, 16);
	insert_key(bt, 17);
	insert_key(bt, 1);
	insert_key(bt, 33);
	insert_key(bt, 34);
	insert_key(bt, 7);
	insert_key(bt, 30);
	insert_key(bt, 31);
	insert_key(bt, 32);
	insert_key(bt, 9);
	insert_key(bt, 18);
	insert_key(bt, 19);
	insert_key(bt, 35);
	insert_key(bt, 36);
	insert_key(bt, 24);
	insert_key(bt, 25);
	insert_key(bt, 29);
	insert_key(bt, 2);
	insert_key(bt, 3);
	insert_key(bt, 8);
	insert_key(bt, 20);
	insert_key(bt, 26);
	insert_key(bt, 27);
	insert_key(bt, 28);
	delete_Btree(bt);
}
// Btree ���� �Լ�
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
// ��� ���� �Լ�
node* create_node(void) {
	node* new_node = malloc(sizeof(node));
	return new_node;
}
void split_node(node* parent, int index) {
	// ������ �ڽ��� �� ��带 �����Ѵ�
	node* right_child = create_node();
	// ���� ���� ���� �ڽ��� �ȴ�
	node* left_child = parent->p_arr[index];
	// ������ �ڽ��� ������� ���δ� ���� �ڽ��� ���� �����ϴ�
	right_child->isLeaf = left_child->isLeaf;
	// ������ �ڽ��� ũ��� M/2 or T �� �ǰ�
	right_child->size = T;
	// ���� �ڽ��� Ű �迭���� �߰��� �����ʿ� �ִ� ���� ������ ���� �ű��
	for (int i = 0; i < T; i++) {
		right_child->keys[i] = left_child->keys[i + T + 1];
	}
	// ���� ��尡 ������尡 �ƴ϶��
	if (!(left_child->isLeaf)) {
		// ���� �ڽ��� ������ �迭���� �߰��� �����ʿ� �ִ� ���� ������ ���� �ű��
		for (int i = 0; i <= T; i++) {
			right_child->p_arr[i] = left_child->p_arr[i + T + 1];
		}
	}
	// ���� ��忡�� ���� �����͸� �ű�� ���� �������� ũ�⸦ �����Ѵ�
	left_child->size = T;
	// ������ ����� �߰� ���� �� �ڸ��� �����
	// �θ��� Ű �迭���� �ڽ� ��带 ����Ű�� ��ġ ���� ���� �� ĭ�� �ڷ� �ű��
	for (int i = parent->size; i > index; i--) {
		parent->keys[i] = parent->keys[i - 1];
	}
	// �θ��� ������ �迭���� �ڽ� ��带 ����Ű�� ��ġ ���� ���� �� ĭ�� �ڷ� �ű�� 
	for (int i = parent->size+1; i > index ; i--) {
		parent->p_arr[i] = parent->p_arr[i - 1];
	}
	// ������ ����� Ű �迭�� �߰� ���� �θ� ��忡 �����Ѵ�
	parent->keys[index] = left_child->keys[T];
	// �߰� ���� �� ��ġ�� ������ �����ʹ� ���ҵ� ������ ��带 ����Ų��
	// (���� �����ʹ� �̹� ������ ���� ��带 ����Ű�� �ִ�)
	parent->p_arr[index + 1] = right_child;
	// �θ� Ű ���� �߰��Ǿ����� ũ�⸦ 1 �����Ѵ�
	parent->size += 1;
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
void print_tree(void) {
	printf("-----------------------------\n");
	printf("-----------------------------\n");
	printf("---------- TREE -------------\n");
	printf("-----------------------------\n");
	printf("-----------------------------\n");
}
bool search_key(void) {
	char action[5] = "��ȸ";
	int key = get_key(action);
	printf("       %d %s\n", key, action);
}
bool insert_key(Btree *bt, int key) {
	node* cur = bt->root;
	// ��Ʈ�� ũ�Ⱑ M�̶�� (��Ʈ ��尡 �� á�ٸ�)
	if (cur->size == M) {
		// �� ��带 �ϳ� �����Ѵ�
		node* new_root = create_node();
		// �� ��带 Btree�� �� ��Ʈ�� �����Ѵ�
		bt->root = new_root;
		// �� ��Ʈ�� ���� �ʱ�ȭ ���ְ� �������� �� �տ� ���� ��Ʈ �ּҸ� �����Ѵ�
		new_root->isLeaf = false;
		new_root->size = 0;
		new_root->p_arr[0] = cur;
		// �� ��Ʈ�� ������ �迭�� 0 ��°�� ������ ���� ��Ʈ ��带 �����Ѵ�
		split_node(new_root, 0);
		// ���� ��带 new_root�� �����Ѵ�
		cur = new_root;
	}
	// ���� ������ ������ ������忡 �ϱ� ������
	// ���� ������ ��������
	while (!cur->isLeaf) {
		// Ű ���� ���� ��忡 �ִ� ���� ���Ͽ� ������ �湮�ؾ��ϴ� ��� �ּҸ� ���Ѵ�
		int i = cur->size;
		while (i > 0 && key < cur->keys[i-1]) {
			i--;
		}
		// ������ �湮�ؾ� �ϴ� ��尡 �� ��������
		if (cur->p_arr[i]->size == M) {
			// ������ �湮�� ��带 �����Ѵ�
			split_node(cur, i);
			// �����ϸ鼭 ���� ����� Ű �迭�� i��° ���� ����Ǵµ�
			// �� �� ����� ������ ������ Ű ���� ũ�� ���� ��带 �����Ѵ�  
			if (key > cur->keys[i]) {
				i++;
			}
		}
		// �湮 ��带 ���� ���� �����Ѵ�
		cur = cur->p_arr[i];
	}
	// ������忡 ������ �� Ű�� ����
	int i = cur->size;
	while (i > 0 && key < cur->keys[i-1]) {
		cur->keys[i] = cur->keys[i-1];
		i--;
	}
	cur->keys[i] = key;
	cur->size += 1;
	return true;
}
bool delete_key(Btree* bt, int key) {
	node* cur = bt->root;
	// ���� ��忡�� key ���� ������ �� �ִ� ��ġ�� ã�´�
	int index = find_index(cur, key);
	// �湮�� ��尡 ���� ��尡 �� �� ���� �ݺ����� �����Ѵ�
	while (!cur->isLeaf) {
		// ������ �湮�� ����� ũ�Ⱑ T���� ũ�ų� ������
			// key �� ������ �ڽ� ����� key`�� ����� key�� key`�� �ٲ۵� �������� �Ѿ��
			// key �� ������ Ű�� ���� ���� ��ġ�� �׳� �Ѿ��.
		// ������ �湮�� ����� ũ�Ⱑ T���� ������
			// ���� ó���� �ϰ� �Ѿ��
			// 1. �湮�� ����� ������ ũ�Ⱑ t���� ũ�ų� ���� ���
				// 1-1. �θ� ���� �湮�� ��忡 �ְ� ���� ��忡�� ���� �������� ���� ���� �Ѿ��	
			// 2. �湮�� ����� ������ ũ�Ⱑ t���� ���� ���
		// ���� �湮�� ��忡 Ű�� �ִٸ�
		if (cur->keys[index] == key) {
			// ������ �湮�� ����� ũ�Ⱑ T���� ũ�ų� ������ (���� ó���� �ʿ� ������)
			if (T <= cur->p_arr[index]->size) {
				// �ڽĳ�忡�� key�� �����ϴ� ���� ���� ����� key���� �����
				int new_key = cur->p_arr[index]->keys[find_index(cur->p_arr[index], key)];
				cur->keys[index] = new_key;
				key = new_key;
			}
			// ������ �湮�� ����� ũ�Ⱑ T���� �۴ٸ�(���� ó���� �ʿ��ϸ�)
		}
		// �湮�� ��忡 Ű�� ���ٸ�
		else {
		}
		index = find_key(cur, key);
	}
	// ������忡 ������ �� Ű�� ����
	for (int i = index; i < cur->size; i++) {
		cur->keys[i] = cur->keys[i + 1];
	}
	cur->size -= 1;
	return true;
}
bool find_index(node* cur, int key) {
	int i = cur->size;
	while (0 < i && key < cur->keys[i - 1]) {
		i--;
	}
	return i;
}
void exit_program(void) {
	printf("   --------------------------------------------------------\n");
	printf("   -----------   ��� �� ���α׷��� �����մϴ�  -----------\n");
	printf("   --------------------------------------------------------\n");
}
void start_program(Btree* bt) {
	while (true) {
		switch (select_menu()) {
			// �Է� ���� 1�� ��� ���� tree�� ����Ѵ�
		case 1:
			system("cls");
			print_tree();
			break;
			// �Է� ���� 2�� ��� �����͸� �޾Ƽ� Ʈ������ ��ȸ�Ѵ�
		case 2:
			system("cls");
			search_key();
			break;
			// �Է� ���� 3�� ��� �����͸� �޾Ƽ� Ʈ���� �����Ѵ�
		case 3:
			system("cls");
			char action[5] = "����";
			int key = get_key(action);
			insert_key(bt, key);
			break;
			//�Է� ���� 4�� ��� �����͸� �޾Ƽ� Ʈ������ �����Ѵ�
		case 4:
			system("cls");
			char action[5] = "����";
			int key = get_key(action);
			delete_key(bt, key);
			break;
			//�Է� ���� 0�� ��� ���α׷��� �����Ѵ�
		case 0:
			exit_program();
			Sleep(wait_time * 2);
			exit(1);		// ���α׷� ����
		default:	// �� �ܿ� �Է��� ��� ���� �޽��� ��� �ٽ� �޴� �Է�
			printf("       �޴��� �߸� �Է��ϼ̽��ϴ�\n");
		}
		system("pause");
	}
}
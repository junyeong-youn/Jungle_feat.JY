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
	node* root;						// BƮ���� ��Ʈ �ּ�
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
void insert_key(Btree* bt);
void delete_key(void);
void exit_program(void);
void start_program(Btree* bt);
int main() {
	Btree* bt = create_Btree();
	start_program(bt);
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
	// ���� �ڽ��� �߰��� �����ʿ� �ִ� ���� ������ ���� �ű��
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
void insert_key(Btree *bt) {
	char action[5] = "����";
	int key = get_key(action);
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
	// ���������� ��������
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
	// ������忡 ������ �� K�� ����
	int i = cur->size;
	while (i > 0 && key < cur->keys[i-1]) {
		cur->keys[i] = cur->keys[i-1];
		i--;
	}
	cur->keys[i] = key;
	cur->size += 1;
}
void delete_key(void) {
	char action[5] = "����";
	int key = get_key(action);
	printf("       %d %s\n", key, action);
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
			insert_key(bt);
			break;
			//�Է� ���� 4�� ��� �����͸� �޾Ƽ� Ʈ������ �����Ѵ�
		case 4:
			system("cls");
			delete_key();
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
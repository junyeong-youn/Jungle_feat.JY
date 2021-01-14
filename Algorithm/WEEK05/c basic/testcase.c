#define TEST { 10,1,3,63,82,6,31,8,2,16,11,77,96,14,92,21,47,23,24,78,26,97,15,4,30,69,37,38,76,90,17,87,53,44,45,46,9,41,54,43,22,84,58,39,65,28,42,59,99,70,71,72,29,74,73,68,13,60,79,80,81,85,83,64,94,86,66,88,93,40,91,62,25,20,36,95,19,52,55,100 }

// 확인 함수
void print_for_exam(node* x);

// 테스트
int main()
{
    int arr[80] = TEST;
    struct Node* flag = createNode();
    struct BTREE* BTree = initTree();
    struct Node* rootNode = createNode();
    Bptree->root = rootNode;
    flag->nextNode = Bptree->root;

		// TEST 1 CASE
    InsertToTree(Bptree, 4, 4 * 1000);
    InsertToTree(Bptree, 1, 1 * 1000);
    InsertToTree(Bptree, 3, 3 * 1000);
    InsertToTree(Bptree, 2, 2 * 1000);

    DeleteFromTree(Bptree, Bptree->root, 4);
    DeleteFromTree(Bptree, Bptree->root, 2);
    DeleteFromTree(Bptree, Bptree->root, 3);

    printf("---- TEST1 ----");
    print_for_exam(Bptree->root);

		// TEST 2 CASE
    for (int i = 2; i <= 100; i++) {
        InsertToTree(Bptree, i, i * 1000);
    }
    for (int i = 50; i <= 70; i++) {
        DeleteFromTree(Bptree, Bptree->root, i);
    }

    printf("\n\n\n\n\n\n");
    printf("---- TEST2 ----");
    print_for_exam(Bptree->root);

		// TEST3 CASE
    for (int i = 50; i <= 70; i++) {
        InsertToTree(BTree, i, i * 1000);
    }

    for (int i = 0; i <80; i++) {
        DeleteFromTree(BTree, Bptree->root, arr[i]);
    }

    printf("\n\n\n\n\n\n");
    printf("---- TEST3 ----");
    print_for_exam(Bptree->root);

    printf("프로그램이 정상적으로 종료 되었음.");
    return 0;
}

// 출력(DFS)
void print_for_exam(node* x) {
    if (x->leaf) {
        for (int i = 1; i <= x->lenKey; i++) {
            printf("[%5d, %5d]\n", x->key[i], x->C[i]->lenKey);
        }
    }
    else {
        for (int i = 1; i <= x->lenKey; i++) {
            print_for_exam(x->C[i]);
            printf("[%5d]\n", x->key[i]);
        }
        print_for_exam(x->C[x->lenKey+1]);
    }
}
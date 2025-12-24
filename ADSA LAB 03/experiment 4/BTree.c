#include <stdio.h>
#include <stdlib.h>

#define T 3   // Minimum degree of B-Tree

/* -------- B-Tree Node Structure -------- */
struct BNode {
    int key[2 * T - 1];
    struct BNode *child[2 * T];
    int count;     // number of keys
    int isLeaf;    // 1 if leaf node
};

/* Create a new B-Tree node */
struct BNode* createBNode(int leafFlag) {
    struct BNode* node = (struct BNode*)malloc(sizeof(struct BNode));
    node->isLeaf = leafFlag;
    node->count = 0;

    for (int i = 0; i < 2 * T; i++)
        node->child[i] = NULL;

    return node;
}

/* Traverse B-Tree (inorder style) */
void traverseTree(struct BNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->count; i++) {
            if (!root->isLeaf)
                traverseTree(root->child[i]);
            printf("%d ", root->key[i]);
        }
        if (!root->isLeaf)
            traverseTree(root->child[i]);
    }
}

/* Search key in B-Tree */
struct BNode* searchKey(struct BNode* root, int value) {
    int i = 0;
    while (i < root->count && value > root->key[i])
        i++;

    if (i < root->count && root->key[i] == value)
        return root;

    if (root->isLeaf)
        return NULL;

    return searchKey(root->child[i], value);
}

/* Split full child */
void splitChildNode(struct BNode* parent, int index, struct BNode* y) {
    struct BNode* z = createBNode(y->isLeaf);
    z->count = T - 1;

    for (int j = 0; j < T - 1; j++)
        z->key[j] = y->key[j + T];

    if (!y->isLeaf) {
        for (int j = 0; j < T; j++)
            z->child[j] = y->child[j + T];
    }

    y->count = T - 1;

    for (int j = parent->count; j >= index + 1; j--)
        parent->child[j + 1] = parent->child[j];

    parent->child[index + 1] = z;

    for (int j = parent->count - 1; j >= index; j--)
        parent->key[j + 1] = parent->key[j];

    parent->key[index] = y->key[T - 1];
    parent->count++;
}

/* Insert key into a non-full node */
void insertIntoNonFull(struct BNode* node, int value) {
    int i = node->count - 1;

    if (node->isLeaf) {
        while (i >= 0 && node->key[i] > value) {
            node->key[i + 1] = node->key[i];
            i--;
        }
        node->key[i + 1] = value;
        node->count++;
    } else {
        while (i >= 0 && node->key[i] > value)
            i--;

        if (node->child[i + 1]->count == 2 * T - 1) {
            splitChildNode(node, i + 1, node->child[i + 1]);

            if (value > node->key[i + 1])
                i++;
        }
        insertIntoNonFull(node->child[i + 1], value);
    }
}

/* Insert a key into B-Tree */
struct BNode* insertKey(struct BNode* root, int value) {
    if (root == NULL) {
        root = createBNode(1);
        root->key[0] = value;
        root->count = 1;
        return root;
    }

    if (root->count == 2 * T - 1) {
        struct BNode* newRoot = createBNode(0);
        newRoot->child[0] = root;

        splitChildNode(newRoot, 0, root);

        int i = 0;
        if (newRoot->key[0] < value)
            i++;

        insertIntoNonFull(newRoot->child[i], value);
        return newRoot;
    } else {
        insertIntoNonFull(root, value);
        return root;
    }
}

/* -------- MAIN FUNCTION -------- */
int main() {
    struct BNode* root = NULL;
    int choice, data;

    while (1) {
        printf("\n--- B-Tree Operations ---\n");
        printf("1. Insert\n2. Traverse\n3. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &data);
                root = insertKey(root, data);
                break;

            case 2:
                printf("B-Tree traversal: ");
                traverseTree(root);
                printf("\n");
                break;

            case 3:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

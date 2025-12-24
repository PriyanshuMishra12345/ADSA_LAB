#include <stdio.h>
#include <stdlib.h>

/* -------- AVL Tree Node Definition -------- */
struct AVLNode {
    int data;
    struct AVLNode *leftChild;
    struct AVLNode *rightChild;
    int height;
};

/* Get height of node */
int getHeight(struct AVLNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

/* Create a new AVL node */
struct AVLNode* createAVLNode(int value) {
    struct AVLNode* node = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    node->data = value;
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->height = 1;
    return node;
}

/* Get balance factor */
int balanceFactor(struct AVLNode *node) {
    if (node == NULL)
        return 0;
    return getHeight(node->leftChild) - getHeight(node->rightChild);
}

/* Right rotation */
struct AVLNode* rotateRight(struct AVLNode* y) {
    struct AVLNode* x = y->leftChild;
    struct AVLNode* T2 = x->rightChild;

    x->rightChild = y;
    y->leftChild = T2;

    y->height = 1 + (getHeight(y->leftChild) > getHeight(y->rightChild)
                        ? getHeight(y->leftChild)
                        : getHeight(y->rightChild));
    x->height = 1 + (getHeight(x->leftChild) > getHeight(x->rightChild)
                        ? getHeight(x->leftChild)
                        : getHeight(x->rightChild));

    return x;
}

/* Left rotation */
struct AVLNode* rotateLeft(struct AVLNode* x) {
    struct AVLNode* y = x->rightChild;
    struct AVLNode* T2 = y->leftChild;

    y->leftChild = x;
    x->rightChild = T2;

    x->height = 1 + (getHeight(x->leftChild) > getHeight(x->rightChild)
                        ? getHeight(x->leftChild)
                        : getHeight(x->rightChild));
    y->height = 1 + (getHeight(y->leftChild) > getHeight(y->rightChild)
                        ? getHeight(y->leftChild)
                        : getHeight(y->rightChild));

    return y;
}

/* Insert node into AVL tree */
struct AVLNode* insertAVL(struct AVLNode* node, int value) {
    if (node == NULL)
        return createAVLNode(value);

    if (value < node->data)
        node->leftChild = insertAVL(node->leftChild, value);
    else if (value > node->data)
        node->rightChild = insertAVL(node->rightChild, value);
    else
        return node;   // duplicates not allowed

    node->height = 1 + (getHeight(node->leftChild) > getHeight(node->rightChild)
                           ? getHeight(node->leftChild)
                           : getHeight(node->rightChild));

    int balance = balanceFactor(node);

    /* Balancing cases */
    if (balance > 1 && value < node->leftChild->data)
        return rotateRight(node);

    if (balance < -1 && value > node->rightChild->data)
        return rotateLeft(node);

    if (balance > 1 && value > node->leftChild->data) {
        node->leftChild = rotateLeft(node->leftChild);
        return rotateRight(node);
    }

    if (balance < -1 && value < node->rightChild->data) {
        node->rightChild = rotateRight(node->rightChild);
        return rotateLeft(node);
    }

    return node;
}

/* Find node with minimum value */
struct AVLNode* minimumNode(struct AVLNode* node) {
    struct AVLNode* current = node;
    while (current->leftChild != NULL)
        current = current->leftChild;
    return current;
}

/* Delete node from AVL tree */
struct AVLNode* deleteAVL(struct AVLNode* root, int value) {
    if (root == NULL)
        return root;

    if (value < root->data)
        root->leftChild = deleteAVL(root->leftChild, value);
    else if (value > root->data)
        root->rightChild = deleteAVL(root->rightChild, value);
    else {
        if (root->leftChild == NULL || root->rightChild == NULL) {
            struct AVLNode* temp = root->leftChild
                                   ? root->leftChild
                                   : root->rightChild;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            struct AVLNode* temp = minimumNode(root->rightChild);
            root->data = temp->data;
            root->rightChild = deleteAVL(root->rightChild, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + (getHeight(root->leftChild) > getHeight(root->rightChild)
                           ? getHeight(root->leftChild)
                           : getHeight(root->rightChild));

    int balance = balanceFactor(root);

    /* Rebalancing cases */
    if (balance > 1 && balanceFactor(root->leftChild) >= 0)
        return rotateRight(root);

    if (balance > 1 && balanceFactor(root->leftChild) < 0) {
        root->leftChild = rotateLeft(root->leftChild);
        return rotateRight(root);
    }

    if (balance < -1 && balanceFactor(root->rightChild) <= 0)
        return rotateLeft(root);

    if (balance < -1 && balanceFactor(root->rightChild) > 0) {
        root->rightChild = rotateRight(root->rightChild);
        return rotateLeft(root);
    }

    return root;
}

/* Preorder traversal */
void preorderTraversal(struct AVLNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->leftChild);
        preorderTraversal(root->rightChild);
    }
}

/* -------- MAIN FUNCTION -------- */
int main() {
    struct AVLNode* root = NULL;
    int choice, value;

    while (1) {
        printf("\n--- AVL Tree Operations ---\n");
        printf("1. Insert\n2. Delete\n3. Preorder Traversal\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                root = insertAVL(root, value);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteAVL(root, value);
                break;

            case 3:
                printf("Preorder: ");
                preorderTraversal(root);
                printf("\n");
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

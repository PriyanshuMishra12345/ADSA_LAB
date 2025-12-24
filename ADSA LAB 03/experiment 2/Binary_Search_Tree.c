#include <stdio.h>
#include <stdlib.h>

/* Definition of BST node */
struct TreeNode {
    int value;
    struct TreeNode *leftChild;
    struct TreeNode *rightChild;
};

/* Create a new BST node */
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->value = val;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

/* Insert a value into BST */
struct TreeNode* insertNode(struct TreeNode* root, int val) {
    if (root == NULL)
        return newNode(val);

    if (val < root->value)
        root->leftChild = insertNode(root->leftChild, val);
    else if (val > root->value)
        root->rightChild = insertNode(root->rightChild, val);

    return root;
}

/* Find node with minimum value */
struct TreeNode* minValueNode(struct TreeNode* root) {
    while (root->leftChild != NULL)
        root = root->leftChild;
    return root;
}

/* Delete a node from BST */
struct TreeNode* removeNode(struct TreeNode* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->value)
        root->leftChild = removeNode(root->leftChild, key);
    else if (key > root->value)
        root->rightChild = removeNode(root->rightChild, key);
    else {
        /* Node with zero or one child */
        if (root->leftChild == NULL) {
            struct TreeNode* temp = root->rightChild;
            free(root);
            return temp;
        }
        else if (root->rightChild == NULL) {
            struct TreeNode* temp = root->leftChild;
            free(root);
            return temp;
        }

        /* Node with two children */
        struct TreeNode* temp = minValueNode(root->rightChild);
        root->value = temp->value;
        root->rightChild = removeNode(root->rightChild, temp->value);
    }
    return root;
}

/* Inorder traversal */
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->leftChild);
        printf("%d ", root->value);
        inorderTraversal(root->rightChild);
    }
}

/* Preorder traversal */
void preorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        preorderTraversal(root->leftChild);
        preorderTraversal(root->rightChild);
    }
}

/* Postorder traversal */
void postorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->leftChild);
        postorderTraversal(root->rightChild);
        printf("%d ", root->value);
    }
}

int main() {
    struct TreeNode* root = NULL;
    int option, data;

    while (1) {
        printf("\n--- Binary Search Tree Operations ---\n");
        printf("1. Insert\n2. Delete\n3. Inorder Traversal\n");
        printf("4. Preorder Traversal\n5. Postorder Traversal\n");
        printf("6. Exit\nEnter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &data);
                root = removeNode(root, data);
                break;

            case 3:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;

            case 4:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;

            case 5:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

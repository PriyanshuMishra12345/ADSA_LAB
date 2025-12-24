#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct FibNode {
    int key, degree, mark;
    struct FibNode *parent, *child, *left, *right;
} FibNode;

typedef struct FibHeap {
    FibNode *min;
    int n;
} FibHeap;

// ---------------------- Creation ------------------------

FibNode* createNode(int key) {
    FibNode *node = (FibNode*)malloc(sizeof(FibNode));
    node->key = key;
    node->degree = 0;
    node->mark = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    return node;
}

FibHeap* createHeap() {
    FibHeap *H = (FibHeap*)malloc(sizeof(FibHeap));
    H->min = NULL;
    H->n = 0;
    return H;
}

// ---------------------- Helpers ------------------------

void insertIntoRootList(FibHeap *H, FibNode *node) {
    if (H->min == NULL) {
        H->min = node;
        node->left = node;
        node->right = node;
    } else {
        // insert node after H->min
        node->right = H->min->right;
        node->left = H->min;
        H->min->right->left = node;
        H->min->right = node;
    }
}

void fibLink(FibNode *y, FibNode *x) {
    // Remove y from root list
    y->left->right = y->right;
    y->right->left = y->left;

    y->parent = x;
    y->mark = 0;

    // Add y to x's child list
    if (x->child == NULL) {
        x->child = y;
        y->left = y;
        y->right = y;
    } else {
        // insert y into child's circular list
        y->right = x->child->right;
        y->left  = x->child;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
}

// ---------------------- Consolidate ------------------------

void consolidate(FibHeap *H) {
    if (H->min == NULL) return;

    int maxD = (int)(log2(H->n)) + 2;
    FibNode **A = (FibNode**)calloc(maxD, sizeof(FibNode*));

    // Count roots first (because root list changes during consolidation)
    FibNode *start = H->min;
    FibNode *w = start;
    int rootCount = 0;
    do {
        rootCount++;
        w = w->right;
    } while (w != start);

    w = start;
    for (int i = 0; i < rootCount; i++) {
        FibNode *x = w;
        w = w->right;  // move ahead in current root list

        int d = x->degree;
        while (d >= maxD) {  // grow array if needed (very rare)
            int oldMax = maxD;
            maxD *= 2;
            A = (FibNode**)realloc(A, maxD * sizeof(FibNode*));
            for (int j = oldMax; j < maxD; j++) A[j] = NULL;
        }

        while (A[d] != NULL) {
            FibNode *y = A[d];
            if (x->key > y->key) {
                FibNode *temp = x;
                x = y;
                y = temp;
            }
            fibLink(y, x);
            A[d] = NULL;
            d++;
            while (d >= maxD) {
                int oldMax = maxD;
                maxD *= 2;
                A = (FibNode**)realloc(A, maxD * sizeof(FibNode*));
                for (int j = oldMax; j < maxD; j++) A[j] = NULL;
            }
        }
        A[d] = x;
    }

    H->min = NULL;

    // Rebuild root list from A[]
    for (int i = 0; i < maxD; i++) {
        if (A[i] != NULL) {
            if (H->min == NULL) {
                H->min = A[i];
                H->min->left = H->min;
                H->min->right = H->min;
            } else {
                FibNode *node = A[i];
                node->left = H->min;
                node->right = H->min->right;
                H->min->right->left = node;
                H->min->right = node;
                if (node->key < H->min->key)
                    H->min = node;
            }
        }
    }

    free(A);
}

// ---------------------- Insert ------------------------

void insert(FibHeap *H, int key) {
    FibNode *node = createNode(key);
    insertIntoRootList(H, node);
    if (H->min == NULL || node->key < H->min->key)
        H->min = node;
    H->n++;
}

// ---------------------- Extract Min ------------------------

FibNode* extractMin(FibHeap *H) {
    FibNode *z = H->min;
    if (z == NULL) return NULL;

    // Add children of z to root list
    if (z->child != NULL) {
        FibNode *start = z->child;
        FibNode *x = start;
        do {
            FibNode *next = x->right;  // save next sibling before altering links

            // Remove parent link
            x->parent = NULL;

            // Insert x into root list (after H->min)
            x->left = H->min;
            x->right = H->min->right;
            H->min->right->left = x;
            H->min->right = x;

            x = next;
        } while (x != start);
        z->child = NULL;
    }

    // Remove z from root list
    z->left->right = z->right;
    z->right->left = z->left;

    if (z == z->right) {
        H->min = NULL;
    } else {
        H->min = z->right;
        consolidate(H);
    }

    H->n--;
    // Detach z from any list
    z->left = z->right = z;
    return z;
}

// ---------------------- Cut & Cascading Cut ------------------------

void cut(FibHeap *H, FibNode *x, FibNode *y) {
    // Remove x from y's child list
    if (y->child == x) {
        if (x->right != x)
            y->child = x->right;
        else
            y->child = NULL;
    }
    x->left->right = x->right;
    x->right->left = x->left;
    y->degree--;

    // Add x to root list
    insertIntoRootList(H, x);
    x->parent = NULL;
    x->mark = 0;
}

void cascadingCut(FibHeap *H, FibNode *y) {
    FibNode *z = y->parent;
    if (z != NULL) {
        if (y->mark == 0) {
            y->mark = 1;
        } else {
            cut(H, y, z);
            cascadingCut(H, z);
        }
    }
}

// ---------------------- Decrease Key ------------------------

void decreaseKey(FibHeap *H, FibNode *x, int newKey) {
    if (newKey > x->key) {
        printf("Error: New key is greater than current key!\n");
        return;
    }

    x->key = newKey;
    FibNode *y = x->parent;

    if (y != NULL && x->key < y->key) {
        cut(H, x, y);
        cascadingCut(H, y);
    }

    if (x->key < H->min->key)
        H->min = x;
}

// ---------------------- Delete Node ------------------------

void deleteNode(FibHeap *H, FibNode *x) {
    decreaseKey(H, x, INT_MIN);
    FibNode *z = extractMin(H);
    if (z) free(z);
}

// ---------------------- Search ------------------------

FibNode* search(FibNode* start, int key) {
    if (start == NULL) return NULL;

    FibNode *temp = start;
    do {
        if (temp->key == key) return temp;

        FibNode *res = search(temp->child, key);
        if (res != NULL) return res;

        temp = temp->right;
    } while (temp != start);

    return NULL;
}

// ---------------------- Display (Full Hierarchy) ------------------------

void displayNode(FibNode *node, int depth) {
    if (!node) return;

    FibNode *start = node;
    FibNode *curr = start;
    do {
        for (int i = 0; i < depth; i++)
            printf("  "); // indentation
        printf("- %d\n", curr->key);

        if (curr->child != NULL) {
            displayNode(curr->child, depth + 1);
        }

        curr = curr->right;
    } while (curr != start);
}

void displayHeap(FibHeap *H) {
    if (H->min == NULL) {
        printf("\nHeap is empty.\n");
        return;
    }

    printf("\nFibonacci Heap (min = %d):\n", H->min->key);
    displayNode(H->min, 0);
}

// ---------------------- Free All Memory ------------------------

void freeNodeList(FibNode *start) {
    if (!start) return;
    FibNode *curr = start;
    do {
        FibNode *next = curr->right;
        if (curr->child)
            freeNodeList(curr->child);
        free(curr);
        curr = next;
    } while (curr != start);
}

void freeHeap(FibHeap *H) {
    if (!H) return;
    if (H->min)
        freeNodeList(H->min);
    free(H);
}

// ---------------------- MAIN MENU ------------------------

int main() {
    FibHeap *H = createHeap();
    int choice, key, newKey;
    FibNode *node;

    while (1) {
        printf("\n===== Fibonacci Heap Menu =====\n");
        printf("1. Insert\n");
        printf("2. Find Min\n");
        printf("3. Extract Min\n");
        printf("4. Decrease Key\n");
        printf("5. Delete Key\n");
        printf("6. Display Heap (full)\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &key);
            insert(H, key);
            break;

        case 2:
            if (H->min)
                printf("Minimum: %d\n", H->min->key);
            else
                printf("Heap is empty.\n");
            break;

        case 3:
            node = extractMin(H);
            if (node) {
                printf("Extracted Min: %d\n", node->key);
                free(node); // free extracted node
            } else {
                printf("Heap is empty.\n");
            }
            break;

        case 4:
            printf("Enter key to decrease: ");
            scanf("%d", &key);
            node = search(H->min, key);
            if (node == NULL) {
                printf("Key not found.\n");
                break;
            }
            printf("Enter new smaller key: ");
            scanf("%d", &newKey);
            decreaseKey(H, node, newKey);
            break;

        case 5:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            node = search(H->min, key);
            if (node == NULL) {
                printf("Key not found.\n");
                break;
            }
            deleteNode(H, node);
            printf("Deleted.\n");
            break;

        case 6:
            displayHeap(H);
            break;

        case 7:
            freeHeap(H);
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid choice.\n");
        }
    }

    freeHeap(H);
    return 0;
}


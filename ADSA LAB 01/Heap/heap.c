#include <stdio.h>

#define MAXSIZE 100   // maximum heap capacity

int minHeap[MAXSIZE];

/* Swap two values */
void exchange(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

/* Heapify downward to maintain min-heap */
void heapifyDown(int pos, int size) {
    int leftChild = 2 * pos;
    int rightChild = 2 * pos + 1;
    int smallest = pos;

    if (leftChild <= size && minHeap[leftChild] < minHeap[smallest])
        smallest = leftChild;

    if (rightChild <= size && minHeap[rightChild] < minHeap[smallest])
        smallest = rightChild;

    if (smallest != pos) {
        exchange(&minHeap[pos], &minHeap[smallest]);
        heapifyDown(smallest, size);
    }
}

/* Display heap elements */
void displayHeap(int size) {
    for (int i = 1; i <= size; i++) {
        printf("%d ", minHeap[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter the no. of elements to be inserted in heap\n");
    scanf("%d", &n);

    printf("Enter Heap elements:\n");
    for (int i = 1; i <= n; i++) {   // heap starts at index 1
        scanf("%d", &minHeap[i]);
    }

    printf("Inserted Heap (Array):\n");
    displayHeap(n);

    /* Build min heap */
    for (int i = n / 2; i >= 1; i--) {
        heapifyDown(i, n);
    }

    printf("Heapified Heap (Min-Heap):\n");
    displayHeap(n);

    return 0;
}

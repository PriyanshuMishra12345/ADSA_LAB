#include <stdio.h>

#define MAXSIZE 100   // maximum heap size

int minHeap[MAXSIZE];
int size = 0;

/* Swap two elements */
void exchange(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

/* Restore heap property upwards */
void siftUp(int pos) {
    int parent = pos / 2;

    if (parent >= 1 && minHeap[parent] > minHeap[pos]) {
        exchange(&minHeap[parent], &minHeap[pos]);
        siftUp(parent);
    }
}

/* Insert an element into the min heap */
void insertElement(int data) {
    if (size >= MAXSIZE - 1) {
        printf("Heap overflow!\n");
        return;
    }

    size++;
    minHeap[size] = data;
    siftUp(size);
}

/* Print heap contents */
void showHeap() {
    printf("Heap array: ");
    for (int i = 1; i <= size; i++) {
        printf("%d ", minHeap[i]);
    }
    printf("\n");
}

int main() {
    int n, value;

    printf("Enter number of elements to insert: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter value: ");
        scanf("%d", &value);
        insertElement(value);
        showHeap();
    }

    return 0;
}

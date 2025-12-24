#include <stdio.h>

/* ---------- COMMON SWAP FUNCTION ---------- */
void exchange(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

/* ---------- QUICK SORT ---------- */
int quickPartition(int a[], int low, int high) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            exchange(&a[i], &a[j]);
        }
    }
    exchange(&a[i + 1], &a[high]);
    return i + 1;
}

void quickSortAlgo(int a[], int low, int high) {
    if (low < high) {
        int p = quickPartition(a, low, high);
        quickSortAlgo(a, low, p - 1);
        quickSortAlgo(a, p + 1, high);
    }
}

/* ---------- MERGE SORT ---------- */
void mergeArrays(int a[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (i < n1)
        a[k++] = L[i++];

    while (j < n2)
        a[k++] = R[j++];
}

void mergeSortAlgo(int a[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSortAlgo(a, l, m);
        mergeSortAlgo(a, m + 1, r);
        mergeArrays(a, l, m, r);
    }
}

/* ---------- HEAP SORT ---------- */
void heapifyNode(int a[], int size, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && a[left] > a[largest])
        largest = left;

    if (right < size && a[right] > a[largest])
        largest = right;

    if (largest != root) {
        exchange(&a[root], &a[largest]);
        heapifyNode(a, size, largest);
    }
}

void heapSortAlgo(int a[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapifyNode(a, size, i);

    for (int i = size - 1; i > 0; i--) {
        exchange(&a[0], &a[i]);
        heapifyNode(a, i, 0);
    }
}

/* ---------- DISPLAY FUNCTION ---------- */
void displayArray(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

/* ---------- MAIN ---------- */
int main() {
    int n, option;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nChoose Sorting Method:\n");
    printf("1. Quick Sort\n");
    printf("2. Merge Sort\n");
    printf("3. Heap Sort\n");
    printf("Enter choice: ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            quickSortAlgo(arr, 0, n - 1);
            printf("Sorted Array using Quick Sort:\n");
            break;

        case 2:
            mergeSortAlgo(arr, 0, n - 1);
            printf("Sorted Array using Merge Sort:\n");
            break;

        case 3:
            heapSortAlgo(arr, n);
            printf("Sorted Array using Heap Sort:\n");
            break;

        default:
            printf("Invalid choice!\n");
            return 0;
    }

    displayArray(arr, n);
    return 0;
}

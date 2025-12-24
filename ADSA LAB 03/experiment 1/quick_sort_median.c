#include <stdio.h>

/* Swap two integers */
void exchange(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

/* Choose median of low, mid, high as pivot */
int selectMedian(int a[], int low, int high) {
    int mid = (low + high) / 2;

    if (a[low] > a[mid])
        exchange(&a[low], &a[mid]);
    if (a[low] > a[high])
        exchange(&a[low], &a[high]);
    if (a[mid] > a[high])
        exchange(&a[mid], &a[high]);

    /* Move median to high - 1 */
    exchange(&a[mid], &a[high - 1]);
    return a[high - 1];
}

/* Partition array using median pivot */
int divide(int a[], int low, int high) {
    int pivot = selectMedian(a, low, high);
    int i = low;
    int j = high - 1;

    while (1) {
        while (a[++i] < pivot) { }
        while (a[--j] > pivot) { }

        if (i < j)
            exchange(&a[i], &a[j]);
        else
            break;
    }

    exchange(&a[i], &a[high - 1]);   // restore pivot
    return i;
}

/* Quick Sort with Median-of-Three */
void quickSortMedian(int a[], int low, int high) {
    if (low < high) {
        if (high - low + 1 <= 3) {
            if (a[low] > a[high])
                exchange(&a[low], &a[high]);
        } else {
            int p = divide(a, low, high);
            quickSortMedian(a, low, p - 1);
            quickSortMedian(a, p + 1, high);
        }
    }
}

/* Print array */
void display(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    quickSortMedian(arr, 0, n - 1);

    printf("Sorted Array (Quick Sort with Median Pivot):\n");
    display(arr, n);

    return 0;
}

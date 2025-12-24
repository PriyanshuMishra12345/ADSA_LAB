#include <stdio.h>

/* Recursive Binary Search */
int recursiveBinarySearch(int a[], int left, int right, int target) {
    if (left <= right) {
        int mid = left + (right - left) / 2;

        if (a[mid] == target)
            return mid;

        if (target < a[mid])
            return recursiveBinarySearch(a, left, mid - 1, target);
        else
            return recursiveBinarySearch(a, mid + 1, right, target);
    }
    return -1;
}

/* Iterative Binary Search */
int iterativeBinarySearch(int a[], int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (a[mid] == target)
            return mid;

        if (target < a[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

int main() {
    int n, key, option, index;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d sorted integers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter key to search: ");
    scanf("%d", &key);

    printf("\nChoose search method:\n");
    printf("1. Recursive Binary Search\n");
    printf("2. Iterative Binary Search\n");
    printf("Enter choice: ");
    scanf("%d", &option);

    if (option == 1)
        index = recursiveBinarySearch(arr, 0, n - 1, key);
    else
        index = iterativeBinarySearch(arr, n, key);

    if (index != -1)
        printf("Key %d found at index %d (0-based index)\n", key, index);
    else
        printf("Key %d not found in the list.\n", key);

    return 0;
}

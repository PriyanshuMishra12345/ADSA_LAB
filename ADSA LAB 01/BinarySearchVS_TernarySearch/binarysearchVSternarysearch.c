#include <stdio.h>
#include <stdlib.h>

/* Global comparison counters */
int binCount = 0;
int terCount = 0;

/* Function declarations */
int binarySearch(int a[], int l, int r, int key);
int ternarySearch(int a[], int l, int r, int key);

/* Binary Search */
int binarySearch(int a[], int l, int r, int key) {
    if (l <= r) {
        int m = l + (r - l) / 2;

        binCount++;
        if (a[m] == key)
            return m;

        binCount++;
        if (key < a[m])
            return binarySearch(a, l, m - 1, key);
        else
            return binarySearch(a, m + 1, r, key);
    }
    return -1;
}

/* Ternary Search */
int ternarySearch(int a[], int l, int r, int key) {
    if (l <= r) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        terCount++;
        if (a[m1] == key)
            return m1;

        terCount++;
        if (a[m2] == key)
            return m2;

        terCount++;
        if (key < a[m1])
            return ternarySearch(a, l, m1 - 1, key);

        terCount++;
        if (key > a[m2])
            return ternarySearch(a, m2 + 1, r, key);

        return ternarySearch(a, m1 + 1, m2 - 1, key);
    }
    return -1;
}

int main() {
    int t;
    scanf("%d", &t);

    FILE *fp = fopen("output.dat", "a");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while (t--) {
        int n;
        printf("Enter the size of array\n");
        scanf("%d", &n);
        printf("%d\n", n);

        int arr[n];
        printf("Enter the array elements\n");
        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);

        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");

        int key;
        printf("Enter the value of key\n");
        scanf("%d", &key);
        printf("%d\n", key);

        binCount = 0;
        terCount = 0;

        int idxBin = binarySearch(arr, 0, n - 1, key);
        int idxTer = ternarySearch(arr, 0, n - 1, key);

        printf("%d\n", idxBin);
        printf("%d %d %d\n", n, binCount, terCount);
        fprintf(fp, "%d %d %d\n", n, binCount, terCount);
    }

    printf("Results appended to output.dat\n");
    fclose(fp);
    return 0;
}

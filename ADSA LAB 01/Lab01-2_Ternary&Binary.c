#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Binary Search 
int binarySearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (arr[mid] == x)
            return mid;
        else if (arr[mid] < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}

// Ternary Search 
int ternarySearch(int l, int r, int key, int arr[]) {
    while (r >= l) {
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;

        if (arr[mid1] == key)
            return mid1;
        if (arr[mid2] == key)
            return mid2;

        if (key < arr[mid1])
            r = mid1 - 1;
        else if (key > arr[mid2])
            l = mid2 + 1;
        else {
            l = mid1 + 1;
            r = mid2 - 1;
        }
    }
    return -1;
}

// Timing Helper 
double measure_binary(int arr[], int n, int key, int trials) {
    clock_t start = clock();
    for (int i = 0; i < trials; i++) {
        binarySearch(arr, 0, n - 1, key);
    }
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC / trials;
}

double measure_ternary(int arr[], int n, int key, int trials) {
    clock_t start = clock();
    for (int i = 0; i < trials; i++) {
        ternarySearch(0, n - 1, key, arr);
    }
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC / trials;
}

// Main
int main() {
    int sizes[] = {1000, 5000, 10000, 50000, 100000, 200000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    FILE *f = fopen("search_comparison.csv", "w");
    if (!f) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(f, "n,Binary,Ternary\n");

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int *arr = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) arr[j] = j;

        int key = arr[n - 1]; // search for last element (worst case)
        int trials = 100000;  // repeat to get measurable time

        double t_binary = measure_binary(arr, n, key, trials);
        double t_ternary = measure_ternary(arr, n, key, trials);

        printf("n=%d | Binary=%.10f | Ternary=%.10f\n", n, t_binary, t_ternary);
        fprintf(f, "%d,%.10f,%.10f\n", n, t_binary, t_ternary);

        free(arr);
    }

    fclose(f);
    printf("Results saved to search_comparison.csv\n");
    return 0;
}

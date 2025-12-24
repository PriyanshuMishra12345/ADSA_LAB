#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Function definitions */
double fun1(double a)  { return a * (log(a) / log(2)); }
double fun2(double a)  { return 12 * sqrt(a); }
double fun3(double a)  { return 1.0 / a; }
double fun4(double a)  { return pow(a, log(a) / log(2)); }
double fun5(double a)  { return 100 * pow(a, 2) + 6 * a; }
double fun6(double a)  { return pow(a, 0.51); }
double fun7(double a)  { return pow(a, 2) - 324; }
double fun8(double a)  { return 50 * sqrt(a); }
double fun9(double a)  { return 2 * pow(a, 3); }
double fun10(double a) { return pow(3, a); }
double fun11(double a) { return pow(2, 32) * a; }
double fun12(double a) { return log(a) / log(2); }

int main() {
    int maxn;
    printf("Enter the value of n:\n");
    scanf("%d", &maxn);

    int *ptr = (int *)calloc(maxn, sizeof(int));
    if (!ptr) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter %d numbers:\n", maxn);
    for (int i = 0; i < maxn; i++)
        scanf("%d", &ptr[i]);

    printf("\nYou entered:\n");
    for (int i = 0; i < maxn; i++)
        printf("%d ", ptr[i]);
    printf("\n\n");

    /* Function pointer array */
    double (*funcs[])(double) = {
        fun1, fun2, fun3, fun4, fun5, fun6,
        fun7, fun8, fun9, fun10, fun11, fun12
    };

    /* Print results (same as original program) */
    for (int i = 0; i < maxn; i++) {
        for (int f = 0; f < 12; f++) {
            printf("n=%d %f\n", ptr[i], funcs[f](ptr[i]));
        }
        printf("\n");
    }

    free(ptr);
    return 0;
}

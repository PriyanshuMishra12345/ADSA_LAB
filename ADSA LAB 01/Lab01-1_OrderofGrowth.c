#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NUM_FUNCS 12

// Define the 12 functions
double f1(double n)  { return n * log2(n); }
double f2(double n)  { return 12 * pow(n, 0.5); }
double f3(double n)  { return 1.0 / n; }
double f4(double n)  { return pow(n, log2(n)); }
double f5(double n)  { return 100 * n * n + 6 * n; }
double f6(double n)  { return pow(n, 0.51); }
double f7(double n)  { return n * n - 324; }
double f8(double n)  { return 50 * pow(n, 0.5); }
double f9(double n)  { return 2 * pow(n, 3); }
double f10(double n) { return pow(3, n); }
double f11(double n) { return pow(2, 32) * n; }
double f12(double n) { return log2(n); }

// Function pointer array
double (*funcs[NUM_FUNCS])(double) = {
    f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12
};

char *names[NUM_FUNCS] = {
    "n*log2(n)",
    "12*sqrt(n)",
    "1/n",
    "n^(log2(n))",
    "100*n^2+6n",
    "n^0.51",
    "n^2-324",
    "50*sqrt(n)",
    "2*n^3",
    "3^n",
    "2^32*n",
    "log2(n)"
};

// Struct to hold function values for sorting
typedef struct {
    char *name;
    double value;
} FuncVal;

int compare(const void *a, const void *b) {
    double diff = ((FuncVal*)a)->value - ((FuncVal*)b)->value;
    return (diff < 0) ? -1 : (diff > 0);
}

int main() {
    // Extended n values
    long nValues[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    int numN = sizeof(nValues)/sizeof(nValues[0]);

    printf("Dynamic Growth Comparison:\n\n");

    for(int i=0; i<numN; i++) {
        long n = nValues[i];
        printf("n = %ld \n", n);

        for(int j=0; j<NUM_FUNCS; j++) {
            printf("%-15s = %e\n", names[j], funcs[j](n));
        }
        printf("\n");
    }

    // Final asymptotic ordering at a large n
    long Nlarge = 1024;  
    FuncVal arr[NUM_FUNCS];

    for(int j=0; j<NUM_FUNCS; j++) {
        arr[j].name = names[j];
        arr[j].value = funcs[j](Nlarge);
    }

    qsort(arr, NUM_FUNCS, sizeof(FuncVal), compare);

    printf("Order of functions by growth at n = %ld:\n", Nlarge);
    for(int j=0; j<NUM_FUNCS; j++) {
        printf("%d. %-15s -> %e\n", j+1, arr[j].name, arr[j].value);
    }

    return 0;
}

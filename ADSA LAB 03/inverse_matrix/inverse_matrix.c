#include <stdio.h>

#define MAX 10   // Maximum matrix dimension

/* Display matrix */
void display(double A[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%8.3lf ", A[i][j]);
        printf("\n");
    }
}

int main() {
    int n;
    double A[MAX][MAX], inv[MAX][MAX];

    printf("Enter size of square matrix (n x n): ");
    scanf("%d", &n);

    printf("Enter elements of matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);

    /* Initialize inverse as identity matrix */
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inv[i][j] = (i == j) ? 1.0 : 0.0;

    /* Gauss–Jordan elimination */
    for (int i = 0; i < n; i++) {

        /* Ensure non-zero pivot */
        if (A[i][i] == 0) {
            int row = -1;
            for (int k = i + 1; k < n; k++) {
                if (A[k][i] != 0) {
                    row = k;
                    break;
                }
            }

            if (row == -1) {
                printf("Matrix is singular, cannot find inverse.\n");
                return 0;
            }

            /* Swap rows */
            for (int j = 0; j < n; j++) {
                double temp = A[i][j];
                A[i][j] = A[row][j];
                A[row][j] = temp;

                temp = inv[i][j];
                inv[i][j] = inv[row][j];
                inv[row][j] = temp;
            }
        }

        /* Normalize pivot row */
        double pivot = A[i][i];
        for (int j = 0; j < n; j++) {
            A[i][j] /= pivot;
            inv[i][j] /= pivot;
        }

        /* Eliminate other rows */
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = A[k][i];
                for (int j = 0; j < n; j++) {
                    A[k][j] -= factor * A[i][j];
                    inv[k][j] -= factor * inv[i][j];
                }
            }
        }
    }

    printf("Inverse Matrix:\n");
    display(inv, n);

    return 0;
}

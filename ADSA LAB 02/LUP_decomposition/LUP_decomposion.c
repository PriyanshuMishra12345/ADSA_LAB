#include <stdio.h>
#include <math.h>

#define N 3   // Matrix dimension

/* Perform LUP decomposition: A is overwritten with L and U */
int LUP_Decompose(double M[N][N], int perm[N]) {
    int i, j, k, pivotRow;
    double maxVal, absVal, temp;

    /* Initialize permutation vector */
    for (i = 0; i < N; i++) {
        perm[i] = i;
    }

    for (i = 0; i < N; i++) {
        maxVal = 0.0;
        pivotRow = i;

        /* Find pivot element */
        for (k = i; k < N; k++) {
            absVal = fabs(M[k][i]);
            if (absVal > maxVal) {
                maxVal = absVal;
                pivotRow = k;
            }
        }

        if (maxVal < 1e-12) {
            return 0;   // Singular matrix
        }

        /* Update permutation */
        if (pivotRow != i) {
            int t = perm[i];
            perm[i] = perm[pivotRow];
            perm[pivotRow] = t;
        }

        /* Swap rows in matrix */
        for (j = 0; j < N; j++) {
            temp = M[i][j];
            M[i][j] = M[pivotRow][j];
            M[pivotRow][j] = temp;
        }

        /* Gaussian elimination */
        for (j = i + 1; j < N; j++) {
            M[j][i] /= M[i][i];
            for (k = i + 1; k < N; k++) {
                M[j][k] -= M[j][i] * M[i][k];
            }
        }
    }
    return 1;
}

/* Display L, U, and permutation matrices */
void printLUP(double M[N][N], int perm[N]) {
    int i, j;
    double L[N][N] = {0}, U[N][N] = {0}, Pmat[N][N] = {0};

    /* Separate L and U matrices */
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i > j)
                L[i][j] = M[i][j];
            else if (i == j)
                L[i][j] = 1.0;

            if (i <= j)
                U[i][j] = M[i][j];
        }
    }

    /* Construct permutation matrix */
    for (i = 0; i < N; i++) {
        Pmat[i][perm[i]] = 1.0;
    }

    printf("L matrix:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            printf("%8.4f ", L[i][j]);
        printf("\n");
    }

    printf("\nU matrix:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            printf("%8.4f ", U[i][j]);
        printf("\n");
    }

    printf("\nP matrix:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            printf("%8.4f ", Pmat[i][j]);
        printf("\n");
    }
}

int main() {
    double A[N][N];
    int P[N];

    printf("Enter Matrix(3*3)\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    if (!LUP_Decompose(A, P)) {
        printf("Matrix is singular!\n");
        return -1;
    }

    printLUP(A, P);
    return 0;
}

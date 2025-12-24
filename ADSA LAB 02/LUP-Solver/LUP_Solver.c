#include <stdio.h>
#include <math.h>

#define N 3          // size of the matrix
#define EPS 1e-9     // tolerance for singularity check

/* Swap two rows in matrix and permutation vector */
void swapRows(double M[N][N], int perm[N], int rA, int rB) {
    for (int j = 0; j < N; j++) {
        double temp = M[rA][j];
        M[rA][j] = M[rB][j];
        M[rB][j] = temp;
    }
    int t = perm[rA];
    perm[rA] = perm[rB];
    perm[rB] = t;
}

/* Perform LUP decomposition in-place */
int LUP_Decompose(double M[N][N], int perm[N]) {
    for (int i = 0; i < N; i++)
        perm[i] = i;

    for (int k = 0; k < N; k++) {
        int pivot = k;
        double maxVal = fabs(M[k][k]);

        for (int i = k + 1; i < N; i++) {
            if (fabs(M[i][k]) > maxVal) {
                maxVal = fabs(M[i][k]);
                pivot = i;
            }
        }

        if (maxVal < EPS)
            return 0;   // singular matrix

        if (pivot != k)
            swapRows(M, perm, k, pivot);

        for (int i = k + 1; i < N; i++) {
            M[i][k] /= M[k][k];
            for (int j = k + 1; j < N; j++) {
                M[i][j] -= M[i][k] * M[k][j];
            }
        }
    }
    return 1;
}

/* Solve Ax = b using LUP factors */
void LUP_Solve(double M[N][N], int perm[N], double b[N], double x[N]) {
    double y[N];

    /* Forward substitution: Ly = Pb */
    for (int i = 0; i < N; i++) {
        y[i] = b[perm[i]];
        for (int j = 0; j < i; j++)
            y[i] -= M[i][j] * y[j];
    }

    /* Backward substitution: Ux = y */
    for (int i = N - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < N; j++)
            x[i] -= M[i][j] * x[j];
        x[i] /= M[i][i];
    }
}

int main() {
    double A[N][N], b[N], x[N];
    int P[N];

    printf("Enter the elements of matrix A (%dx%d):\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("A[%d][%d] = ", i, j);
            scanf("%lf", &A[i][j]);
        }
    }

    printf("Enter the elements of vector b (%d values):\n", N);
    for (int i = 0; i < N; i++) {
        printf("b[%d] = ", i);
        scanf("%lf", &b[i]);
    }

    if (!LUP_Decompose(A, P)) {
        printf("Matrix is singular!\n");
        return 1;
    }

    LUP_Solve(A, P, b, x);

    printf("\nSolution x:\n");
    for (int i = 0; i < N; i++) {
        if (fabs(x[i]) < EPS)
            x[i] = 0;   // remove negative zero
        printf("x[%d] = %.6f\n", i, x[i]);
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

/* Allocate memory for an n x n matrix */
int **createMatrix(int n) {
    int **mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        mat[i] = (int *)malloc(n * sizeof(int));
    return mat;
}

/* Matrix addition */
void matrixAdd(int **X, int **Y, int **Z, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Z[i][j] = X[i][j] + Y[i][j];
}

/* Matrix subtraction */
void matrixSub(int **X, int **Y, int **Z, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Z[i][j] = X[i][j] - Y[i][j];
}

/* Strassen’s multiplication algorithm */
void strassenMultiply(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int half = n / 2;

    /* Submatrices */
    int **A11 = createMatrix(half);
    int **A12 = createMatrix(half);
    int **A21 = createMatrix(half);
    int **A22 = createMatrix(half);
    int **B11 = createMatrix(half);
    int **B12 = createMatrix(half);
    int **B21 = createMatrix(half);
    int **B22 = createMatrix(half);
    int **C11 = createMatrix(half);
    int **C12 = createMatrix(half);
    int **C21 = createMatrix(half);
    int **C22 = createMatrix(half);
    int **M1  = createMatrix(half);
    int **M2  = createMatrix(half);
    int **M3  = createMatrix(half);
    int **M4  = createMatrix(half);
    int **M5  = createMatrix(half);
    int **M6  = createMatrix(half);
    int **M7  = createMatrix(half);
    int **T1  = createMatrix(half);
    int **T2  = createMatrix(half);

    /* Split matrices A and B */
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    /* Compute M1 to M7 */
    matrixAdd(A11, A22, T1, half);
    matrixAdd(B11, B22, T2, half);
    strassenMultiply(T1, T2, M1, half);

    matrixAdd(A21, A22, T1, half);
    strassenMultiply(T1, B11, M2, half);

    matrixSub(B12, B22, T2, half);
    strassenMultiply(A11, T2, M3, half);

    matrixSub(B21, B11, T2, half);
    strassenMultiply(A22, T2, M4, half);

    matrixAdd(A11, A12, T1, half);
    strassenMultiply(T1, B22, M5, half);

    matrixSub(A21, A11, T1, half);
    matrixAdd(B11, B12, T2, half);
    strassenMultiply(T1, T2, M6, half);

    matrixSub(A12, A22, T1, half);
    matrixAdd(B21, B22, T2, half);
    strassenMultiply(T1, T2, M7, half);

    /* Combine intermediate matrices */
    matrixAdd(M1, M4, T1, half);
    matrixSub(T1, M5, T2, half);
    matrixAdd(T2, M7, C11, half);

    matrixAdd(M3, M5, C12, half);
    matrixAdd(M2, M4, C21, half);

    matrixSub(M1, M2, T1, half);
    matrixAdd(T1, M3, T2, half);
    matrixAdd(T2, M6, C22, half);

    /* Merge into result matrix C */
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }
}

/* Print matrix */
void displayMatrix(int **M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter matrix size (power of 2): ");
    scanf("%d", &n);

    int **A = createMatrix(n);
    int **B = createMatrix(n);
    int **C = createMatrix(n);

    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    displayMatrix(A, n);

    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);
    displayMatrix(B, n);

    strassenMultiply(A, B, C, n);

    printf("Resultant matrix (A * B):\n");
    displayMatrix(C, n);

    return 0;
}

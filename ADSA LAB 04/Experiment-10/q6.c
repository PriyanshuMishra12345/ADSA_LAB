#include <stdio.h>
#include <stdlib.h>

#define MAX 16   // Supports up to 16x16 after padding

// Find next power of 2
int nextPowerOf2(int n) {
    int p = 1;
    while (p < n) p *= 2;
    return p;
}

// Add matrices
void addMatrix(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Subtract matrices
void subMatrix(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Strassen Algorithm
void strassen(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n/2;
    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
    int M1[MAX][MAX], M2[MAX][MAX], M3[MAX][MAX], M4[MAX][MAX];
    int M5[MAX][MAX], M6[MAX][MAX], M7[MAX][MAX];
    int T1[MAX][MAX], T2[MAX][MAX];

    // Split matrices
    for(int i=0;i<k;i++) {
        for(int j=0;j<k;j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+k];
            A21[i][j] = A[i+k][j];
            A22[i][j] = A[i+k][j+k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+k];
            B21[i][j] = B[i+k][j];
            B22[i][j] = B[i+k][j+k];
        }
    }

    addMatrix(k, A11, A22, T1);
    addMatrix(k, B11, B22, T2);
    strassen(k, T1, T2, M1);

    addMatrix(k, A21, A22, T1);
    strassen(k, T1, B11, M2);

    subMatrix(k, B12, B22, T2);
    strassen(k, A11, T2, M3);

    subMatrix(k, B21, B11, T2);
    strassen(k, A22, T2, M4);

    addMatrix(k, A11, A12, T1);
    strassen(k, T1, B22, M5);

    subMatrix(k, A21, A11, T1);
    addMatrix(k, B11, B12, T2);
    strassen(k, T1, T2, M6);

    subMatrix(k, A12, A22, T1);
    addMatrix(k, B21, B22, T2);
    strassen(k, T1, T2, M7);

    // Combine result blocks
    for(int i=0;i<k;i++) {
        for(int j=0;j<k;j++) {
            C[i][j]       = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j+k]     = M3[i][j] + M5[i][j];
            C[i+k][j]     = M2[i][j] + M4[i][j];
            C[i+k][j+k]   = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }
}

// Normal matrix multiply (for verification / fallback)
void normalMultiply(int r, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for(int i=0;i<r;i++)
        for(int j=0;j<r;j++) {
            C[i][j] = 0;
            for(int k=0;k<r;k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int main() {

    int n;
    int A[MAX][MAX] = {0}, B[MAX][MAX] = {0}, C[MAX][MAX] = {0};
    int Apadded[MAX][MAX] = {0}, Bpadded[MAX][MAX] = {0}, Cpadded[MAX][MAX] = {0};

    printf("Enter original matrix size (any n): ");
    scanf("%d", &n);

    if (n > MAX) {
        printf("Error: Max supported is %d\n", MAX);
        return 1;
    }

    // Read Matrix A
    printf("Enter Matrix A:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d", &A[i][j]);

    // Read Matrix B
    printf("Enter Matrix B:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d", &B[i][j]);

    int newSize = nextPowerOf2(n);
    printf("\nPadded size used = %d x %d\n", newSize, newSize);

    // Copy original matrices into padded matrices
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) {
            Apadded[i][j] = A[i][j];
            Bpadded[i][j] = B[i][j];
        }

    // Apply Strassen
    strassen(newSize, Apadded, Bpadded, Cpadded);

    // Remove padding
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            C[i][j] = Cpadded[i][j];

    // Output original size result
    printf("\nResult Matrix:\n");
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    return 0;
}


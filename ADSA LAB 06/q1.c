#include <stdio.h>
#include <stdlib.h>

#define MAX 20

void printTableau(float T[MAX][MAX], int rows, int cols) {
    printf("\nSimplex Tableau:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%8.2f ", T[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main() {
    int n, m;
    float T[MAX][MAX];

    // Input LP problem
    printf("Enter number of variables: ");
    scanf("%d", &n);

    printf("Enter number of constraints: ");
    scanf("%d", &m);

    int cols = n + m + 1;   // variables + slack + RHS
    int rows = m + 1;       // objective + constraints

    printf("\nEnter coefficients of constraints row-wise:\n");
    printf("(Format: coefficients of variables then RHS)\n");

    for (int i = 1; i <= m; i++) {
        printf("Constraint %d:\n", i);
        for (int j = 0; j < n; j++)
            scanf("%f", &T[i][j]);
        scanf("%f", &T[i][cols - 1]);  // RHS
    }

    printf("\nEnter coefficients of objective function (Z):\n");
    for (int j = 0; j < n; j++)
        scanf("%f", &T[0][j]);

    // Convert objective row to negative (for maximization)
    for (int j = 0; j < n; j++)
        T[0][j] = -T[0][j];

    // Add slack variables
    for (int i = 1; i <= m; i++) {
        for (int j = n; j < n + m; j++)
            T[i][j] = (j - n + 1 == i) ? 1 : 0;
    }

    // Objective RHS = 0
    T[0][cols - 1] = 0;

    int iter = 1;

    // Simplex algorithm loop
    while (1) {
        printf("\n----------------------------------\n");
        printf("Iteration %d:\n", iter++);
        printTableau(T, rows, cols);

        // Choose entering column
        int pivotCol = -1;
        float min = 0;
        for (int j = 0; j < cols - 1; j++) {
            if (T[0][j] < min) {
                min = T[0][j];
                pivotCol = j;
            }
        }

        if (pivotCol == -1)
            break;  // optimal reached

        // Choose leaving row by minimum ratio test
        int pivotRow = -1;
        float minRatio = 1e9;

        for (int i = 1; i < rows; i++) {
            if (T[i][pivotCol] > 0) {
                float ratio = T[i][cols - 1] / T[i][pivotCol];
                if (ratio < minRatio) {
                    minRatio = ratio;
                    pivotRow = i;
                }
            }
        }

        if (pivotRow == -1) {
            printf("Unbounded solution!\n");
            return 0;
        }

        // Pivot
        float pivot = T[pivotRow][pivotCol];

        // Normalize pivot row
        for (int j = 0; j < cols; j++)
            T[pivotRow][j] /= pivot;

        // Eliminate pivot column
        for (int i = 0; i < rows; i++) {
            if (i != pivotRow) {
                float factor = T[i][pivotCol];
                for (int j = 0; j < cols; j++)
                    T[i][j] -= factor * T[pivotRow][j];
            }
        }
    }

    // Print final solution
    printf("\n=================================\n");
    printf("OPTIMAL TABLEAU:\n");
    printTableau(T, rows, cols);

    printf("Optimal value of Z = %.2f\n", T[0][cols - 1]);

    // Extract variable values
    printf("\nValues of decision variables:\n");
    for (int j = 0; j < n; j++) {
        int oneRow = -1;
        int isBasic = 1;

        for (int i = 1; i < rows; i++) {
            if (T[i][j] == 1 && oneRow == -1)
                oneRow = i;
            else if (T[i][j] != 0)
                isBasic = 0;
        }

        if (isBasic && oneRow != -1)
            printf("x%d = %.2f\n", j + 1, T[oneRow][cols - 1]);
        else
            printf("x%d = 0\n", j + 1);
    }

    return 0;
}


#include <stdio.h>
#include <string.h>

#define MAX 101

int main() {
    char X[MAX], Y[MAX];
    int dp[MAX][MAX];

    // Take input from user
    printf("Enter first string: ");
    scanf("%s", X);

    printf("Enter second string: ");
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    // Fill DP table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) 
                            ? dp[i - 1][j] 
                            : dp[i][j - 1];
            }
        }
    }

    // Print LCS length
    printf("LCS Length: %d\n", dp[m][n]);

    // Backtrack to find LCS
    char lcs[MAX];
    int idx = dp[m][n];
    lcs[idx] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[idx - 1] = X[i - 1];
            i--;
            j--;
            idx--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // Print LCS
    printf("LCS: %s\n", lcs);

    return 0;
}


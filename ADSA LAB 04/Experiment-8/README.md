## Longest Common Subsequence (LCS)

### Problem Statement

This program finds the Longest Common Subsequence (LCS) of two given strings. A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements. The LCS problem aims to find the longest possible subsequence that is common to both input strings. This problem is a classic example demonstrating the power of dynamic programming.

### Related Algorithm: Longest Common Subsequence (LCS) using Dynamic Programming

The Longest Common Subsequence (LCS) problem is a fundamental problem in computer science with applications in fields like bioinformatics (e.g., comparing DNA sequences), text editors (e.g., diff utilities), and version control systems.

A naive approach to find the LCS would be highly inefficient (exponential time complexity). The problem exhibits optimal substructure and overlapping subproblems, making it well-suited for a dynamic programming approach.

**Dynamic Programming Approach:**

The dynamic programming solution typically involves constructing a 2D table (or matrix), let's call it `dp`, to store the lengths of the LCS for all prefixes of the two input strings.

Let `X` be the first string of length `m`, and `Y` be the second string of length `n`.
The `dp` table will have dimensions `(m+1) x (n+1)`.

1.  **Initialization**:
    *   The first row and first column of the `dp` table are initialized to `0`. This signifies that if one of the strings is empty, the LCS length is 0.

2.  **Filling the Table**:
    *   The table is filled in a bottom-up manner. For each cell `dp[i][j]` (representing the LCS of `X[0...i-1]` and `Y[0...j-1]`):
        *   **If `X[i-1] == Y[j-1]` (characters match)**:
            If the current characters at `X[i-1]` and `Y[j-1]` are the same, they can be part of the common subsequence. So, the length of the LCS is one more than the LCS of the preceding prefixes:
            `dp[i][j] = dp[i-1][j-1] + 1`
        *   **If `X[i-1] != Y[j-1]` (characters do not match)**:
            If the current characters do not match, we cannot include both. We take the maximum LCS length from two possibilities:
            *   LCS of `X[0...i-2]` and `Y[0...j-1]` (excluding `X[i-1]`), which is `dp[i-1][j]`.
            *   LCS of `X[0...i-1]` and `Y[0...j-2]` (excluding `Y[j-1]`), which is `dp[i][j-1]`.
            `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`

3.  **Result**: The value at `dp[m][n]` will contain the length of the Longest Common Subsequence of the entire strings `X` and `Y`.

**Reconstructing the LCS**:
To find the actual LCS string, one can backtrack through the `dp` table starting from `dp[m][n]`.
*   If `X[i-1] == Y[j-1]`, it means this character is part of the LCS, so we add it to the result and move diagonally up-left (`i--`, `j--`).
*   If `X[i-1] != Y[j-1]`, we move to the cell that corresponds to the larger value (either `dp[i-1][j]` or `dp[i][j-1]`) to trace the path that led to the longer subsequence.

**Time Complexity**: O(m * n), where `m` and `n` are the lengths of the two strings.
**Space Complexity**: O(m * n) for the `dp` table.

### Code Details

The `q4.c` file implements the LCS algorithm using dynamic programming:

*   **`MAX`**: A preprocessor macro defining the maximum length of the strings (101 characters to accommodate null terminator).
*   **`X[MAX]`, `Y[MAX]`**: Character arrays to store the input strings.
*   **`dp[MAX][MAX]`**: A 2D integer array representing the dynamic programming table.
*   **Input**: The program prompts the user to enter two strings.
*   **Table Filling**:
    *   Initializes the `dp` table with `0`s in the first row and column.
    *   Uses nested loops to fill the `dp` table based on the dynamic programming recurrence relations (matching characters or taking the maximum from adjacent cells).
*   **LCS Length**: After filling the table, `dp[m][n]` holds the length of the LCS, which is printed.
*   **LCS Reconstruction**:
    *   A character array `lcs[MAX]` is used to store the reconstructed LCS.
    *   The code backtracks from `dp[m][n]` using a `while` loop:
        *   If `X[i-1] == Y[j-1]`, the character is added to `lcs`, and `i` and `j` are decremented.
        *   If `X[i-1] != Y[j-1]`, it moves `i` or `j` (depending on which `dp` cell has the larger value) to trace back the path of the longest subsequence.
*   **Output**: The reconstructed LCS string is printed.

### Sample Input/Output

**Input:**

```
Enter first string: AGGTAB
Enter second string: GXTXAYB
```

**Output:**

```
LCS Length: 4
LCS: GTAB
```

**Another Sample Input/Output:**

**Input:**

```
Enter first string: ABCBDAB
Enter second string: BDCABA
```

**Output:**

```
LCS Length: 4
LCS: BCAB
```
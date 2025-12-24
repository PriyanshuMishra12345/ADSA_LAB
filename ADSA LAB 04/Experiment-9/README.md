## KMP and Rabin-Karp String Searching Algorithms

### Problem Statement

This program implements and demonstrates two popular and efficient string searching algorithms: Knuth-Morris-Pratt (KMP) and Rabin-Karp. Given a main text string and a pattern string, the program finds all occurrences (indices) where the pattern appears within the text using both algorithms, allowing for a comparison of their approaches.

### Related Algorithms: KMP and Rabin-Karp String Searching

String searching (or string matching) is the process of finding one or more occurrences of a "pattern" string within a larger "text" string. Naive string matching can be inefficient, especially for large texts and patterns. KMP and Rabin-Karp offer optimized solutions.

#### 1. Knuth-Morris-Pratt (KMP) Algorithm

The KMP algorithm optimizes string searching by avoiding re-examination of characters in the text that have already been matched. It achieves this by preprocessing the pattern to understand its internal structure.

**How it works:**

1.  **Preprocessing (LPS Array Construction)**:
    *   A "Longest Proper Prefix which is also Suffix" (LPS) array (also called a failure function) is computed for the pattern.
    *   `lps[i]` stores the length of the longest proper prefix of `pattern[0...i]` that is also a suffix of `pattern[0...i]`.
    *   This array tells the algorithm how many characters to shift the pattern when a mismatch occurs, utilizing previously matched portions.

2.  **Searching**:
    *   The algorithm compares characters of the pattern with characters in the text.
    *   When a match occurs, both text and pattern pointers advance.
    *   When a mismatch occurs, instead of shifting the pattern by one position (like naive search), the LPS array is consulted. The pattern is shifted forward by an amount determined by the `lps` value of the mismatched position, effectively aligning the longest proper prefix that is also a suffix of the matched part. This avoids unnecessary backtracking in the text.

**Time Complexity**: O(N + M), where N is the length of the text and M is the length of the pattern.
**Space Complexity**: O(M) for the LPS array.

#### 2. Rabin-Karp Algorithm

The Rabin-Karp algorithm uses hashing to quickly filter out impossible matching positions in the text, relying on character-by-character comparison only when hash values match.

**How it works:**

1.  **Hashing**:
    *   A hash value is computed for the pattern string.
    *   A hash value is computed for the first substring of the text (of the same length as the pattern).
    *   A suitable hash function (often a polynomial rolling hash) and a large prime number (`PRIME`) are used to minimize collisions and handle large numbers.

2.  **Rolling Hash**:
    *   For subsequent substrings of the text, a "rolling hash" technique is used. Instead of recalculating the hash for each new substring from scratch, the hash value is efficiently updated in constant time. This is done by subtracting the contribution of the character leaving the window and adding the contribution of the new character entering the window.

3.  **Comparison and Verification**:
    *   The hash of the pattern is compared with the hash of the current text substring.
    *   If the hashes match, there's a *potential* match. Since hash collisions are possible, a full character-by-character comparison (a "full check") is performed to confirm if it's a true match (to avoid "spurious hits").
    *   If hashes do not match, the algorithm immediately slides the window to the next position.

**Time Complexity**:
*   **Average Case**: O(N + M) (with good hash function and few collisions).
*   **Worst Case**: O(N * M) (if many hash collisions occur, leading to frequent character-by-character comparisons).
**Space Complexity**: O(1) for a single pattern.

### Code Details

The `q5.c` file implements both KMP and Rabin-Karp algorithms sequentially:

*   **`MAX`**: A preprocessor macro defining the maximum length of strings (500).
*   **`D`**: A constant `256` representing the number of characters in the input alphabet (e.g., ASCII size), used as the base for hashing.
*   **`PRIME`**: A prime number `101` used for modular arithmetic in the Rabin-Karp hash function to reduce hash values to a manageable range and minimize collisions.
*   **Input**: The program prompts the user to enter the `text` string and the `pattern` string.
*   **KMP Implementation**:
    *   **LPS Array (`lps[MAX]`)**: An array to store the Longest Proper Prefix which is also Suffix values for the pattern. It's built in a `for` loop before the search.
    *   **KMP Search**: Uses `i` for text traversal and `j` for pattern traversal. When a mismatch occurs, `j` is updated using `lps[j-1]` to shift the pattern efficiently.
*   **Rabin-Karp Implementation**:
    *   **Hash Calculation**: Computes the initial hash values for the pattern (`p`) and the first text window (`t`).
    *   **`h`**: A variable to store `D^(M-1) % PRIME`, used for efficiently removing the leading digit in the rolling hash.
    *   **Rolling Hash**: In the main search loop, the hash `t` is updated for each new window.
    *   **Match Check**: If `p == t`, a character-by-character comparison is performed to verify the match.

### Sample Input/Output

**Input:**

```
Enter the text: ABABABCABABABABCABAB
Enter the pattern: ABAB
```

**Output:**

```
Text: ABABABCABABABABCABAB
Pattern: ABAB

KMP matches at indices: 0 2 7 9 12 14
Rabin-Karp matches at indices: 0 2 7 9 12 14
```
*(Both algorithms correctly identify all occurrences of the pattern in the text.)*
## Knuth-Morris-Pratt (KMP) String Searching Algorithm

### Problem Statement

This program implements the Knuth-Morris-Pratt (KMP) algorithm for efficient string searching. Given a main `text` string and a `pattern` string, the program finds all occurrences of the `pattern` within the `text` and reports their starting indices. The KMP algorithm is known for its ability to avoid redundant character comparisons by preprocessing the pattern.

### Related Algorithm: Knuth-Morris-Pratt (KMP) Algorithm

The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that aims to find occurrences of a "pattern" string `P` within a "text" string `T`. Unlike naive string matching algorithms that might backtrack in the `text` string, KMP avoids this by intelligently shifting the pattern based on information learned from previous matches and mismatches.

**Core Idea:**

The KMP algorithm works by preprocessing the `pattern` to build an auxiliary array (the LPS array) that stores information about the longest proper prefix of the `pattern` that is also a suffix of any prefix of the `pattern`. This array guides the algorithm on how much to shift the `pattern` after a mismatch.

**Algorithm Steps:**

1.  **Preprocessing the Pattern (Building the LPS Array)**:
    *   An array, typically called `lps` (Longest Proper Prefix which is also Suffix), is constructed for the `pattern` string.
    *   For each index `i` in the `pattern`, `lps[i]` stores the length of the longest proper prefix of `pattern[0...i]` that is also a suffix of `pattern[0...i]`.
    *   This array effectively tells us, upon a mismatch, the longest prefix of the pattern that has just matched, allowing us to shift the pattern correctly without re-checking characters that are guaranteed to match.

2.  **Searching for the Pattern**:
    *   Two pointers are maintained: `i` for the `text` string and `j` for the `pattern` string.
    *   Characters `text[i]` and `pattern[j]` are compared.
    *   **Match**: If `text[i] == pattern[j]`, both pointers are incremented (`i++`, `j++`).
    *   **Pattern Found**: If `j` reaches the length of the `pattern` (`j == m`), it means an occurrence of the `pattern` has been found starting at index `i - j` in the `text`. After finding a match, the algorithm does not stop but continues searching for further occurrences by updating `j = lps[j-1]` (effectively shifting the pattern).
    *   **Mismatch**: If `text[i] != pattern[j]`:
        *   If `j` is not `0` (meaning some part of the pattern has already matched), the `pattern` is shifted by setting `j = lps[j-1]`. This means we try to match the next potential prefix of the pattern.
        *   If `j` is `0` (meaning no characters of the pattern have matched yet or we've shifted past the last possible prefix match), we simply advance the `text` pointer (`i++`).

**Time Complexity**: O(N + M), where N is the length of the `text` and M is the length of the `pattern`. This includes O(M) for preprocessing the pattern and O(N) for the search phase.
**Space Complexity**: O(M) for storing the LPS array.

### Code Details

The `q3.c` file implements the KMP algorithm using dynamic memory allocation for input strings and the LPS array:

*   **`buildLPS(const char *pattern, int m, int *lps)`**:
    *   Takes the `pattern` string, its length `m`, and an integer array `lps` to fill.
    *   It calculates the `lps` array based on the described algorithm: `len` keeps track of the length of the current longest proper prefix suffix, and `i` iterates through the pattern to fill `lps[i]`.
*   **`KMPsearch(const char *text, const char *pattern)`**:
    *   Takes the `text` and `pattern` strings as input.
    *   Calculates their lengths `n` and `m`.
    *   Handles the edge case where the pattern is empty.
    *   Dynamically allocates memory for the `lps` array using `malloc`.
    *   Calls `buildLPS` to populate the `lps` array.
    *   Implements the main searching logic using pointers `i` (for `text`) and `j` (for `pattern`), as described in the algorithm steps.
    *   Prints the indices where the `pattern` is found.
    *   Frees the allocated `lps` array.
*   **`main` function**:
    *   Dynamically allocates memory for the `text` and `pattern` strings to allow for flexible input sizes.
    *   Prompts the user to enter the `text` and `pattern`. It uses `fgets` and `strcspn` to read entire lines, including spaces, and remove the trailing newline character.
    *   Calls `KMPsearch` to perform the string matching.
    *   Frees the dynamically allocated memory for `text` and `pattern`.

### Sample Input/Output

**Input:**

```
Enter the text: ABABDABACDABABCABAB
Enter the pattern: ABABCABAB
```

**Output:**

```
--- KMP Search Result ---
Pattern found at index 10
```
*(The pattern "ABABCABAB" is found starting at index 10 in the text "ABABDABACDABABCABAB".)*

**Another Sample Input/Output:**

**Input:**

```
Enter the text: AAAAAAAAAA
Enter the pattern: AAA
```

**Output:**

```
--- KMP Search Result ---
Pattern found at index 0
Pattern found at index 1
Pattern found at index 2
Pattern found at index 3
Pattern found at index 4
Pattern found at index 5
Pattern found at index 6
Pattern found at index 7
```
*(Multiple overlapping occurrences are correctly identified.)*
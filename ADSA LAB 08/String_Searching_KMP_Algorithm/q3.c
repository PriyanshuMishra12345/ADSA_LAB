#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to build LPS (Longest Prefix Suffix) array
void buildLPS(const char *pattern, int m, int *lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Search Function
void KMPsearch(const char *text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    // Edge case: empty pattern
    if (m == 0) {
        printf("Invalid: Pattern is empty.\n");
        return;
    }

    int *lps = (int*)malloc(m * sizeof(int));
    if (!lps) {
        printf("Memory allocation failed.\n");
        return;
    }

    buildLPS(pattern, m, lps);

    int i = 0, j = 0;
    int found = 0;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
            found = 1;
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    if (!found)
        printf("Pattern not found in text.\n");

    free(lps);
}

int main() {
    char *text = (char*)malloc(1000);
    char *pattern = (char*)malloc(200);

    if (!text || !pattern) {
        printf("Memory allocation error.\n");
        return 1;
    }

    printf("Enter the text: ");
    fgets(text, 1000, stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter the pattern: ");
    fgets(pattern, 200, stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    printf("\n--- KMP Search Result ---\n");
    KMPsearch(text, pattern);

    free(text);
    free(pattern);

    return 0;
}


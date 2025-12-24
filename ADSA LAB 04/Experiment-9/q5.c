#include <stdio.h>
#include <string.h>

#define D 256
#define PRIME 101
#define MAX 500

int main() {
    char text[MAX], pattern[MAX];

    // Take input from user
    printf("Enter the text: ");
    scanf("%s", text);

    printf("Enter the pattern: ");
    scanf("%s", pattern);

    int n = strlen(text);
    int m = strlen(pattern);

    if (m > n) {
        printf("Pattern is longer than text.\n");
        return 0;
    }

    printf("\nText: %s\n", text);
    printf("Pattern: %s\n\n", pattern);

    // ===================== KMP =====================

    int lps[MAX];
    int i, j;

    // Build LPS
    lps[0] = 0;
    j = 0;
    for (i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j])
            j = lps[j - 1];
        if (pattern[i] == pattern[j])
            j++;
        lps[i] = j;
    }

    // KMP search
    printf("KMP matches at indices: ");
    i = 0;
    j = 0;
    int found = 0;

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("%d ", i - j);
            found = 1;
            j = lps[j - 1];
        }
        else if (i < n && text[i] != pattern[j]) {
            if (j > 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    if (!found)
        printf("No match");

    printf("\n");

    // ===================== RABIN KARP =====================

    int p = 0, t = 0, h = 1;

    for (i = 0; i < m - 1; i++)
        h = (h * D) % PRIME;

    for (i = 0; i < m; i++) {
        p = (D * p + pattern[i]) % PRIME;
        t = (D * t + text[i]) % PRIME;
    }

    printf("Rabin-Karp matches at indices: ");
    found = 0;

    for (i = 0; i <= n - m; i++) {

        if (p == t) {
            int ok = 1;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                printf("%d ", i);
                found = 1;
            }
        }

        if (i < n - m) {
            t = (D * (t - text[i] * h) + text[i + m]) % PRIME;
            if (t < 0)
                t += PRIME;
        }
    }

    if (!found)
        printf("No match");

    printf("\n");

    return 0;
}


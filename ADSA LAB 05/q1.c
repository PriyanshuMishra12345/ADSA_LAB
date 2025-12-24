#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 50

int nU, nV;
int graph[MAX][MAX];
int matchV[MAX];
bool visited[MAX];

// DFS to check matching for U[u]
bool bpm(int u) {
    for (int v = 0; v < nV; v++) {
        if (graph[u][v] && !visited[v]) {
            visited[v] = true;

            // if v is free or reassignable
            if (matchV[v] == -1 || bpm(matchV[v])) {
                matchV[v] = u;
                return true;
            }
        }
    }
    return false;
}

// Returns maximum matching size
int maxBPM() {
    memset(matchV, -1, sizeof(matchV));
    int result = 0;

    for (int u = 0; u < nU; u++) {
        memset(visited, false, sizeof(visited));
        if (bpm(u))
            result++;
    }
    return result;
}

int main() {

    printf("Enter number of vertices in set U and V: ");
    scanf("%d %d", &nU, &nV);

    if (nU > MAX || nV > MAX || nU <= 0 || nV <= 0) {
        printf("Invalid size! 1 ≤ U,V ≤ %d\n", MAX);
        return 1;
    }

    printf("Enter adjacency matrix (%d x %d):\n", nU, nV);
    for (int i = 0; i < nU; i++) {
        for (int j = 0; j < nV; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] != 0 && graph[i][j] != 1) {
                printf("Error: Adjacency matrix must contain only 0 or 1\n");
                return 1;
            }
        }
    }

    int result = maxBPM();

    printf("\nMaximum Matching = %d\n", result);
    printf("Matched Pairs (U -> V):\n");

    int matched = 0;
    for (int v = 0; v < nV; v++) {
        if (matchV[v] != -1) {
            printf("U%d -> V%d\n", matchV[v], v);
            matched++;
        }
    }

    if (!matched)
        printf("No matches found\n");

    return 0;
}


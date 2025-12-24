#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 99999
#define MAX 20   // Maximum number of vertices

/* -------------------- GLOBAL DATA -------------------- */
int adj[MAX][MAX];
int vertices;

/* -------------------- READ GRAPH (SIF FORMAT) -------------------- */

int findIndex(char names[MAX][10], char *node, int *total) {
    for (int i = 0; i < *total; i++) {
        if (strcmp(names[i], node) == 0)
            return i;
    }
    strcpy(names[*total], node);
    (*total)++;
    return (*total) - 1;
}

void readGraphSIF() {
    char a[10], b[10];
    int weight;
    char names[MAX][10];
    int count = 0;

    printf("Enter edges in SIF format (u v w). Type END to stop:\n");

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            adj[i][j] = (i == j) ? 0 : INF;

    while (1) {
        scanf("%s", a);
        if (strcmp(a, "END") == 0)
            break;

        scanf("%s %d", b, &weight);

        int u = findIndex(names, a, &count);
        int v = findIndex(names, b, &count);

        adj[u][v] = weight;   // directed
        adj[v][u] = weight;   // undirected (optional)
    }

    vertices = count;

    printf("\nGraph adjacency matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (adj[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", adj[i][j]);
        }
        printf("\n");
    }
}

/* -------------------- DIJKSTRA ALGORITHM -------------------- */
void runDijkstra(int source) {
    int dist[MAX], used[MAX];

    for (int i = 0; i < vertices; i++) {
        dist[i] = INF;
        used[i] = 0;
    }
    dist[source] = 0;

    for (int c = 0; c < vertices - 1; c++) {
        int u = -1, minVal = INF;

        for (int i = 0; i < vertices; i++) {
            if (!used[i] && dist[i] < minVal) {
                minVal = dist[i];
                u = i;
            }
        }

        used[u] = 1;

        for (int v = 0; v < vertices; v++) {
            if (!used[v] && adj[u][v] != INF &&
                dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
            }
        }
    }

    printf("\nDijkstra (source %d):\n", source);
    for (int i = 0; i < vertices; i++) {
        if (dist[i] == INF)
            printf("Node %d: INF\n", i);
        else
            printf("Node %d: %d\n", i, dist[i]);
    }
}

/* -------------------- FLOYD-WARSHALL -------------------- */
void runFloydWarshall() {
    int dist[MAX][MAX];

    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            dist[i][j] = adj[i][j];

    for (int k = 0; k < vertices; k++)
        for (int i = 0; i < vertices; i++)
            for (int j = 0; j < vertices; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    printf("\nFloyd-Warshall All-Pairs Shortest Paths:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", dist[i][j]);
        }
        printf("\n");
    }
}

/* -------------------- MAIN MENU -------------------- */
int main() {
    int option, src;

    while (1) {
        printf("\n--- Graph Algorithms ---\n");
        printf("1. Read Graph (SIF)\n");
        printf("2. Dijkstra (Single Source)\n");
        printf("3. Floyd-Warshall (All Pairs)\n");
        printf("4. Exit\nChoice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                readGraphSIF();
                break;

            case 2:
                printf("Enter source vertex index (0-%d): ", vertices - 1);
                scanf("%d", &src);
                runDijkstra(src);
                break;

            case 3:
                runFloydWarshall();
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

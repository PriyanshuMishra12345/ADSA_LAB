#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define INF 999999

typedef struct {
    char name[10];
} Vertex;

int findVertexIndex(Vertex vertices[], int *count, char name[]) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(vertices[i].name, name) == 0)
            return i;
    }

    if (*count >= MAX) {
        printf("Vertex limit exceeded\n");
        exit(1);
    }

    strcpy(vertices[*count].name, name);
    (*count)++;
    return (*count - 1);
}

int minKey(int key[], int mstSet[], int n) {
    int min = INF, index = -1;
    for (int i = 0; i < n; i++)
        if (!mstSet[i] && key[i] < min) {
            min = key[i];
            index = i;
        }
    return index;
}

void primMST(int graph[MAX][MAX], Vertex vertices[], int n) {
    int parent[MAX], key[MAX], mstSet[MAX];

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < n - 1; i++) {

        int u = minKey(key, mstSet, n);
        if (u == -1) {
            printf("Graph is disconnected. MST not possible.\n");
            return;
        }

        mstSet[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] < INF && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("\nMinimum Spanning Tree:\n");
    int total = 0;
    for (int i = 1; i < n; i++) {
        printf("%s - %s : %d\n",
               vertices[parent[i]].name, vertices[i].name,
               graph[i][parent[i]]);
        total += graph[i][parent[i]];
    }
    printf("Total Cost = %d\n", total);
}

int main() {
    FILE *fp;
    char fileName[50];
    printf("Enter input file name: ");
    scanf("%s", fileName);

    fp = fopen(fileName, "r");
    if (!fp) {
        printf("Error opening file\n");
        return 1;
    }

    Vertex vertices[MAX];
    int graph[MAX][MAX];

    for(int i=0;i<MAX;i++)
      for(int j=0;j<MAX;j++)
        graph[i][j] = INF;

    int count = 0;
    char u[10], v[10];
    int w;

    while (fscanf(fp, "%s %s %d", u, v, &w) == 3) {
        int i = findVertexIndex(vertices, &count, u);
        int j = findVertexIndex(vertices, &count, v);
        graph[i][j] = graph[j][i] = w;
    }

    fclose(fp);

    if (count == 0) {
        printf("Empty graph\n");
        return 1;
    }

    primMST(graph, vertices, count);
    return 0;
}


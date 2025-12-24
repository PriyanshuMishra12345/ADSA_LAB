#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char src[10];
    char dest[10];
    int weight;
} Edge;

typedef struct {
    char name[10];
} Vertex;

/* Insert or return existing vertex index */
int findVertexIndex(Vertex vertices[], int *count, char name[]) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(vertices[i].name, name) == 0)
            return i;
    }

    if (*count >= MAX) {
        printf("Vertex limit exceeded!\n");
        exit(1);
    }

    strcpy(vertices[*count].name, name);
    (*count)++;
    return *count - 1;
}

/* Lookup only (no insert) */
int getVertexIndex(Vertex vertices[], int V, char name[]) {
    for (int i = 0; i < V; i++) {
        if (strcmp(vertices[i].name, name) == 0)
            return i;
    }
    return -1;
}

int findParent(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = findParent(parent, parent[i]);
    return parent[i];
}

void unionSet(int parent[], int rank[], int x, int y) {
    int xroot = findParent(parent, x);
    int yroot = findParent(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int compareEdges(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->weight - e2->weight;
}

void kruskalMST(Edge edges[], Vertex vertices[], int V, int E) {

    qsort(edges, E, sizeof(Edge), compareEdges);

    int parent[MAX], rank[MAX];

    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    Edge result[MAX];
    int e = 0;
    int i = 0;
    int totalCost = 0;

    while (e < V - 1 && i < E) {

        Edge next = edges[i++];

        int srcIndex = getVertexIndex(vertices, V, next.src);
        int destIndex = getVertexIndex(vertices, V, next.dest);

        if (srcIndex == -1 || destIndex == -1) {
            printf("Invalid vertex detected in edge %s - %s\n",
                    next.src, next.dest);
            continue;
        }

        int x = findParent(parent, srcIndex);
        int y = findParent(parent, destIndex);

        if (x != y) {
            result[e++] = next;
            unionSet(parent, rank, x, y);
            totalCost += next.weight;
        }
    }

    printf("\n------ MINIMUM SPANNING TREE ------\n");
    for (int j = 0; j < e; j++)
        printf("%s -- %s  (Weight = %d)\n",
               result[j].src, result[j].dest, result[j].weight);

    printf("----------------------------------\n");
    printf("TOTAL COST = %d\n", totalCost);
}

int main() {

    FILE *fp;
    char fileName[50];

    printf("Enter input file name: ");
    scanf("%s", fileName);

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    Edge edges[MAX];
    Vertex vertices[MAX];
    int Vcount = 0, Ecount = 0;

    char u[10], v[10];
    int w;

    while (fscanf(fp, "%s %s %d", u, v, &w) == 3) {

        if (Ecount >= MAX) {
            printf("Edge limit exceeded!\n");
            exit(1);
        }

        strcpy(edges[Ecount].src, u);
        strcpy(edges[Ecount].dest, v);
        edges[Ecount].weight = w;

        findVertexIndex(vertices, &Vcount, u);
        findVertexIndex(vertices, &Vcount, v);

        Ecount++;
    }

    fclose(fp);

    if (Ecount == 0) {
        printf("Empty graph file.\n");
        return 1;
    }

    printf("\nGraph Loaded:\nVertices = %d, Edges = %d\n", Vcount, Ecount);

    kruskalMST(edges, vertices, Vcount, Ecount);

    return 0;
}


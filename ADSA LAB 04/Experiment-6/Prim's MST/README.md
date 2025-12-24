## Prim's Algorithm for Minimum Spanning Tree (MST)

### Problem Statement

This program implements Prim's algorithm to find the Minimum Spanning Tree (MST) of a given connected, undirected, and weighted graph. The graph data, including vertices and edge weights, is read from an external file (`graph.txt`). An MST is a subgraph that connects all vertices in the original graph with the minimum possible total sum of edge weights, without forming any cycles.

### Related Algorithm: Prim's Algorithm

Prim's algorithm is a greedy algorithm used to find a Minimum Spanning Tree (MST) for a connected, undirected, and weighted graph. Unlike Kruskal's algorithm, which starts with edges, Prim's algorithm starts with a single vertex and grows the MST by iteratively adding the "cheapest" edge that connects a vertex already in the MST to a vertex not yet in the MST.

**Key Concepts:**

*   **Greedy Approach**: At each step, the algorithm makes a locally optimal choice by selecting the edge with the minimum weight that connects a vertex in the growing MST to a vertex outside it.
*   **Connected Graph**: The algorithm assumes the input graph is connected; otherwise, it cannot form a single spanning tree for all vertices.
*   **Weighted Edges**: Each edge must have a numerical weight.

**Algorithm Steps:**

1.  **Initialization**:
    *   Choose an arbitrary starting vertex (e.g., vertex 0) to be included in the MST.
    *   Assign a `key` value to every vertex: 0 for the starting vertex and infinity (`INF`) for all others. The `key` value represents the minimum weight of an edge connecting the vertex to the MST found so far.
    *   Initialize a `parent` array to store the MST structure, where `parent[v]` will store the parent of vertex `v` in the MST.
    *   Initialize an `mstSet` boolean array, where `mstSet[v]` is true if vertex `v` is already included in the MST, and false otherwise.

2.  **Iterative Growth**:
    *   Repeat `V-1` times (where `V` is the number of vertices) to include all vertices in the MST:
        *   **Select Minimum Key Vertex**: Pick a vertex `u` from the set of vertices not yet included in the MST (`mstSet[u]` is false) that has the minimum `key` value.
        *   **Add to MST**: Add `u` to the `mstSet` (mark `mstSet[u]` as true).
        *   **Update Neighbors' Key Values**: For all neighbors `v` of `u`:
            *   If `v` is not yet in the MST (`mstSet[v]` is false) and there is an edge `(u, v)`:
            *   If the weight of edge `(u, v)` is less than `key[v]`, update `key[v]` to `graph[u][v]` and set `parent[v] = u`. This means a shorter edge to connect `v` to the MST has been found.

3.  **Result**: After `V-1` iterations, the `parent` array will define the MST, and the sum of the `key` values (excluding the starting vertex's 0) will give the total minimum cost.

### Code Details

The `q2.c` file implements Prim's algorithm using an adjacency matrix representation for the graph:

*   **`MAX`**: A preprocessor macro for the maximum number of vertices.
*   **`INF`**: A large integer value representing infinity.
*   **`Vertex` struct**: Stores the name of a vertex.
*   **`findVertexIndex(Vertex vertices[], int *count, char name[])`**: A utility function that maps a vertex name to a unique integer index, adding new vertices as they are encountered.
*   **`minKey(int key[], int mstSet[], int n)`**: Finds the vertex `u` not yet in `mstSet` that has the minimum `key` value. This is a crucial greedy step.
*   **`primMST(int graph[MAX][MAX], Vertex vertices[], int n)`**: The main Prim's algorithm implementation.
    *   Initializes `parent`, `key`, and `mstSet` arrays.
    *   Sets `key[0] = 0` (starting vertex) and `parent[0] = -1`.
    *   Iterates `n-1` times, calling `minKey` to select the next vertex `u`.
    *   Updates `mstSet[u]` to true.
    *   Iterates through all possible neighbors `v` of `u` and updates their `key` and `parent` values if a shorter connection to the MST is found.
    *   After the loop, it prints the edges forming the MST and calculates the `total` cost using the `parent` and `key` arrays. It also handles disconnected graphs.

The `main` function:
1.  Prompts the user for an input file name (e.g., `graph.txt`).
2.  Reads edges (source vertex name, destination vertex name, weight) from the file.
3.  Uses `findVertexIndex` to map vertex names to integer indices.
4.  Populates the `graph` (adjacency matrix), ensuring it's an undirected graph (`graph[i][j] = graph[j][i] = w`). Non-existent edges are represented by `INF`.
5.  Calls `primMST` to compute and print the MST.

### Sample Input/Output

**Input (from `graph.txt`):**

```
A B 1
A C 4
B C 2
B D 5
C D 3
```

**Output:**

```
Enter input file name: graph.txt

Minimum Spanning Tree:
A - B : 1
B - C : 2
C - D : 3
Total Cost = 6
```
*(This output shows the edges that form the Minimum Spanning Tree and their total combined weight.)*
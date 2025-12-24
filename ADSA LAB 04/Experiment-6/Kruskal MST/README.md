## Kruskal's Algorithm for Minimum Spanning Tree (MST)

### Problem Statement

This program implements Kruskal's algorithm to find the Minimum Spanning Tree (MST) of a given connected, undirected, and weighted graph. The graph data is read from an external file (`graph.txt`). An MST is a subset of the graph's edges that connects all the vertices without forming any cycles, with the minimum possible total edge weight.

### Related Algorithm: Kruskal's Algorithm

Kruskal's algorithm is a greedy algorithm in graph theory that finds an MST for a connected, undirected, and weighted graph. It works by iteratively adding the smallest-weight edges that do not form a cycle, until all vertices are connected.

**Algorithm Steps:**

1.  **Initialize**:
    *   Create a list of all edges in the graph.
    *   Sort all edges in non-decreasing order of their weights.
    *   Initialize an empty set (forest) to store the MST.
    *   Create a Disjoint Set Union (DSU) data structure where each vertex is initially in its own separate set. The DSU is used to efficiently detect cycles.

2.  **Iterate and Select Edges**:
    *   Iterate through the sorted list of edges, starting with the one with the smallest weight.
    *   For each edge `(u, v)` with weight `w`:
        *   **Check for Cycle**: Use the DSU's `findParent` operation to determine if `u` and `v` already belong to the same connected component (i.e., if adding this edge would create a cycle).
        *   **Add to MST**: If `u` and `v` are in different components, add the edge `(u, v)` to the MST set, and perform a `unionSet` operation on `u` and `v` in the DSU. This merges their respective components.
        *   **Discard**: If `u` and `v` are already in the same component, discard the edge as it would form a cycle.
    *   Continue this process until the MST set contains `V - 1` edges (where `V` is the number of vertices) or all edges have been processed.

3.  **Result**: The set of `V - 1` edges forms the Minimum Spanning Tree.

**Time Complexity**: The dominant factors are sorting the edges (E log E, where E is the number of edges) and DSU operations (approximately E * α(V), where α is the inverse Ackermann function, which is nearly constant). So, the total time complexity is generally O(E log E) or O(E log V).

### Code Details

The `q1.c` file implements Kruskal's algorithm using a Disjoint Set Union (DSU) data structure:

*   **`Edge` struct**: Represents an edge with `src` (source vertex name), `dest` (destination vertex name), and `weight`.
*   **`Vertex` struct**: Represents a vertex with its `name`.
*   **`vertices[MAX]`**: An array to store unique vertex names.
*   **`edges[MAX]`**: An array to store all graph edges.
*   **`MAX`**: A preprocessor macro for maximum number of vertices/edges.
*   **`findVertexIndex(Vertex vertices[], int *count, char name[])`**: A utility function to get the integer index of a vertex name. If the name is new, it's added to the `vertices` array.
*   **DSU Functions**:
    *   **`findParent(int parent[], int i)`**: Finds the representative (parent) of the set containing element `i` using path compression.
    *   **`unionSet(int parent[], int rank[], int x, int y)`**: Merges the sets containing `x` and `y` using union by rank.
*   **`compareEdges(const void *a, const void *b)`**: A comparison function used by `qsort` to sort edges based on their weights.
*   **`kruskalMST(Edge edges[], Vertex vertices[], int V, int E)`**: The main Kruskal's algorithm implementation.
    *   Sorts all edges using `qsort`.
    *   Initializes `parent` and `rank` arrays for the DSU.
    *   Iterates through the sorted edges, using `findParent` to check for cycles and `unionSet` to merge components.
    *   Stores the edges forming the MST in the `result` array and calculates the `totalCost`.
    *   Prints the MST edges and their total cost.

The `main` function:
1.  Prompts the user to enter the input file name (expected to be `graph.txt`).
2.  Opens the specified file and reads graph edge data (source, destination, weight).
3.  Populates the `edges` and `vertices` arrays, assigning unique indices to vertex names.
4.  Calls `kruskalMST` to find and print the MST.

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

Graph Loaded:
Vertices = 4, Edges = 5

------ MINIMUM SPANNING TREE ------
A -- B  (Weight = 1)
B -- C  (Weight = 2)
C -- D  (Weight = 3)
----------------------------------
TOTAL COST = 6
```
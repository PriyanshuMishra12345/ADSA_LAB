## Maximum Bipartite Matching

### Problem Statement

This program finds the maximum cardinality matching in a bipartite graph. A bipartite graph consists of two disjoint sets of vertices, and edges only connect vertices from one set to vertices in the other. A matching is a subset of edges where no two edges share a common vertex. A maximum matching is one with the largest possible number of edges. This implementation uses a Depth-First Search (DFS) based approach to find augmenting paths, a common technique derived from network flow algorithms.

### Related Algorithm: Maximum Bipartite Matching (using DFS and Augmenting Paths)

Finding a maximum bipartite matching is a classic problem in graph theory with applications in diverse areas such as scheduling, resource allocation, and job assignments. The algorithm employed here is a common way to solve it, often conceptually linked to the Ford-Fulkerson algorithm for maximum flow.

**Key Concepts:**

*   **Bipartite Graph**: A graph `G = (V, E)` where the set of vertices `V` can be partitioned into two disjoint sets, say `U` and `V` (often denoted `X` and `Y`), such that every edge in `E` connects a vertex in `U` to one in `V`. There are no edges within `U` or within `V`.
*   **Matching**: A matching `M` in a graph is a set of edges such that no two edges in `M` share a common vertex.
*   **Maximum Matching**: A matching `M` is maximum if no other matching in the graph has more edges than `M`.
*   **Augmenting Path**: An alternating path with respect to a matching `M` is a path whose edges alternate between being in `M` and not in `M`. An augmenting path is an alternating path that starts and ends at unmatched vertices. The critical property of an augmenting path is that if you "flip" its edges (remove matched edges from `M` and add unmatched edges to `M`), the size of the matching increases by one.
*   **Berge's Lemma**: A matching `M` is maximum if and only if there are no `M`-augmenting paths. This theorem is the foundation for this algorithm.

**Algorithm Steps (DFS-based Augmenting Path Search):**

1.  **Initialize**: Start with an empty matching. The `matchV` array is initialized with -1, indicating that all vertices in set `V` are initially unmatched.
2.  **Iterate through vertices in U**: For each vertex `u` in set `U`:
    *   **Reset Visited Status**: Clear the `visited` array (mark all vertices in set `V` as unvisited) for the current DFS traversal. This is crucial because `visited` tracks nodes visited in a *single* DFS call, not globally.
    *   **Find Augmenting Path**: Call a DFS function (`bpm` in the code) starting from `u`. The goal of this DFS is to find an augmenting path.
        *   The DFS explores neighbors `v` of `u` (edges `(u, v)` that are not yet part of the matching).
        *   If `v` is unvisited: Mark `v` as visited.
        *   **Case 1: `v` is unmatched**: If `v` is unmatched (`matchV[v] == -1`), an augmenting path has been found. The edge `(u, v)` is added to the matching by setting `matchV[v] = u`. The DFS returns `true`.
        *   **Case 2: `v` is matched**: If `v` is matched to some `u'` (`matchV[v] = u'`), the DFS tries to find an augmenting path from `u'` (the current match of `v`). If `bpm(u')` returns `true` (meaning an augmenting path was found from `u'` to some other unmatched `V` vertex), then `(u, v)` can be added to the matching by setting `matchV[v] = u`. The DFS returns `true`.
    *   **Augment Matching**: If the `bpm(u)` function returns `true`, it means an augmenting path was found starting from `u`, and the matching size has increased by one. Increment the `result` counter.
3.  **Result**: After iterating through all vertices in `U`, the `result` will be the size of the maximum bipartite matching. The `matchV` array will contain the actual matched pairs.

### Code Details

The `q1.c` file implements the Maximum Bipartite Matching algorithm:

*   **`MAX`**: A preprocessor macro defining the maximum number of vertices (50).
*   **`nU`, `nV`**: Global integers representing the number of vertices in set U and set V, respectively.
*   **`graph[MAX][MAX]`**: An adjacency matrix where `graph[u][v] = 1` if there's an edge from vertex `u` in set U to vertex `v` in set V, and `0` otherwise.
*   **`matchV[MAX]`**: An array where `matchV[v] = u` indicates that vertex `v` from set V is matched with vertex `u` from set U. `-1` means `v` is unmatched.
*   **`visited[MAX]`**: A boolean array used during DFS (`bpm` function) to keep track of visited vertices in set V in the current path exploration, preventing cycles within a single DFS call.
*   **`bpm(int u)`**: This function performs a Depth-First Search starting from a vertex `u` in set U to find an augmenting path.
    *   It iterates through all vertices `v` in set V.
    *   If an edge `(u,v)` exists (`graph[u][v]`) and `v` has not been visited in the current DFS:
        *   Mark `v` as visited.
        *   If `v` is unmatched (`matchV[v] == -1`) or if `bpm(matchV[v])` (recursively finding an augmenting path from `v`'s current match `u'`) is successful:
            *   Then `u` can be matched with `v`, and the path is augmented. Set `matchV[v] = u` and return `true`.
    *   If no augmenting path is found from `u`, return `false`.
*   **`maxBPM()`**: The main function to calculate the maximum bipartite matching.
    *   Initializes `matchV` to -1 (all unmatched).
    *   Iterates through each vertex `u` in set U.
    *   For each `u`, it resets `visited` array and calls `bpm(u)`. If `bpm(u)` returns true, it means a new augmenting path was found, and the matching size (`result`) is incremented.
    *   Returns the total `result`.

The `main` function:
1.  Prompts the user to enter the number of vertices in sets U and V (`nU`, `nV`).
2.  Prompts the user to enter the `nU x nV` adjacency matrix, consisting of only 0s and 1s.
3.  Calls `maxBPM()` to compute the maximum matching size.
4.  Prints the "Maximum Matching" size.
5.  Prints the actual "Matched Pairs" (`U -> V`) by iterating through the `matchV` array.

### Sample Input/Output

**Input:**

```
Enter number of vertices in set U and V: 3 3
Enter adjacency matrix (3 x 3):
0 1 1
1 0 1
1 1 0
```
*(This represents a bipartite graph with 3 vertices in set U and 3 in set V. For instance, U0 is connected to V1 and V2.)*

**Output:**

```
Maximum Matching = 3
Matched Pairs (U -> V):
U0 -> V1
U1 -> V0
U2 -> V2
```
*(This output shows that all 3 vertices in U can be matched with 3 unique vertices in V, forming a maximum matching of size 3.)*
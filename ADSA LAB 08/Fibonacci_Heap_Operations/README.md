## Fibonacci Heap Operations

### Problem Statement

This program implements a Fibonacci Heap, a sophisticated priority queue data structure, and demonstrates its core operations. Fibonacci Heaps offer highly efficient amortized time complexities, making them particularly useful in certain graph algorithms (like Dijkstra's and Prim's minimum spanning tree) where many `decrease-key` operations are required. The program provides an interactive menu to perform operations such as insertion, finding the minimum element, extracting the minimum, decreasing a key, and deleting a node.

### Related Algorithm: Fibonacci Heap

A Fibonacci Heap is a collection of min-heap-ordered trees. It's a type of priority queue that provides excellent amortized time complexity for most operations, especially `decrease-key` and `merge`. It achieves this efficiency by being "lazy" – it defers some structural maintenance until the `extract-min` operation, where it performs a `consolidate` step.

**Key Concepts and Properties:**

*   **Min-Heap Ordered Trees**: Each tree in the heap is min-heap ordered, meaning the key of a parent node is always less than or equal to the keys of its children.
*   **Root List**: The roots of all trees are linked together in a circular doubly linked list.
*   **Minimum Pointer**: A pointer `H->min` always points to the root of a tree containing the minimum key in the entire heap.
*   **Lazy Operations**: Operations like `insert` and `decrease-key` are performed quickly, potentially leaving the heap structure somewhat messy.
*   **Amortized Analysis**: The complexities are amortized, meaning the average time over a sequence of operations is efficient, even if a single operation (like `extract-min`) might be slow.

**Core Operations:**

1.  **`Insert(key)`**:
    *   Creates a new node with the given `key`.
    *   Adds this new node as a single-node tree to the root list.
    *   Updates `H->min` if the new key is smaller.
    *   Amortized time: O(1).
2.  **`FindMin()`**:
    *   Returns the node pointed to by `H->min`.
    *   Amortized time: O(1).
3.  **`ExtractMin()`**:
    *   Removes the `H->min` node.
    *   Adds all children of the removed `min` node to the root list.
    *   Performs a **`consolidate`** operation to reduce the number of trees in the root list.
    *   Updates `H->min` to point to the new minimum.
    *   Amortized time: O(log n).
4.  **`DecreaseKey(node, newKey)`**:
    *   Decreases the `key` of a given `node` to `newKey`.
    *   If the min-heap property is violated (new key is smaller than its parent's key), the `node` is `cut` from its parent.
    *   A **`cascadingCut`** might be performed on the parent to maintain structural invariants.
    *   Updates `H->min` if `newKey` is the new minimum.
    *   Amortized time: O(1).
5.  **`Delete(node)`**:
    *   First, `decreaseKey` the node's key to negative infinity (or `INT_MIN`).
    *   Then, perform `extractMin` to remove the node.
    *   Amortized time: O(log n).

**Helper Operations (Internal to the Heap):**

*   **`Consolidate()`**: Iterates through the root list, linking trees of the same degree. This process ensures that no two roots in the root list have the same degree. It helps maintain the logarithmic bound on the maximum degree of any node.
*   **`FibLink(child, parent)`**: Makes `child` a child of `parent`. `child` is removed from the root list and added to `parent`'s child list.
*   **`Cut(node, parent)`**: Removes `node` from `parent`'s child list and adds `node` to the root list. Clears `node`'s parent and mark.
*   **`CascadingCut(node)`**: A recursive procedure invoked after `cut`. If a `parent` loses a child and was already marked, it means `parent` has lost two children since it became a child itself. In this case, `parent` is also `cut` from its own parent, and `cascadingCut` is called on `parent`'s parent. This limits the degree of nodes and maintains heap efficiency.

### Code Details

The `q1.c` file provides a C implementation of Fibonacci Heap operations:

*   **`FibNode` struct**: Contains `key`, `degree` (number of children), `mark` (boolean indicating if a node has lost a child since it became a child of its current parent), and pointers to its `parent`, `child`, `left` sibling, and `right` sibling.
*   **`FibHeap` struct**: Contains a pointer `min` to the minimum node in the root list and `n`, the total number of nodes in the heap.
*   **Creation Functions**: `createNode`, `createHeap`.
*   **Helper Functions**: `insertIntoRootList`, `fibLink`.
*   **Core Operations**: `insert`, `extractMin`, `decreaseKey`, `deleteNode`.
*   **Internal Rebalancing Functions**: `consolidate`, `cut`, `cascadingCut`.
*   **`search`**: A recursive function to find a node by its key, used by `decreaseKey` and `deleteNode`.
*   **`displayHeap`**: Prints the structure of the heap's root list and their children, providing an overview of the heap's current state.
*   **`freeHeap`**: A recursive function to deallocate all dynamically allocated memory for the heap nodes.

The `main` function presents an interactive menu to the user, allowing them to perform various Fibonacci Heap operations and observe their effects.

### Sample Input/Output

**Input (interactive menu choices):**

```
===== Fibonacci Heap Menu =====
1. Insert
2. Find Min
3. Extract Min
4. Decrease Key
5. Delete Key
6. Display Heap (full)
7. Exit
Enter choice: 1
Enter key to insert: 10
Enter choice: 1
Enter key to insert: 3
Enter choice: 1
Enter key to insert: 7
Enter choice: 6

Enter choice: 2
Minimum: 3
Enter choice: 3
Extracted Min: 3
Enter choice: 6

Enter choice: 1
Enter key to insert: 1
Enter choice: 4
Enter key to decrease: 10
Key not found. (Assuming user wants to decrease 7 to 1, but mistakenly types 10)
Enter key to decrease: 7
Enter new smaller key: 1
Enter choice: 6

Enter choice: 7
```

**Output (corresponding to the above input):**

```
===== Fibonacci Heap Menu =====
1. Insert
...
Enter choice: 1
Enter key to insert: 10

===== Fibonacci Heap Menu =====
...
Enter choice: 1
Enter key to insert: 3

===== Fibonacci Heap Menu =====
...
Enter choice: 1
Enter key to insert: 7

===== Fibonacci Heap Menu =====
...
Enter choice: 6

Fibonacci Heap (min = 3):
- 3
- 7
- 10

===== Fibonacci Heap Menu =====
...
Enter choice: 2
Minimum: 3

===== Fibonacci Heap Menu =====
...
Enter choice: 3
Extracted Min: 3

===== Fibonacci Heap Menu =====
...
Enter choice: 6

Fibonacci Heap (min = 7):
- 10
- 7

===== Fibonacci Heap Menu =====
...
Enter choice: 1
Enter key to insert: 1

===== Fibonacci Heap Menu =====
...
Enter choice: 4
Enter key to decrease: 10
Key not found.
Enter choice: 4
Enter key to decrease: 7
Enter new smaller key: 1

===== Fibonacci Heap Menu =====
...
Enter choice: 6

Fibonacci Heap (min = 1):
- 1
- 10

===== Fibonacci Heap Menu =====
...
Enter choice: 7
Exiting...
```
*(The output demonstrates how keys are inserted, the minimum is found and extracted, and how decrease-key (with a subsequent rebalance due to `cut` and `cascadingCut`) affects the heap's structure and minimum value. The `displayHeap` provides a snapshot of the root list and child trees.)*
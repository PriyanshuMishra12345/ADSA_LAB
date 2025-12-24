## Splay Tree Operations

### Problem Statement

This program implements a Splay Tree, a self-adjusting binary search tree, and demonstrates its core operations: insertion, search, and deletion. Splay trees are known for their amortized O(log n) performance for these operations, making them efficient for sequences of operations. Their unique self-adjusting property automatically moves recently accessed nodes to the root of the tree, optimizing for scenarios with locality of reference (frequent access to the same items).

### Related Algorithm: Splay Tree

A Splay Tree is a self-balancing binary search tree that automatically reorganizes itself by performing a series of tree rotations to move the most recently accessed node to the root of the tree. Unlike other balanced trees (like AVL or Red-Black trees) that maintain strict balance rules, Splay Trees achieve amortized efficiency without storing any explicit balance information in the nodes.

**The Splay Operation:**

The heart of the Splay Tree is the `splay(root, key)` operation. When a node containing `key` is accessed (searched, inserted, or deleted), `splay` performs rotations to bring that node to the root of the tree. If the `key` is not found, the last accessed node (the parent of where the `key` would have been) is moved to the root.

There are three primary cases for rotations within the `splay` operation, depending on the node `x` (the accessed node), its parent `p`, and its grandparent `g`:

1.  **Zig Rotation**: Occurs when `x` is a child of the `root`. A single rotation (either `leftRotate` or `rightRotate`) moves `x` to the root.
2.  **Zig-Zig Rotation**: Occurs when `x` and `p` are both left children (LL) or both right children (RR). Two rotations are performed in the same direction: first on `p`, then on `g`. This brings `x` closer to the root.
3.  **Zig-Zag Rotation**: Occurs when `x` is a right child of `p`, and `p` is a left child of `g` (LR), or vice versa (RL). Two rotations are performed in opposite directions: first on `x` with respect to `p`, then on `x` with respect to `g`. This also brings `x` closer to the root.

These rotations are repeatedly applied until the accessed node `key` becomes the root of the entire tree.

**Amortized Analysis**: All Splay Tree operations (insertion, search, deletion) have an amortized time complexity of O(log n), meaning that while a single operation might take O(n) in the worst case (e.g., if the tree becomes highly skewed), a sequence of `m` operations will take O(m log n) time in total. This amortized efficiency arises from the fact that frequent accesses to certain nodes make them cheaper to access in the future, exploiting locality of reference.

### Code Details

The `q2.c` file implements a Splay Tree with the following functions:

*   **`Node` struct**: Defines the structure of a Splay Tree node, containing an integer `key` and pointers to its `left` and `right` children.
*   **`createNode(int key)`**: A utility function to create a new Splay Tree node.
*   **`rightRotate(Node *x)`**: Performs a right rotation on the subtree rooted at `x`.
*   **`leftRotate(Node *x)`**: Performs a left rotation on the subtree rooted at `x`.
*   **`splay(Node *root, int key)`**: The core Splay operation. It takes the `root` of the tree and the `key` to be splayed. It recursively searches for the `key` and performs `zig`, `zig-zig`, or `zig-zag` rotations to bring the `key` (or the last accessed node if `key` not found) to the root.
*   **`insert(Node *root, int key)`**: Inserts a new `key` into the Splay Tree. It first `splay`s the tree with the `key`. If `key` is already present, it simply returns the root. Otherwise, it creates a new node, and based on the comparison with the current root, splits the tree and attaches the left/right parts to the new node, making the new node the root.
*   **`search(Node *root, int key)`**: Searches for a `key`. It calls `splay(root, key)`. If the returned root's `key` matches the searched `key`, the key was found and is now at the root.
*   **`deleteNode(Node *root, int key)`**: Deletes a `key` from the Splay Tree. It first `splay`s the tree with the `key`. If `key` is not found, the tree structure (with the splayed node at root) is returned. If found, the node is deleted. The operation then merges the left and right subtrees of the deleted node, typically by splaying the maximum element of the left subtree to become the root of the left subtree, and then attaching the right subtree to this new left root's right child.
*   **`inorder(Node *root)`**: Performs an in-order traversal of the Splay Tree and prints the node keys (which will be in sorted order).
*   **`freeTree(Node *root)`**: Recursively deallocates all memory used by the tree nodes.

The `main` function presents an interactive menu to the user, allowing them to perform Splay Tree operations and observe the self-adjusting behavior, primarily through the in-order traversal which always prints the keys in sorted order.

### Sample Input/Output

**Input (interactive menu choices):**

```
--- Splay Tree Menu ---
1. Insert
2. Search
3. Delete
4. Inorder Traversal
5. Exit
Enter choice: 1
Enter key to insert: 10
Enter choice: 1
Enter key to insert: 20
Enter choice: 1
Enter key to insert: 30
Enter choice: 4
Inorder: 10 20 30
Enter choice: 2
Enter key to search: 20
Key found and splayed to root.
Enter choice: 4
Inorder: 10 20 30
Enter choice: 3
Enter key to delete: 10
Deletion attempted.
Enter choice: 4
Inorder: 20 30
Enter choice: 5
```

**Output (corresponding to the above input):**

```
--- Splay Tree Menu ---
1. Insert
...
Enter choice: 1
Enter key to insert: 10

--- Splay Tree Menu ---
...
Enter choice: 1
Enter key to insert: 20

--- Splay Tree Menu ---
...
Enter choice: 1
Enter key to insert: 30

--- Splay Tree Menu ---
...
Enter choice: 4
Inorder: 10 20 30

--- Splay Tree Menu ---
...
Enter choice: 2
Enter key to search: 20
Key found and splayed to root.

--- Splay Tree Menu ---
...
Enter choice: 4
Inorder: 10 20 30

--- Splay Tree Menu ---
...
Enter choice: 3
Enter key to delete: 10
Deletion attempted.

--- Splay Tree Menu ---
...
Enter choice: 4
Inorder: 20 30

--- Splay Tree Menu ---
...
Enter choice: 5
Exiting...
```
*(The output shows the in-order traversal, which remains sorted, and messages indicating operation results. After a search for `20`, it's splayed to the root, but the inorder traversal still lists elements in sorted order. After deleting `10`, it's removed from the sorted list.)*
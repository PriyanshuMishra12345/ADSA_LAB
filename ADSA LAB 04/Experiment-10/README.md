## Strassen's Matrix Multiplication

### Problem Statement

This program implements Strassen's algorithm for multiplying two square matrices. It aims to compute the product of two `n x n` matrices more efficiently than the traditional matrix multiplication method, especially for larger matrices. The program handles matrices whose dimensions are not necessarily powers of 2 by padding them with zeros to the next power of 2 before applying the recursive algorithm.

### Related Algorithm: Strassen's Matrix Multiplication

Strassen's algorithm is a divide-and-conquer algorithm for matrix multiplication that achieves an asymptotic improvement over the conventional `O(n^3)` algorithm. Developed by Volker Strassen, it reduces the number of recursive multiplications from 8 to 7, resulting in a time complexity of `O(n^log2(7))`, which is approximately `O(n^2.81)`.

The algorithm works as follows for two `n x n` matrices A and B, where `n` is a power of 2:

1.  **Divide**: Both matrices A and B are divided into four `n/2 x n/2` sub-matrices:
    ```
    A = | A11 A12 |   B = | B11 B12 |
        | A21 A22 |       | B21 B22 |
    ```
2.  **Conquer (Recursive Multiplication)**: Instead of performing 8 recursive multiplications, Strassen's algorithm computes 7 products (`M1` to `M7`) of `n/2 x n/2` sub-matrices, requiring more additions/subtractions but fewer multiplications:
    *   `M1 = (A11 + A22) * (B11 + B22)`
    *   `M2 = (A21 + A22) * B11`
    *   `M3 = A11 * (B12 - B22)`
    *   `M4 = A22 * (B21 - B11)`
    *   `M5 = (A11 + A12) * B22`
    *   `M6 = (A21 - A11) * (B11 + B12)`
    *   `M7 = (A12 - A22) * (B21 + B22)`
3.  **Combine**: The four sub-matrices of the resultant matrix C are then calculated using these 7 products:
    *   `C11 = M1 + M4 - M5 + M7`
    *   `C12 = M3 + M5`
    *   `C21 = M2 + M4`
    *   `C22 = M1 - M2 + M3 + M6`

These steps are applied recursively until the sub-matrices are small enough (base case, e.g., 1x1) to be multiplied directly. For matrices whose dimensions are not powers of 2, they are padded with zeros to the next largest power of 2.

### Code Details

The `q6.c` file implements Strassen's matrix multiplication algorithm using static 2D arrays (with `MAX` defined as 16).

*   **`MAX`**: A preprocessor macro defining the maximum allowed size for matrices after padding (16x16 in this implementation). This limits the original `n` to a maximum of 16.
*   **`nextPowerOf2(int n)`**: A helper function to find the smallest power of 2 that is greater than or equal to `n`.
*   **`addMatrix(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX])`**: Performs matrix addition for `n x n` sub-matrices.
*   **`subMatrix(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX])`**: Performs matrix subtraction for `n x n` sub-matrices.
*   **`strassen(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX])`**: The core recursive function implementing Strassen's algorithm.
    *   **Base Case**: If `n == 1`, it performs simple scalar multiplication.
    *   **Recursive Step**: It recursively splits the input matrices into four `k x k` (where `k = n/2`) sub-matrices. It then recursively calls `strassen` to compute the seven intermediate products (M1-M7) using combinations of additions and subtractions of sub-matrices. Finally, it combines these products to form the `C` matrix.
*   **`normalMultiply`**: (Included but not used in `main`) A standard `O(n^3)` matrix multiplication function, potentially for comparison or fallback.

The `main` function:
1.  Prompts the user to enter the original matrix size `n`.
2.  Reads the elements for two `n x n` matrices, `A` and `B`.
3.  Calculates `newSize` as the next power of 2 for `n`.
4.  Creates padded versions (`Apadded`, `Bpadded`, `Cpadded`) of the input matrices, initialized with zeros.
5.  Copies the input matrix elements into the top-left `n x n` block of the padded matrices.
6.  Calls `strassen` with `newSize` and the padded matrices to perform the multiplication.
7.  "Unpads" the result by copying the top-left `n x n` block of `Cpadded` back into `C`.
8.  Prints the resultant `C` matrix of the original `n x n` dimensions.

### Sample Input/Output

**Input:**

```
Enter original matrix size (any n): 2
Enter Matrix A:
1 2
3 4
Enter Matrix B:
5 6
7 8
```

**Output:**

```
Padded size used = 2 x 2

Result Matrix:
19 22
43 50
```
*(This output corresponds to the matrix product:
[ (1*5 + 2*7)  (1*6 + 2*8) ]   =   [ (5+14) (6+16) ]   =   [ 19 22 ]
[ (3*5 + 4*7)  (3*6 + 4*8) ]       [ (15+28) (18+32) ]     [ 43 50 ]
)*
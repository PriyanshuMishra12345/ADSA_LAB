## Interior Point Method (Simplified Barrier Method)

### Problem Statement

This program implements a simplified version of the Interior Point Method (IPM), specifically a barrier method, to solve a Linear Programming (LP) problem of the form:

Minimize `c^T x`
Subject to `A x = b`
And `x >= 0` (implicitly handled by the barrier)

The method iteratively finds a solution to a sequence of modified (barrier) problems, ensuring that all intermediate solutions remain strictly within the feasible region (i.e., `x > 0`).

### Related Algorithm: Interior Point Method (Barrier Method)

The Interior Point Method is a powerful class of algorithms for solving Linear Programming (LP) and other convex optimization problems. Unlike the Simplex algorithm, which traverses the vertices of the feasible region, IPMs approach the optimal solution by moving through the *interior* of the feasible region.

**Key Concepts:**

*   **Barrier Function**: Inequality constraints (like `x >= 0`) are handled by adding a "barrier term" to the objective function. This term penalizes solutions that approach the boundary of the feasible region, effectively keeping the iterative solutions strictly positive. A common barrier function is the logarithmic barrier: `-mu * sum(log(x_i))`.
    *   As `x_i` approaches 0, `log(x_i)` tends to negative infinity, making `-mu * log(x_i)` tend to positive infinity, thus preventing `x_i` from becoming zero.
*   **Barrier Parameter (`mu`)**: This positive parameter controls the strength of the barrier.
    *   Initially, `mu` is large, and the barrier term dominates, pushing solutions away from the boundaries.
    *   As `mu` is gradually reduced towards zero, the barrier's influence diminishes, and the modified objective function increasingly approximates the original LP objective.
*   **Central Path**: The set of optimal solutions to the barrier-augmented problem for different values of `mu` forms a continuous curve called the central path. As `mu` approaches zero, the central path leads to an optimal solution of the original LP.
*   **Path-Following**: IPMs generally work by following this central path. In each iteration, the algorithm aims to:
    1.  Find an approximate optimal solution for the current `mu` (this subproblem is unconstrained or has only equality constraints).
    2.  Reduce `mu`.
    3.  Repeat until `mu` is sufficiently small, and the solution to the barrier problem is close enough to the true LP optimum.

The actual solution of the barrier subproblems usually involves Newton's method, which calculates a search direction based on the gradient and Hessian of the objective. The provided code simplifies this by using gradient descent.

### Code Details

The `q2.c` file implements a simplified Interior Point Method using a barrier function and gradient descent:

*   **`MAXN`, `MAXM`**: Preprocessor macros for maximum number of variables (N) and equality constraints (M).
*   **`MU_REDUCTION`**: Factor by which `mu` is reduced in each outer iteration (e.g., 0.5).
*   **`TOL`**: Tolerance for checking convergence (though not fully utilized in this simplified loop structure).
*   **`STEP`**: Step size for gradient descent.
*   **`MAX_ITER`**: Maximum inner iterations for gradient descent per `mu` value.
*   **`matvec(double y[], double A[][MAXN], double x[], int m, int n)`**: Computes matrix-vector product `y = A*x`.
*   **`objective(double x[], double c[], double mu, int n)`**: Calculates the value of the barrier-augmented objective function: `c^T x - mu * sum(log(x_i))`.
*   **`gradient(double grad[], double x[], double c[], double mu, int n)`**: Calculates the gradient of the barrier-augmented objective function.

The `main` function:
1.  Prompts for `n` (number of variables) and `m` (number of equality constraints).
2.  Takes input for the `m x n` matrix `A`, `m`-element vector `b`, and `n`-element cost vector `c`.
3.  Initializes `x` (primal variables) with `1.0` for all elements (an initial interior feasible point).
4.  Initializes the barrier parameter `mu` to `1.0`.
5.  **Outer Loop (`iter < 20`)**: This loop controls the reduction of `mu`.
    *   **Inner Loop (`k < MAX_ITER`)**: This loop performs gradient descent to find an approximate solution for the current `mu`.
        *   Calculates the `gradient`.
        *   Updates `x` using `x_new = x - STEP * grad`.
        *   Enforces `x[i] >= 1e-8` to prevent `log(0)` issues and maintain strict positivity.
        *   **Simplified Projection**: Includes a heuristic projection step (`for (int i = 0; i < m; i++) { ... x[j] -= 0.01 * diff * A[i][j]; }`) to attempt to satisfy the equality constraints `Ax = b`. This is a basic adjustment rather than a formal projection method.
    *   Prints the current iteration, `mu`, `x` vector, and the objective value.
    *   Reduces `mu` by `MU_REDUCTION`.
6.  Finally, prints the estimated `Optimal x` vector and the `Optimal objective` value based on the last `x` and the original `c`.

### Sample Input/Output

Consider the LP problem (after converting to equality constraints `Ax=b` and `x>=0`):
Minimize `Z = -x1 - x2`
Subject to:
`x1 + 2x2 + x3 = 2`
`2x1 + x2 + x4 = 2`
`x1, x2, x3, x4 >= 0`

Here, `n=4` (x1, x2, x3, x4), `m=2` (two equality constraints).
`c = [-1, -1, 0, 0]`
`A = [[1, 2, 1, 0], [2, 1, 0, 1]]`
`b = [2, 2]`

**Input:**

```
Enter number of variables (n): 4
Enter number of equality constraints (m): 2

Enter matrix A (2 x 4):
1 2 1 0
2 1 0 1

Enter vector b (2 elements):
2
2

Enter cost vector c (4 elements):
-1 -1 0 0
```

**Output (partial, as it runs for many iterations):**

```
Running Interior Point Method...
Iter  0  mu = 1.00000   x = [ 0.2863  0.2863  1.1428  1.1428 ]   f = -0.57266
Iter  1  mu = 0.50000   x = [ 0.6128  0.6128  0.1744  0.1744 ]   f = -1.22569
Iter  2  mu = 0.25000   x = [ 0.6666  0.6666  0.0000  0.0000 ]   f = -1.33336
...
Optimal x ≈ [  0.666667   0.666667   0.000000   0.000000 ]
Optimal objective ≈ -1.333333
```
*(The output shows the iterative convergence of `x` towards the optimal solution as `mu` decreases. The final `x` and objective value approximate the true optimum `x = [2/3, 2/3, 0, 0]` and `Z = -4/3`.)*
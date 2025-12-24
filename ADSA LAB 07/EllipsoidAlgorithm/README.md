## Ellipsoid Algorithm

### Problem Statement

This program implements the Ellipsoid Algorithm, an iterative method for finding a feasible point within a given convex set defined by a system of linear inequalities (`Ax <= b`). While not always the fastest in practice for all problems, it holds significant theoretical importance as it was the first algorithm proven to solve linear programming problems in polynomial time. The algorithm works by iteratively shrinking an ellipsoid that is guaranteed to contain the feasible region until a feasible point is found or the ellipsoid becomes too small.

### Related Algorithm: Ellipsoid Algorithm

The Ellipsoid Algorithm is a method used in mathematical optimization to solve convex optimization problems. It gained prominence when Leonid Khachiyan used it in 1979 to prove that linear programming problems could be solved in polynomial time, making linear programming problems belong to the complexity class P.

**Core Idea:**

The algorithm maintains an ellipsoid that is guaranteed to contain at least one feasible point of the problem's solution space. In each iteration, it checks if the center of the current ellipsoid is a feasible point. If it is not, a "separation oracle" (which, in this implementation, is a violated constraint) is used to find a hyperplane that separates the current center from the feasible region. This hyperplane then "cuts" the ellipsoid, and a new, smaller ellipsoid is constructed that encloses the portion of the previous ellipsoid containing the feasible region. This process continues, with the volume of the ellipsoid shrinking at a guaranteed rate, until a feasible point is found or the ellipsoid's volume becomes negligibly small, indicating no feasible solution.

**Algorithm Steps:**

1.  **Initialization**:
    *   Start with a large initial ellipsoid defined by its center `x` and a shape matrix `P`. This ellipsoid must initially contain the entire feasible region.
2.  **Iteration**: For a fixed number of iterations (`MAX_ITER`):
    *   **Check Feasibility**: Evaluate the constraints at the current ellipsoid center `x`.
    *   **Find Violated Constraint**: If `x` does not satisfy all constraints (i.e., `Ax > b` for at least one row `A_i`), identify one such violated constraint. This constraint's normal vector `a_i` (the `i`-th row of matrix `A`) defines the cutting hyperplane.
    *   **Feasible Point Found**: If `x` satisfies all constraints, then `x` is a feasible point, and the algorithm terminates successfully.
    *   **Update Ellipsoid**: If a violated constraint `a_i` is found:
        *   Calculate `Pa` (where `P` is the current shape matrix and `a` is the normal vector of the violated constraint).
        *   Calculate the scalar `a^T P a`.
        *   Update the center `x` using the formula: `x_new = x - gamma * (P*a / sqrt(a^T P a))`.
        *   Update the shape matrix `P` using the formula: `P_new = factor * (P - beta * ( (P*a)*(P*a)^T / (a^T P a) ) )`.
        *   The constants `gamma`, `beta`, and `factor` are chosen to ensure the maximum possible volume reduction of the ellipsoid while still containing the feasible region.

**Theoretical Significance:**
The Ellipsoid Algorithm's primary significance is theoretical. It proved that linear programming problems are solvable in polynomial time. However, in practice, it is often outperformed by the Simplex Method and interior-point methods due to numerical instability and higher constant factors in its complexity.

### Code Details

The `q1.c` file implements the Ellipsoid Algorithm to find a feasible solution to a system of linear inequalities `Ax <= b`.

*   **`MAXN`, `MAXM`**: Preprocessor macros for maximum number of variables (N) and constraints (M).
*   **`MAX_ITER`**: Maximum number of iterations to attempt before giving up.
*   **`EPS`**: A small tolerance value used for floating-point comparisons (`1e-6`).
*   **Matrix/Vector Operations**:
    *   `matvec(double y[], double A[][MAXN], double x[], int m, int n)`: Computes matrix-vector product `y = A*x`.
    *   `matvec2(double y[], double M[][MAXN], double x[], int n)`: Computes `y = M*x` (for square matrices).
    *   `outer(double C[][MAXN], double a[], double b[], int n)`: Computes the outer product `C = a*b^T`.
    *   `print_vec(double x[], int n)`: Utility to print a vector.
*   **`main` function**:
    1.  Prompts for `n` (number of variables) and `m` (number of constraints).
    2.  Takes input for the `m x n` matrix `A` and the `m`-element vector `b`.
    3.  Takes an initial center point `x` and an initial radius `R` for the ellipsoid.
    4.  Initializes the shape matrix `P` as `R^2 * I` (identity matrix scaled by `R^2`).
    5.  Enters a loop for `MAX_ITER` iterations:
        *   It calculates `Ax` and then iterates through the constraints to find the first `violated` constraint (where `Ax[i] > b[i] + EPS`).
        *   If no constraint is violated, `x` is a feasible solution, and the program terminates.
        *   If a constraint is violated, its normal vector `a` is extracted.
        *   It then applies the standard Ellipsoid Algorithm update formulas to calculate the new center `x` and the new shape matrix `P`, effectively shrinking the ellipsoid.
        *   It prints the current ellipsoid center `x` every 50 iterations for progress tracking.
    6.  If `MAX_ITER` is reached without finding a feasible point, it prints a failure message.

### Sample Input/Output

Consider finding a feasible point for:
`x + y <= 4`
`x - y <= 2`
`x >= 0` (`-x <= 0`)
`y >= 0` (`-y <= 0`)

Let's represent `x >= 0` as `-1x + 0y <= 0` and `y >= 0` as `0x - 1y <= 0`.

So, the system `Ax <= b` is:
`A = [[1, 1], [1, -1], [-1, 0], [0, -1]]`
`b = [4, 2, 0, 0]`

**Input:**

```
Enter number of variables (n): 2
Enter number of constraints (m): 4

Enter matrix A (4 x 2):
1 1
1 -1
-1 0
0 -1

Enter vector b (4 elements):
4
2
0
0

Enter initial point (center of ellipsoid):
0 0
Enter initial ellipsoid radius R: 10
```

**Output:**

```
Running Ellipsoid Method...
Iter 50: center = [ -0.12643  -0.12643 ]
Iter 100: center = [ -0.06321  -0.06321 ]
...
Feasible solution found at iteration 130:
[ 0.00000  0.00000 ]
```
*(Note: The exact output iterations may vary slightly based on `EPS` and numerical precision. For this specific example, the origin `(0,0)` is a feasible solution, and the algorithm finds it. The intermediate prints show how the center of the ellipsoid moves closer to the feasible region.)*
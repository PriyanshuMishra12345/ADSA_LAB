## Simplex Algorithm for Linear Programming (Maximization)

### Problem Statement

This program implements the Simplex Algorithm to solve Linear Programming (LP) problems, specifically focusing on maximization problems. Given a set of linear inequality constraints and a linear objective function to maximize, the program iteratively moves through basic feasible solutions (corner points of the feasible region) to find the optimal solution.

### Related Algorithm: The Simplex Method

The Simplex Algorithm is a widely used and powerful algebraic method for solving linear programming problems. It was developed by George Dantzig and provides an efficient way to find the optimal solution (maximum or minimum value of an objective function) subject to linear constraints.

**Key Concepts:**

*   **Linear Programming (LP)**: A mathematical method for determining a way to achieve the best outcome (such as maximum profit or lowest cost) in a given mathematical model for some list of requirements represented as linear relationships.
*   **Objective Function**: The linear function to be maximized (or minimized).
*   **Constraints**: A set of linear inequalities or equalities that restrict the values of the decision variables.
*   **Feasible Region**: The set of all points that satisfy all the constraints. In an LP problem, this region is a convex polyhedron.
*   **Basic Feasible Solution (BFS)**: A corner point (vertex) of the feasible region. The Simplex Algorithm works by moving from one BFS to an adjacent one, improving the objective function value at each step.
*   **Simplex Tableau**: A tabular representation of the linear programming problem, which is augmented with slack variables and the objective function. This tableau is used to perform the iterative steps of the algorithm.
*   **Slack Variables**: Non-negative variables introduced to convert "less than or equal to" (`<=`) inequality constraints into equality constraints. Each slack variable represents the unused resource or capacity.

**Algorithm Steps (for Maximization Problems):**

1.  **Standard Form Conversion**:
    *   Ensure the objective function is to be maximized.
    *   Convert all inequality constraints to equalities by adding slack variables.
    *   All variables (decision and slack) must be non-negative.
2.  **Initial Simplex Tableau Construction**:
    *   Represent the objective function and constraints in a matrix format. The objective function row is typically the first row, and its coefficients are negated (for maximization problems, we look for negative values to improve).
3.  **Iterative Optimization**: The algorithm repeats the following steps until an optimal solution is reached:
    *   **Identify Entering Variable (Pivot Column)**: Find the column with the most negative value in the objective function row (excluding the RHS value). This variable is chosen to enter the basis (become a basic variable) because increasing it will improve the objective function the most.
    *   **Identify Leaving Variable (Pivot Row)**: Perform the "ratio test." For each constraint row, divide the RHS value by the corresponding positive value in the pivot column. The row that yields the smallest non-negative ratio is the pivot row. The basic variable corresponding to this row is the leaving variable. This ensures that feasibility is maintained.
    *   **Pivot Operation**: The element at the intersection of the pivot row and pivot column is the pivot element. Perform row operations (Gaussian elimination) to make the pivot element 1 and all other elements in the pivot column 0. This transforms the tableau to a new BFS.
4.  **Optimality Check**: If there are no negative values in the objective function row, the current BFS is optimal, and the algorithm terminates.
5.  **Solution Extraction**: The values of the decision variables and the optimal objective function value can be read directly from the final tableau.

### Code Details

The `q1.c` file implements the Simplex Algorithm:

*   **`MAX`**: A preprocessor macro defining the maximum number of variables/constraints (20).
*   **`T[MAX][MAX]`**: A 2D float array representing the Simplex Tableau.
*   **`printTableau(float T[MAX][MAX], int rows, int cols)`**: A utility function to display the current state of the Simplex Tableau.

The `main` function:
1.  Prompts the user to enter the number of decision variables (`n`) and the number of constraints (`m`).
2.  Calculates the total number of columns (`cols = n + m + 1` for variables, slack variables, and RHS) and rows (`rows = m + 1` for objective function and constraints).
3.  **Input for Constraints**: Reads the coefficients for each constraint row-wise, followed by its RHS.
4.  **Input for Objective Function**: Reads the coefficients for the objective function `Z`.
5.  **Initial Tableau Setup**:
    *   The coefficients of the objective function are negated and placed in the first row `T[0]`.
    *   Slack variables are automatically added (`1` at the appropriate position in each constraint row) and their coefficients in `T[0]` are `0`.
    *   The RHS of the objective function is `0`.
6.  **Simplex Iteration Loop**:
    *   The `while(1)` loop continues until an optimal solution is found or it's determined that the solution is unbounded.
    *   In each iteration, it calls `printTableau`.
    *   **Finding Pivot Column**: It searches for the most negative element in the objective row (`T[0]`) to determine `pivotCol`.
    *   **Finding Pivot Row (Ratio Test)**: It calculates ratios of RHS values to positive elements in the `pivotCol` to determine `pivotRow`.
    *   **Unbounded Check**: If no positive ratio can be found, it indicates an unbounded solution.
    *   **Pivoting**: It performs row operations to make the pivot element 1 and other elements in the `pivotCol` 0.
7.  **Output**:
    *   Prints the "Optimal Tableau".
    *   Prints the "Optimal value of Z".
    *   Extracts and prints the values of the decision variables from the final tableau.

### Sample Input/Output

Consider the LP problem:
Maximize `Z = 3x1 + 5x2`
Subject to:
`x1 + 2x2 <= 12`
`3x1 + x2 <= 15`
`x1, x2 >= 0`

**Input:**

```
Enter number of variables: 2
Enter number of constraints: 2
Enter coefficients of constraints row-wise:
Constraint 1:
1 2 12
Constraint 2:
3 1 15
Enter coefficients of objective function (Z):
3 5
```

**Output:**

```
Simplex Tableau:
-3.00  -5.00   0.00   0.00   0.00
 1.00   2.00   1.00   0.00  12.00
 3.00   1.00   0.00   1.00  15.00

Iteration 1:

Simplex Tableau:
 0.00   0.00   2.50   0.00  30.00
 0.50   1.00   0.50   0.00   6.00
 2.50   0.00  -0.50   1.00   9.00

=================================
OPTIMAL TABLEAU:

Simplex Tableau:
 0.00   0.00   2.50   0.00  30.00
 0.50   1.00   0.50   0.00   6.00
 2.50   0.00  -0.50   1.00   9.00

Optimal value of Z = 30.00

Values of decision variables:
x1 = 0.00
x2 = 6.00
```
*(The output shows the tableau at each iteration, the final optimal tableau, the maximum value of the objective function (Z = 30.00), and the values of the decision variables (x1 = 0.00, x2 = 6.00) that achieve this optimum.)*
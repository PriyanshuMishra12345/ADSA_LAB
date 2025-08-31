#include <stdio.h>

// Function to simulate weighing two groups of coins
// Returns: 0 if equal, -1 if left lighter, +1 if right lighter
int weigh(int coins[], int leftStart, int rightStart, int size) {
    int leftSum = 0, rightSum = 0;
    for (int i = 0; i < size; i++) {
        leftSum += coins[leftStart + i];
        rightSum += coins[rightStart + i];
    }
    if (leftSum == rightSum) return 0;
    else if (leftSum < rightSum) return -1;
    else return 1;
}

// Recursive divide-and-conquer function
int findDefective(int coins[], int start, int end) {
    int n = end - start + 1;

    // Base cases
    if (n == 1) return start;   // only one coin, possibly defective

    if (n == 2) {
        if (coins[start] == coins[start + 1])
            return -1; // no defective coin
        else if (coins[start] < coins[start + 1])
            return start; // left lighter
        else
            return start + 1; // right lighter
    }

    // Divide coins into two halves
    int mid = start + (n / 2) - 1;
    int leftSize = n / 2;
    int rightSize = n / 2;

    int result = weigh(coins, start, mid + 1, leftSize);

    if (result == 0) { // equal halves
        if (n % 2 == 1) {
            return findDefective(coins, end, end); // check extra coin
        }
        return -1; // no defective coin
    } else if (result == -1) {
        return findDefective(coins, start, mid); // defective in left
    } else {
        return findDefective(coins, mid + 1, end); // defective in right
    }
}

// main Driver code
int main() {
    int n;
    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coins[n];
    printf("Enter weights of coins:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    int index = findDefective(coins, 0, n - 1);

    if (index == -1)
        printf("All coins are of equal weight. No defective coin.\n");
    else
        printf("Defective coin found at no. %d (0-based), weight = %d\n",
               index+1, coins[index]);

    return 0;
}

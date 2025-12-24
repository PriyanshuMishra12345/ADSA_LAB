#include <stdio.h>
#include <stdlib.h>

/* Function declarations */
int compareWeight(int coins[], int s1, int e1, int s2, int e2);
int findDefective(int coins[], int start, int end);

int main() {
    int n;

    printf("Enter the size of array(No of Coins)\n");
    scanf("%d", &n);

    int coins[n];
    printf("Enter the array elements(Weights of coins)\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    int pos = findDefective(coins, 0, n - 1);

    if (pos == -1) {
        printf("No Defective Coin found\n");
    } else {
        printf("Index of Defective Coin = %d and Weigh is %d", pos, coins[pos]);
    }

    return 0;
}

/* Recursive function to find defective coin */
int findDefective(int coins[], int start, int end) {

    if (start == end) {
        return start;
    }

    if (end - start == 1) {
        if (coins[start] < coins[end]) return start;
        if (coins[end] < coins[start]) return end;
        return -1;
    }

    int count = end - start + 1;
    int mid = (start + end) / 2;

    if (count % 2 == 0) {
        int res = compareWeight(coins, start, mid, mid + 1, end);

        if (res == -1)
            return findDefective(coins, start, mid);
        else if (res == 1)
            return findDefective(coins, mid + 1, end);
        else
            return -1;
    } 
    else {
        int res = compareWeight(coins, start, mid - 1, mid, end - 1);

        if (res == -1)
            return findDefective(coins, start, mid - 1);
        else if (res == 1)
            return findDefective(coins, mid, end - 1);
        else {
            if (coins[end] < coins[start])
                return end;
            else
                return -1;
        }
    }
}

/* Compares total weight of two groups */
int compareWeight(int coins[], int s1, int e1, int s2, int e2) {
    int sumA = 0, sumB = 0;

    for (int i = s1; i <= e1; i++)
        sumA += coins[i];

    for (int j = s2; j <= e2; j++)
        sumB += coins[j];

    if (sumA < sumB) return -1;
    if (sumA > sumB) return 1;
    return 0;
}

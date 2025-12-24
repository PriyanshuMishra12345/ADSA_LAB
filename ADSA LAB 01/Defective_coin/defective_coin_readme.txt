Find Defective Coin Program takes input as the size of the array (number of coins to be checked) and then accepts the weights of the coins as input.
The program applies a Divide and Conquer strategy, where the array is split into two parts and the group with the smaller total weight is further divided and compared recursively.
This approach reduces the number of weighings to log(n) times.
There are a few additional “constant” checks performed outside the recursive division:
If the number of coins is odd, one extra weighing may be required to verify the remaining coin.
If all coins have equal weight, an extra check may be needed to confirm that no defective coin exists.
Hence, the overall time complexity is log(n) (base 2) plus a constant factor (C).
How to Use:
Provide the number of coins when asked.
Enter the weight of each coin.
The program outputs the index (0-based) of the defective lighter coin if detected.
If all coins have the same weight, it indicates that no defective coin is present.


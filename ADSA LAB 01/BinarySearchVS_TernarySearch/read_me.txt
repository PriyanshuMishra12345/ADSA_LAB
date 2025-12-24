Binary Vs Ternary Program accepts input.txt as input
BinaryVsTernary_textinput.exe < input.txt
After execution, BinaryVsTernary_textinput.exe generates the file output.dat
The file output.dat stores the values of n (number of elements in the array), comparison2 (number of comparisons made using Binary Search), and comparison3 (number of comparisons made using Ternary Search)
plot.gp contains the plotting instructions
set title "Binary vs Ternary Search Comparisons"
set xlabel "Array Size (n)"
set ylabel "No. of Comparisons"
set grid
set key left top
plot "output.dat" using 1:2 with linespoints title "Binary Search", \
     "output.dat" using 1:3 with linespoints title "Ternary Search"
Open the terminal and run the command gnuplot -p plot.gp to generate the graph showing the relationship between n and the number of comparisons for Binary and Ternary Search

Algorithm Design:
Binary Search:
The array is repeatedly divided into two equal halves
The middle element is compared with the search key
One half of the array is discarded in each iteration
Executes in O(log? n) time
Requires one comparison per step
Ternary Search:
The array is divided into three nearly equal segments
The search key is compared with two midpoints (mid1 and mid2)
Based on the comparison, one of the three segments is selected
Executes in O(log? n) time
Requires two comparisons per step

Conclusion:
Binary Search performs better than Ternary Search
Although ternary search reduces the search space faster, the additional comparisons at every step make it less efficient
The comparison values and the plotted graph clearly indicate that binary search uses fewer comparisons than ternary search for larger input sizes


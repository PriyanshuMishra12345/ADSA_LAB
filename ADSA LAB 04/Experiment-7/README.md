# Huffman Coding: Lossless Data Compression

## Problem Statement

This program implements the Huffman coding algorithm, a popular method for lossless data compression. Given an input text file, this program analyzes the frequency of each character, builds a Huffman tree to generate a set of optimal prefix-free codes, and then uses these codes to encode the original text into a binary representation.

## Related Algorithm: Huffman Coding

Huffman coding is a greedy algorithm that creates a prefix-free binary code for a set of symbols, typically characters in a text file. The key principle is to assign shorter binary codes to more frequently occurring characters and longer codes to less frequent ones. This results in an overall compressed representation of the source data.

**How it works:**

1.  **Calculate Frequencies**: First, the algorithm reads the input text and counts the occurrences of each unique character.
2.  **Build a Priority Queue**: Each character and its frequency are used to create a leaf node. These nodes are then added to a min-priority queue, which keeps them sorted by frequency.
3.  **Construct the Huffman Tree**:
    *   The algorithm repeatedly extracts the two nodes with the lowest frequencies from the priority queue.
    *   It then creates a new internal node whose frequency is the sum of the two extracted nodes' frequencies. The two extracted nodes become the left and right children of this new node.
    *   This new internal node is inserted back into the priority queue.
    *   This process continues until only one node remains in the queue, which becomes the root of the Huffman tree.
4.  **Generate Codes**: The unique binary code for each character is determined by traversing the tree from the root to the character's leaf node. A '0' is typically assigned for a left branch and a '1' for a right branch. The sequence of 0s and 1s on this path forms the Huffman code for that character.
5.  **Encode Data**: The original text is then re-written by replacing each character with its corresponding Huffman code.

### Code Details

The `q3.c` file provides a complete implementation of the Huffman coding algorithm. It uses a min-heap (implemented as an array-based priority queue) to build the Huffman tree efficiently.

*   **Data Structures**:
    *   `MinHeapNode`: A structure representing a node in the Huffman tree, containing the character (`data`), its frequency (`freq`), and pointers to its `left` and `right` children.
    *   `MinHeap`: A structure to manage the collection of nodes as a min-priority queue.
*   **Core Functions**:
    *   **`calcFrequency`**: Reads an input file (`input.txt`) and populates an array with the frequency of each character.
    *   **`buildHuffmanTree`**:
        1.  Initializes a min-heap with a leaf node for each character present in the input text.
        2.  Repeatedly extracts the two nodes with the lowest frequencies.
        3.  Merges them under a new internal parent node.
        4.  Inserts this new internal node back into the min-heap.
        5.  The process terminates when only one node (the root of the completed Huffman tree) remains.
    *   **`storeCodes`**: Traverses the completed Huffman tree recursively to generate the binary code for each character and stores them in a `codes` array.
    *   **`HuffmanCodes`**: The main driver function that orchestrates the entire process:
        1.  Calls `calcFrequency` to get character counts.
        2.  Calls `buildHuffmanTree` to construct the tree.
        3.  Calls `storeCodes` to generate the code table.
        4.  Prints the character-to-code mapping.
        5.  Reads the input file again and writes the corresponding encoded bitstream into `encoded.txt`.

The `main` function prompts the user for the input filename and initiates the encoding process.

### Sample Input/Output

**Input:**

An input file named `input.txt` with the following content:

```
BCAADDDCCACACAC
```

**Execution:**

```
$ gcc q3.c -o q3
$ ./q3
Enter input file name: input.txt
```

**Output:**

```
Huffman Codes:
A : 1
B : 000
C : 01
D : 001

Encoded file saved as encoded.txt
```

The content of `encoded.txt` would be:
`00001100100100101101101`

*(This output shows the generated Huffman codes for each character and confirms that the encoded data has been saved to `encoded.txt`.)*

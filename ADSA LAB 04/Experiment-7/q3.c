#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 256
#define MAX_CHAR 256

// Huffman Tree Node
struct MinHeapNode {
    unsigned char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

// Min Heap
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

// Create Node
struct MinHeapNode* newNode(unsigned char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->data = data;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}

// Create Min Heap
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Swap
void swapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapify
void minHeapify(struct MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1, right = 2 * idx + 2;

    if (left < heap->size && heap->array[left]->freq < heap->array[smallest]->freq)
        smallest = left;

    if (right < heap->size && heap->array[right]->freq < heap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNode(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

// Remove minimum
struct MinHeapNode* extractMin(struct MinHeap* heap) {
    struct MinHeapNode* temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return temp;
}

// Insert node
void insertMinHeap(struct MinHeap* heap, struct MinHeapNode* node) {
    int i = heap->size++;
    while (i && node->freq < heap->array[(i - 1) / 2]->freq) {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->array[i] = node;
}

// Build heap
void buildMinHeap(struct MinHeap* heap) {
    int n = heap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; i--)
        minHeapify(heap, i);
}

// Build Heap with data
struct MinHeap* createAndBuildHeap(unsigned char data[], int freq[], int size) {
    struct MinHeap* heap = createMinHeap(size);
    for (int i = 0; i < size; i++)
        heap->array[i] = newNode(data[i], freq[i]);
    heap->size = size;
    buildMinHeap(heap);
    return heap;
}

// Build Huffman Tree
struct MinHeapNode* buildHuffmanTree(unsigned char data[], int freq[], int size) {
    struct MinHeap* heap = createAndBuildHeap(data, freq, size);

    while (heap->size > 1) {
        struct MinHeapNode *left = extractMin(heap);
        struct MinHeapNode *right = extractMin(heap);
        struct MinHeapNode *top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(heap, top);
    }
    return extractMin(heap);
}

// Store Huffman Codes
void storeCodes(struct MinHeapNode* root, int arr[], int top, char codes[MAX_CHAR][MAX_TREE_HT]) {

    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1, codes);
    }

    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, codes);
    }

    if (!root->left && !root->right) {
        for (int i = 0; i < top; i++)
            codes[root->data][i] = arr[i] + '0';
        codes[root->data][top] = '\0';
    }
}

// Free memory
void freeTree(struct MinHeapNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Calculate Frequencies
void calcFrequency(char* filename, int freq[]) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("ERROR: File not found.\n");
        exit(1);
    }

    int c;
    while ((c = fgetc(fp)) != EOF)
        freq[c]++;

    fclose(fp);
}

// Huffman Encoding
void HuffmanCodes(char* filename) {

    int freq[MAX_CHAR] = {0};
    calcFrequency(filename, freq);

    unsigned char data[MAX_CHAR];
    int freqArr[MAX_CHAR];
    int size = 0;

    for (int i = 0; i < MAX_CHAR; i++) {
        if (freq[i]) {
            data[size] = i;
            freqArr[size] = freq[i];
            size++;
        }
    }

    // Single character file case
    if (size == 1) {
        printf("\nHuffman Codes:\n%c : 0\n", data[0]);
        FILE* fp = fopen(filename, "r");
        FILE* out = fopen("encoded.txt", "w");

        int ch;
        while ((ch = fgetc(fp)) != EOF)
            fprintf(out, "0");

        fclose(fp);
        fclose(out);
        printf("\nEncoded file saved as encoded.txt\n");
        return;
    }

    struct MinHeapNode* root = buildHuffmanTree(data, freqArr, size);

    int arr[MAX_TREE_HT];
    char codes[MAX_CHAR][MAX_TREE_HT] = {{0}};
    storeCodes(root, arr, 0, codes);

    printf("\nHuffman Codes:\n");
    for (int i = 0; i < size; i++)
        printf("%c : %s\n", data[i], codes[data[i]]);

    FILE* fp = fopen(filename, "r");
    FILE* out = fopen("encoded.txt", "w");

    int ch;
    while ((ch = fgetc(fp)) != EOF)
        fprintf(out, "%s", codes[ch]);

    fclose(fp);
    fclose(out);

    printf("\nEncoded file saved as encoded.txt\n");

    freeTree(root);
}

// Main
int main() {
    char filename[100];
    printf("Enter input file name: ");
    scanf("%s", filename);
    HuffmanCodes(filename);
    return 0;
}


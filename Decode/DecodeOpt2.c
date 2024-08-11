#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// BARR-C: Don't alter any C keywords with #define
#define LOOKUP_SIZE 128

// Lookup Table
static const char* lookup[LOOKUP_SIZE] = {
    [' '] = "100",
    ['"'] = "00111111",
    ['\''] = "11011001",
    [','] = "001110",
    ['.'] = "101000",
    ['A'] = "110110000",
    ['B'] = "001100010",
    ['C'] = "001100011",
    ['D'] = "0011001001",
    ['E'] = "1101100011",
    ['F'] = "0011001010",
    ['G'] = "0011001101",
    ['H'] = "1101001100",
    ['I'] = "110100100",
    ['J'] = "0011000010",
    ['K'] = "00110000000",
    ['L'] = "0011000011",
    ['M'] = "110100111",
    ['N'] = "001100111",
    ['O'] = "0011001000",
    ['P'] = "1101001101",
    ['Q'] = "1101100010011",
    ['R'] = "1101001010",
    ['S'] = "110111100",
    ['T'] = "110111101",
    ['U'] = "00110010110",
    ['V'] = "110110001000",
    ['W'] = "0011001100",
    ['X'] = "11011000100101",
    ['Y'] = "0011000001",
    ['Z'] = "11011000100100",
    ['a'] = "1011",
    ['b'] = "0011110",
    ['c'] = "101001",
    ['d'] = "10101",
    ['e'] = "010",
    ['f'] = "000110",
    ['g'] = "001101",
    ['h'] = "1100",
    ['i'] = "0111",
    ['j'] = "00110010111",
    ['k'] = "00111110",
    ['l'] = "00010",
    ['m'] = "000111",
    ['n'] = "1111",
    ['o'] = "0110",
    ['p'] = "1101110",
    ['q'] = "00110000001",
    ['r'] = "0010",
    ['s'] = "0000",
    ['t'] = "1110",
    ['u'] = "110101",
    ['v'] = "11011111",
    ['w'] = "1101000",
    ['x'] = "1101001011",
    ['y'] = "1101101",
    ['z'] = "11011000101",
};

// Node structure for Huffman Tree
typedef struct Node {
    // Barr-C: use values with implementation-defined widths instead of unsigned char
    uint8_t character;
    struct Node *left;
    struct Node *right;
} Node;

// Barr-C: All private functions should be declared static
// Function to create a new tree node
static Node* createNode(char character) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    // BARR-C: check memory allocation success and handle errors gracefully
    if (!new_node) {
        // BARR-C: Comment an explanation for exit!
        // Memory allocation failure is critical; exit to avoid undefined behavior
        fprintf(stderr, "Memory allocation failed for new node.\n");
        exit(EXIT_FAILURE);
    }
    new_node->character = character;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Barr-C: All private functions should be declared static
// Recursive function to build paths in the Huffman tree
static void buildPath(Node *root, int code, int depth) {
    const char bit = lookup[code][depth];
    // BARR-C: braces surround blocks of code in if, else, while, etc.
    // with braces on their own lines
    if (bit == '\0') {
        // BARR-C: Comment an explanation for casts!
        // code is an unsigned integer, where the value aligns with the ASCII 8-bit value
        // that represents a character
        root->character = (uint8_t)code;
    } else if (bit == '0') {
        if (!root->left) {
            root->left = createNode('*');
        }
        buildPath(root->left, code, depth + 1);
    } else if (bit == '1') {
        if (!root->right) {
            root->right = createNode('*');
        }
        buildPath(root->right, code, depth + 1);
    } else {
        // Invalid Character
        fprintf(stderr, "Error: Invalid character in encoded file (not 0 or 1).\n");
        // BARR-C: Return upon encountering an error
        exit(EXIT_FAILURE);
    }
    // MISRA-C: one exit point for function via return at the bottom
    return;
}

// Barr-C: All private functions should be declared static
// Function to build the entire Huffman tree
static Node* buildHuffmanTree() {
    Node* root = createNode('*');
    // BARR-C: using a for loop for iteration
    for (int i = 0; i < LOOKUP_SIZE; i++) {
        if (lookup[i]) {  // Ensure we only process valid codes
            buildPath(root, i, 0);
        }
    }
    // MISRA-C: one exit point for function via return at the bottom
    return root;
}

// Barr-C: All private functions should be declared static
// Recursive function to free the Huffman tree
static void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Barr-C: All private functions should be declared static
// Function to decode the encoded file using the Huffman tree
static void decode(FILE *input, FILE *output, Node *root) {
    Node *current = root;
    int bit;

    // BARR-C: braces surround blocks of code in if, else, while, etc.
    // with braces on their own lines
    while ((bit = fgetc(input)) != EOF) {
        // BARR-C: constants on left of an if comparison
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        } else {
            // Invalid Character
            fprintf(stderr, "Error: Invalid character in encoded file (not 0 or 1).\n");
            // BARR-C: Return upon encountering an error
            exit(EXIT_FAILURE);
        }

        if (!current->left && !current->right) {  // Reached a leaf node
            fputc(current->character, output);
            current = root;
        } else {
            // MISRA-C: Include else block for all if statements
            // Continue looking for matching leaf node
        }
    }
    // MISRA-C: one exit point for function via return at the bottom
    return;
}

// Main function to handle file operations and initiate decoding
int main(int argc, char *argv[]) {
    // Step 1: Access Encoded File
    if (argc != 2) {
        // BARR-C: Display usage information
        fprintf(stderr, "Usage: %s <encoded file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // BARR-C: Open the encoded file for reading
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        // BARR-C: Use perror to provide detailed error information
        perror("Error opening encoded file");
        return EXIT_FAILURE;
    }

    // Step 2: Build Huffman Tree
    Node* root = buildHuffmanTree();

    // BARR-C: Open the output file for writing decoded data
    FILE *decoded_file = fopen("decoded.txt", "w");
    if (!decoded_file) {
        // BARR-C: Use perror to provide detailed error information
        perror("Error opening decoded output file");
        // BARR-C: Ensure resources are cleaned up before returning
        freeTree(root);
        fclose(file);
        return EXIT_FAILURE;
    }

    // Step 3: Decode the file
    decode(file, decoded_file, root);

    // BARR-C: Close all open files and free memory
    fclose(file);
    fclose(decoded_file);
    freeTree(root);

    // BARR-C: Indicate successful completion
    printf("Decoding completed. Check 'decoded.txt'.\n");

    // MISRA-C: one exit point for function via return at the bottom
    return EXIT_SUCCESS;
}

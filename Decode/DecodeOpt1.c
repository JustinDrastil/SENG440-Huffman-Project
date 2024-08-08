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

typedef struct Node 
{
    // Barr-C: use values with implementation defined widths instead of unsigned char
    uint8_t character;
    struct Node *left;
    struct Node *right;
} Node;


// Barr-C: All private functions should be declared static
// Create a new tree node
static Node* createNode(char character) 
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->character = character;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Barr-C: All private functions should be declared static
// Build path to given Huffman Code
static void buildPath(Node *root, int code, int depth) 
{  
    const char bit = lookup[code][depth];
    // BARR-C: braces surround blocks of code in if, else, while, etc
    // where the braces on their own lines
    // BARR-C: constants on left of an if comparison
    if ('\0' == bit) 
    {
        // BARR-C: Comment an explanation for casts!
        // code is an unsigned integer, where the value aligns with the ASCII 8 bit value
        // that represents a character
        root->character = (uint8_t)code;
    } 
    else if ('0' == bit) 
    {
        if (root->left) {
            buildPath(root->left, code, depth + 1);
        } else {
            root->left = createNode('*');
            buildPath(root->left, code, depth + 1);
        }
    } 
    else if ('1' == bit) 
    {
        if (root->right) 
        {
            buildPath(root->right, code, depth + 1);
        } 
        else 
        {
            root->right = createNode('*');
            buildPath(root->right, code, depth + 1);
        }
    } 
    else 
    {
        // Invalid Character
        printf("Error: Invalid Character in Encoded File (not 0 or 1)\n");
    }
    // MISRA-C: one exit point for function via return at the bottom
    return;
}

// Barr-C: All private functions should be declared static
// Build the Huffman tree
static Node* buildHuffmanTree() 
{
    Node* root = createNode('*');
    int i = 0;
    while(i < LOOKUP_SIZE) 
    {
        buildPath(root, i, 0);
        i++;
    }
    // MISRA-C: one exit point for function via return at the bottom
    return root;
}

// Barr-C: All private functions should be declared static
// Decode the encoded file using a Huffman tree
static void decode(FILE *input, FILE *output, Node *root) 
{
    Node *current = root;
    char bit;

    // BARR-C: braces surround blocks of code in if, else, while, etc
    // where the braces on their own lines
    while ((bit = fgetc(input)) != EOF) 
    {
        // BARR-C: constants on left of an if comparison
        if ('0' == bit) 
        {
            current = current->left;
        } 
        else if ('1' == bit) 
        {
            current = current->right;
        } 
        else 
        {
            // Invalid Character
            printf("Error: Invalid Character in Encoded File (not 0 or 1)\n");
            return;
        }

        if (!current->left && !current->right) 
        {
            fputc(current->character, output);
            current = root;
        } 
        else 
        {
            // MISRA-C: Include else block for all if statements
            // Continue Looking for Matching Leaf Node
        }
    }
    // MISRA-C: one exit point for function via return at the bottom
    return;
}

int main(int argc, char *argv[]) {
    // Step 1: Access Encoded File
    if (2 != argc) 
    {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) 
    {
        perror("Error opening file");
        return 1;
    }

    // Step 2: Build Huffman Tree
    Node* root = buildHuffmanTree();

    // Step 3: Decode the file
    FILE *decoded_file = fopen("decoded.txt", "w");
    decode(file, decoded_file, root);

    fclose(file);
    fclose(decoded_file);

    printf("Decoding completed. Check 'decoded.txt'.\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_SIZE 256
#define LOOKUP_SIZE 123

// Lookup Table for ASCII 0 -> 122 (inclusive)
const char lookup[ASCII_SIZE][16] = {
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "100", //space
    "", //unknown
    "00111111", //"
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "11011001", //'
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "001110", //,
    "", //unknown
    "101000", //.
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "", //unknown
    "110110000", //A
    "001100010", 
    "001100011", 
    "0011001001", 
    "1101100011",
    "0011001010",
    "0011001101",
    "1101001100",
    "110100100",
    "0011000010",
    "00110000000",
    "0011000011",
    "110100111",
    "001100111",
    "0011001000",
    "1101001101",
    "1101100010011",
    "1101001010",
    "110111100",
    "110111101",
    "00110010110",
    "110110001000",
    "0011001100",
    "11011000100101",
    "0011000001",
    "11011000100100",
    "", //unknow
    "", //unknow
    "", //unknow
    "", //unknow
    "", //unknow
    "", //unknow
    "1011", //a
    "0011110",
    "101001",
    "10101",
    "010",
    "000110",
    "001101",
    "1100",
    "0111",
    "00110010111",
    "00111110",
    "00010",
    "000111",
    "1111",
    "0110",
    "1101110",
    "00110000001",
    "0010",
    "0000",
    "1110",
    "110101",
    "11011111",
    "1101000",
    "1101001011",
    "1101101",
    "11011000101"
};

typedef struct Node {
    char character;
    struct Node *left;
    struct Node *right;
} Node;

// Create a new tree node
Node* createNode(char character) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->character = character;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Build path to given Huffman Code
void buildPath(Node *root, int code, int depth) {  
    if (lookup[code][depth] == '\0') {
        root->character = (unsigned char)code;
    } else if (lookup[code][depth] == '0') {
        if (root->left) {
            buildPath(root->left, code, depth + 1);
        } else {
            root->left = createNode('*');
            buildPath(root->left, code, depth + 1);
        }
    } else if (lookup[code][depth] =='1') {
        if (root->right) {
            buildPath(root->right, code, depth + 1);
        } else {
            root->right = createNode('*');
            buildPath(root->right, code, depth + 1);
        }
    } else {
        // Invalid Character
        printf("Error: Invalid Character in Encoded File (not 0 or 1)\n");
    }
    return;
}

// Build the Huffman tree
Node* buildHuffmanTree() {
    Node* root = createNode('*');
    for (int i = 0; i < LOOKUP_SIZE; i++) {
        buildPath(root, i, 0);
    }
    return root;
}

// Decode the encoded file using a Huffman tree
void decode(FILE *input, FILE *output, Node *root) {
    Node *current = root;
    char bit;
    while ((bit = fgetc(input)) != EOF) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        } else {
            // Invalid Character
            printf("Error: Invalid Character in Encoded File (not 0 or 1)\n");
            return;
        }
        if (!current->left && !current->right) {
            fputc(current->character, output);
            current = root;
        } else {
            // Continue Looking for Matching Leaf Node
        }
    }
    return;
}

int main(int argc, char *argv[]) {
    // Step 1: Access Encoded File
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
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

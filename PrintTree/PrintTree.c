#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXPECTED_SYMBOLS 57

// Define the structure for a tree node
typedef struct TreeNode {
    char character;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Create a new tree node
TreeNode* createNode(char character) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->character = character;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert a node into the binary tree based on the given binary code
void insert(TreeNode *root, const char *code, char character) {
    TreeNode *current = root;
    while (*code) {
        if (*code == '0') {
            if (current->left == NULL) {
                current->left = createNode('\0');
            }
            current = current->left;
        } else if (*code == '1') {
            if (current->right == NULL) {
                current->right = createNode('\0');
            }
            current = current->right;
        }
        code++;
    }
    current->character = character;
}

void printTree(TreeNode *node, int depth, char direction, FILE*fptr) {
    if (node != NULL) {
        for (int i = 0; i < depth; i++) {
            fprintf(fptr, "  ");
        }
        if (node->character != '\0') {
            if (node->character != ' ') {
                fprintf(fptr,"%c = ", direction);
                fprintf(fptr,"%c\n", node->character);
            } else {
                fprintf(fptr,"%c = ' '", direction);
            }
            
        } else {
             fprintf(fptr,"%c\n", direction);
        }
        printTree(node->left, depth + 1, '0', fptr);
        printTree(node->right, depth + 1, '1', fptr);
    }
}

int main(int argc, char *argv[]) {
    // Get symbols and huffman codes from given file
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char* codes[EXPECTED_SYMBOLS] = {0};
    char chars[EXPECTED_SYMBOLS] = {0};

    char* ch;

    FILE* fp;
    int bufferLength = 255;
    char buffer[255];
    int count = 0;

    while (fgets(buffer, bufferLength, file) && count < EXPECTED_SYMBOLS) {
        chars[count] = buffer[1];
        *buffer = *buffer + 5;
        strcpy(codes[count], buffer);
        count++;
    }

    fclose(fp);

    // Print codes in tree format to a file
    // Create the root of the tree
    TreeNode *root = createNode('\0');

    // Insert all characters into the tree
    int numCodes = sizeof(codes) / sizeof(codes[0]);
    for (int i = 0; i < numCodes; i++) {
        insert(root, codes[i], chars[i]);
    }

    // Print the binary tree to a file
    FILE *fptr;
    fptr = fopen("tree.txt", "w");

    fprintf(fptr, "Binary Tree:\n");
    printTree(root, 0, ' ', fptr);

    fclose(fptr);
    printf("Printed to tree.txt");

    return 0;
}

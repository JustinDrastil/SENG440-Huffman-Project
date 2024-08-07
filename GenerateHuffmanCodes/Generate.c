#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_SIZE 256

typedef struct Node {
    char character;
    int frequency;
    struct Node *left, *right;
} Node;

typedef struct ListNode {
    Node *treeNode;
    struct ListNode *next;
} ListNode;

// Create a new tree node
Node* createNode(char character, int frequency) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->character = character;
    new_node->frequency = frequency;
    new_node->left = new_node->right = NULL;
    return new_node;
}

// Create a new list node
ListNode* createListNode(Node *treeNode) {
    ListNode *new_list_node = (ListNode*)malloc(sizeof(ListNode));
    new_list_node->treeNode = treeNode;
    new_list_node->next = NULL;
    return new_list_node;
}

// Insert a tree node into the list (priority queue)
ListNode* insert(ListNode *head, Node *treeNode) {
    ListNode *new_list_node = createListNode(treeNode);
    if (!head || treeNode->frequency < head->treeNode->frequency) {
        new_list_node->next = head;
        return new_list_node;
    }

    ListNode *current = head;
    while (current->next && current->next->treeNode->frequency <= treeNode->frequency) {
        current = current->next;
    }
    new_list_node->next = current->next;
    current->next = new_list_node;

    return head;
}

// Extract the minimum frequency node from the list
ListNode* extractMin(ListNode **head) {
    ListNode *temp = *head;
    *head = (*head)->next;
    return temp;
}

// Calculate character frequencies
ListNode* calculateFrequency(FILE *file) {
    int frequencies[ASCII_SIZE] = {0};
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        frequencies[(unsigned char)ch]++;
    }

    ListNode *head = NULL;
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (frequencies[i] > 0) {
            head = insert(head, createNode((char)i, frequencies[i]));
        }
    }

    return head;
}

// Build the Huffman tree
Node* buildHuffmanTree(ListNode *head) {
    while (head && head->next) {
        ListNode *left = extractMin(&head);
        ListNode *right = extractMin(&head);
        Node *merged = createNode('\0', left->treeNode->frequency + right->treeNode->frequency);
        merged->left = left->treeNode;
        merged->right = right->treeNode;
        head = insert(head, merged);
        free(left);
        free(right);
    }
    Node *root = head->treeNode;
    free(head);
    return root;
}

// Generate Huffman codes
void generateCodes(Node *root, char *code, int depth, char codes[ASCII_SIZE][ASCII_SIZE]) {
    if (!root->left && !root->right) {
        code[depth] = '\0';
        strcpy(codes[(unsigned char)root->character], code);
        return;
    }
    if (root->left) {
        code[depth] = '0';
        generateCodes(root->left, code, depth + 1, codes);
    }
    if (root->right) {
        code[depth] = '1';
        generateCodes(root->right, code, depth + 1, codes);
    }
}

// Print Huffman codes (lookup table)
void printCodes(char codes[ASCII_SIZE][ASCII_SIZE]) {
    FILE* output;
    output = fopen("codes.txt", "w");
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (codes[i][0] != '\0') {
            if (i == '\n') {
                fprintf(output,"'\\n': %s\n", codes[i]);
            } else if (i == '\t') {
                fprintf(output,"'\\t': %s\n", codes[i]);
            } else if (i == ' ') {
                fprintf(output,"' ': %s\n", codes[i]);
            } else {
               fprintf(output,"'%c': %s\n", i, codes[i]);
            }
        }
    }
    fclose(output);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // Step 1: Calculate frequencies and build Huffman tree
    ListNode *head = calculateFrequency(file);
    Node *root = buildHuffmanTree(head);

    // Step 2: Generate Huffman codes
    char codes[ASCII_SIZE][ASCII_SIZE] = {0};
    char code[ASCII_SIZE];
    generateCodes(root, code, 0, codes);

    // Step 3: Print Huffman codes
    printCodes(codes);

    // Free the Huffman tree
    Node *current = root;
    while (current) {
        Node *temp = current;
        current = current->left ? current->left : current->right;
        free(temp);
    }

    return 0;
}

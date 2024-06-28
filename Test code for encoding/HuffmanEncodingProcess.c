#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 100

// Define the node structure
typedef struct Node {
    char symbol[3];
    double probability;
    struct Node *left, *right;
} Node;

// Priority queue for building the Huffman tree
typedef struct PriorityQueue {
    Node *nodes[MAX_SYMBOLS];
    int size;
} PriorityQueue;

PriorityQueue pq;

// Function prototypes
Node* create_node(const char *symbol, double probability);
void insert_node(Node *node);
Node* extract_min();
void build_huffman_tree();
void generate_huffman_codes(Node *root, char *code, int depth);
void free_tree(Node *root);

int main() {
    // Define the given probabilities
    const char *symbols[] = {
        "space", "e", "t", "a", "o", "n", "i", "s", "r", "h", "l", "d", "th", "c", "he", ".", ",", "u", "m", "f", "p", "g", "in", "er",
        "an", "y", "w", "re", "b", "nd", "on", "en", "at", "v", "ou", "ed", "ha", "to", "or", "'", "it", "is", "hi", "es", "ng", "k", "\"",
        "T", "S", "A", "M", "C", "I", "N", "B", "R", "P", "E", "D", "H", "x", "W", "L", "O", "F", "Y", "G", "J", "z", "j", "U", "q", "K", "V", "Q", "X", "Z"
    };
    double probabilities[] = {
        14.6367, 7.6227, 5.4230, 5.1828, 4.6565, 4.4658, 4.4577, 4.1218, 4.0743, 2.9104, 2.5139, 2.3334, 1.9341, 1.9303, 1.8339, 1.8071, 1.7678, 1.5885, 1.4448,
        1.2770, 1.2363, 1.1882, 1.1377, 1.0850, 1.0663, 1.0457, 1.0000, 0.8715, 0.8528, 0.7831, 0.7065, 0.6891, 0.6653, 0.6433, 0.6404, 0.6355, 0.6350, 0.5827,
        0.5734, 0.5694, 0.5654, 0.5529, 0.5441, 0.5441, 0.5248, 0.4537, 0.4467, 0.3205, 0.3003, 0.2766, 0.2555, 0.2258, 0.2199, 0.2022, 0.1669, 0.1442, 0.1420,
        0.1363, 0.1276, 0.1217, 0.1217, 0.1055, 0.1053, 0.1041, 0.0992, 0.0928, 0.0918, 0.0775, 0.0654, 0.0648, 0.0566, 0.0534, 0.0459, 0.0306, 0.0115, 0.0075, 0.0055
    };

    int num_symbols = sizeof(probabilities) / sizeof(probabilities[0]);

    // Initialize the priority queue
    pq.size = 0;

    // Insert all symbols into the priority queue
    for (int i = 0; i < num_symbols; i++) {
        insert_node(create_node(symbols[i], probabilities[i]));
    }

    // Build the Huffman tree
    build_huffman_tree();

    // Generate and print Huffman codes
    char code[MAX_SYMBOLS];
    generate_huffman_codes(pq.nodes[0], code, 0);

    // Free the Huffman tree
    free_tree(pq.nodes[0]);

    return 0;
}

// Function to create a new node
Node* create_node(const char *symbol, double probability) {
    Node *node = (Node *)malloc(sizeof(Node));
    strcpy(node->symbol, symbol);
    node->probability = probability;
    node->left = node->right = NULL;
    return node;
}

// Function to insert a node into the priority queue
void insert_node(Node *node) {
    int i = pq.size++;
    while (i > 0 && pq.nodes[(i - 1) / 2]->probability > node->probability) {
        pq.nodes[i] = pq.nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    pq.nodes[i] = node;
}

// Function to extract the node with the minimum probability from the priority queue
Node* extract_min() {
    Node *min_node = pq.nodes[0];
    pq.nodes[0] = pq.nodes[--pq.size];
    int i = 0;
    while (2 * i + 1 < pq.size) {
        int j = 2 * i + 1;
        if (j + 1 < pq.size && pq.nodes[j + 1]->probability < pq.nodes[j]->probability) {
            j++;
        }
        if (pq.nodes[i]->probability <= pq.nodes[j]->probability) {
            break;
        }
        Node *tmp = pq.nodes[i];
        pq.nodes[i] = pq.nodes[j];
        pq.nodes[j] = tmp;
        i = j;
    }
    return min_node;
}

// Function to build the Huffman tree
void build_huffman_tree() {
    while (pq.size > 1) {
        Node *left = extract_min();
        Node *right = extract_min();
        Node *merged = create_node("", left->probability + right->probability);
        merged->left = left;
        merged->right = right;
        insert_node(merged);
    }
}

// Function to generate Huffman codes
void generate_huffman_codes(Node *root, char *code, int depth) {
    if (root->left == NULL && root->right == NULL) {
        code[depth] = '\0';
        printf("Symbol: %s, Code: %s\n", root->symbol, code);
        return;
    }
    if (root->left) {
        code[depth] = '0';
        generate_huffman_codes(root->left, code, depth + 1);
    }
    if (root->right) {
        code[depth] = '1';
        generate_huffman_codes(root->right, code, depth + 1);
    }
}

// Function to free the Huffman tree
void free_tree(Node *root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

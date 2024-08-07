#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 256
#define MAX_CODE_LENGTH 100

typedef struct {
    char symbol;
    float probability;
} Symbol;

typedef struct Node {
    char symbol;
    float probability;
    struct Node *left, *right;
} Node;

typedef struct {
    Node *nodes[MAX_SYMBOLS];
    int size;
} PriorityQueue;

void init_priority_queue(PriorityQueue *pq) {
    pq->size = 0;
}

void insert_priority_queue(PriorityQueue *pq, Node *node) {
    pq->nodes[pq->size++] = node;
    int i = pq->size - 1;
    while (i && pq->nodes[i]->probability < pq->nodes[(i - 1) / 2]->probability) {
        Node *temp = pq->nodes[i];
        pq->nodes[i] = pq->nodes[(i - 1) / 2];
        pq->nodes[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

Node* remove_min_priority_queue(PriorityQueue *pq) {
    Node *minNode = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];
    int i = 0, smallest = 0;
    while (i != smallest) {
        i = smallest;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < pq->size && pq->nodes[left]->probability < pq->nodes[smallest]->probability) {
            smallest = left;
        }
        if (right < pq->size && pq->nodes[right]->probability < pq->nodes[smallest]->probability) {
            smallest = right;
        }
        if (i != smallest) {
            Node *temp = pq->nodes[i];
            pq->nodes[i] = pq->nodes[smallest];
            pq->nodes[smallest] = temp;
        }
    }
    return minNode;
}

Node* create_node(char symbol, float probability) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->symbol = symbol;
    node->probability = probability;
    node->left = node->right = NULL;
    return node;
}

void print_codes(Node *root, char *code, int depth) {
    if (!root) return;
    if (!root->left && !root->right) {
        code[depth] = '\0';
        printf("%c: %s\n", root->symbol, code);
    }
    if (root->left) {
        code[depth] = '0';
        print_codes(root->left, code, depth + 1);
    }
    if (root->right) {
        code[depth] = '1';
        print_codes(root->right, code, depth + 1);
    }
}

void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void build_huffman_tree(Symbol symbols[], int n, Node **root) {
    PriorityQueue pq;
    init_priority_queue(&pq);

    for (int i = 0; i < n; ++i) {
        insert_priority_queue(&pq, create_node(symbols[i].symbol, symbols[i].probability));
    }

    while (pq.size > 1) {
        Node *left = remove_min_priority_queue(&pq);
        Node *right = remove_min_priority_queue(&pq);
        Node *newNode = create_node('\0', left->probability + right->probability);
        newNode->left = left;
        newNode->right = right;
        insert_priority_queue(&pq, newNode);
    }

    *root = remove_min_priority_queue(&pq);
}

void generate_codes(Node *root, char **codes, char *code, int depth) {
    if (!root) return;
    if (!root->left && !root->right) {
        code[depth] = '\0';
        codes[(int)root->symbol] = (char *)malloc((depth + 1) * sizeof(char));
        strcpy(codes[(int)root->symbol], code);
    }
    if (root->left) {
        code[depth] = '0';
        generate_codes(root->left, codes, code, depth + 1);
    }
    if (root->right) {
        code[depth] = '1';
        generate_codes(root->right, codes, code, depth + 1);
    }
}

char* huffman_encode(char *input, char **codes) {
    int length = 0;
    for (int i = 0; input[i] != '\0'; ++i) {
        length += strlen(codes[(int)input[i]]);
    }
    char *encoded = (char *)malloc((length + 1) * sizeof(char));
    encoded[0] = '\0';
    for (int i = 0; input[i] != '\0'; ++i) {
        strcat(encoded, codes[(int)input[i]]);
    }
    return encoded;
}

char* huffman_decode(char *encoded, Node *root) {
    Node *current = root;
    int length = strlen(encoded);
    char *decoded = (char *)malloc((length + 1) * sizeof(char));
    int j = 0;
    for (int i = 0; i < length; ++i) {
        if (encoded[i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (!current->left && !current->right) {
            decoded[j++] = current->symbol;
            current = root;
        }
    }
    decoded[j] = '\0';
    return decoded;
}

void print_tree(Node *root, int depth) {
    if (root == NULL) return;

    // Print right subtree first (for visual alignment)
    print_tree(root->right, depth + 1);

    // Print current node with indentation based on depth
    for (int i = 0; i < depth; i++) printf("    ");
    if (root->symbol) {
        printf("%c: %.4f\n", root->symbol, root->probability);
    } else {
        printf("[%.4f]\n", root->probability);
    }

    // Print left subtree
    print_tree(root->left, depth + 1);
}

int main() {
    Symbol symbols[] = {
        {' ', 14.6367}, {'e', 7.6227}, {'t', 5.4230}, {'a', 5.1828}, {'o', 4.6565},
        {'n', 4.4658}, {'i', 4.4577}, {'s', 4.1218}, {'r', 4.0743}, {'h', 2.9104},
        {'l', 2.5139}, {'d', 2.3334}, {'t', 1.9341}, {'c', 1.9303}, {'h', 1.8339},
        {'.', 1.8071}, {',', 1.7678}, {'u', 1.5885}, {'m', 1.4448}, {'f', 1.2770},
        {'p', 1.2363}, {'g', 1.1882}, {'i', 1.1377}, {'e', 1.0850}, {'a', 1.0663},
        {'y', 1.0457}, {'w', 1.0000}, {'r', 0.8715}, {'b', 0.8528}, {'d', 0.7831},
        {'o', 0.7065}, {'e', 0.6891}, {'a', 0.6653}, {'v', 0.6433}, {'\'', 0.5694},
        {'k', 0.4537}, {'"', 0.4467}, {'T', 0.3205}, {'S', 0.3003}, {'A', 0.2766},
        {'M', 0.2555}, {'C', 0.2258}, {'I', 0.2199}, {'N', 0.2022}, {'B', 0.1669},
        {'R', 0.1442}, {'P', 0.1420}, {'E', 0.1363}, {'D', 0.1276}, {'H', 0.1217},
        {'x', 0.1217}, {'W', 0.1055}, {'L', 0.1053}, {'O', 0.1041}, {'F', 0.0992},
        {'Y', 0.0928}, {'G', 0.0918}, {'J', 0.0775}, {'z', 0.0654}, {'j', 0.0648},
        {'U', 0.0566}, {'q', 0.0534}, {'K', 0.0459}, {'V', 0.0306}, {'Q', 0.0115},
        {'X', 0.0075}, {'Z', 0.0055}
    };

    int n = sizeof(symbols) / sizeof(symbols[0]);

    Node *root;
    build_huffman_tree(symbols, n, &root);

    // Print the tree structure
    printf("Huffman Tree:\n");
    print_tree(root, 0);

    char *codes[MAX_SYMBOLS] = {0};
    char code[MAX_CODE_LENGTH];
    generate_codes(root, codes, code, 0);

    printf("Huffman Codes:\n");
    for (int i = 0; i < MAX_SYMBOLS; ++i) {
        if (codes[i]) {
            printf("%c: %s\n", i, codes[i]);
        }
    }

    char input[] = "hello world";
    char *encoded = huffman_encode(input, codes);
    //printf("\nEncoded: %s\n", encoded);

    char *decoded = huffman_decode(encoded, root);
    //printf("Decoded: %s\n", decoded);

    // Free allocated memory
    free(encoded);
    free(decoded);
    for (int i = 0; i < MAX_SYMBOLS; ++i) {
        if (codes[i]) {
            free(codes[i]);
        }
    }
    free_tree(root);

    return 0;
}

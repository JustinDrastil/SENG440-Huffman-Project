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
    if (pq->size == 0) return NULL;
    Node *minNode = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];
    int i = 0, smallest = 0;
    while (1) {
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
            i = smallest;
        } else {
            break;
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

    printf("Inserting nodes into priority queue:\n");
    for (int i = 0; i < n; ++i) {
        printf("Symbol: %c, Probability: %.4f\n", symbols[i].symbol, symbols[i].probability);
        insert_priority_queue(&pq, create_node(symbols[i].symbol, symbols[i].probability));
    }

    while (pq.size > 1) {
        Node *left = remove_min_priority_queue(&pq);
        Node *right = remove_min_priority_queue(&pq);
        printf("Combining nodes: %c(%.4f) + %c(%.4f)\n",
               left->symbol ? left->symbol : '#', left->probability,
               right->symbol ? right->symbol : '#', right->probability);
        Node *newNode = create_node('\0', left->probability + right->probability);
        newNode->left = left;
        newNode->right = right;
        printf("New node created with probability: %.4f\n", newNode->probability);
        insert_priority_queue(&pq, newNode);
    }

    *root = remove_min_priority_queue(&pq);
}

void generate_codes(Node *root, char **codes, char *code, int depth) {
    if (!root) return;
    if (!root->left && !root->right) {
        code[depth] = '\0';
        codes[(int)root->symbol] = (char *)malloc((depth + 1) * sizeof(char));
        if (codes[(int)root->symbol] == NULL) {
            fprintf(stderr, "Memory allocation failed for code of symbol %c\n", root->symbol);
            exit(1);
        }
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
    if (encoded == NULL) {
        fprintf(stderr, "Memory allocation failed for encoded string\n");
        exit(1);
    }
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
    if (decoded == NULL) {
        fprintf(stderr, "Memory allocation failed for decoded string\n");
        exit(1);
    }
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

int main() {
    Symbol symbols[] = {
        {' ', 14.6367}, {'e', 7.6227}, {'t', 5.4230}, {'a', 5.1828}, {'o', 4.6565}
    };

    int n = sizeof(symbols) / sizeof(symbols[0]);

    Node *root;
    build_huffman_tree(symbols, n, &root);

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
    printf("\nEncoded: %s\n", encoded);

    char *decoded = huffman_decode(encoded, root);
    printf("Decoded: %s\n", decoded);

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

#include <stdio.h>
#include <stdlib.h>

#define ASCII_SIZE 256

void calculateFrequency(FILE *file) {
    int frequencies[ASCII_SIZE] = {0};
    char ch;

    // Read each character and update frequency
    while ((ch = fgetc(file)) != EOF) {
        frequencies[(unsigned char)ch]++;
    }

    // Display frequencies
    printf("Character Frequencies:\n");
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (frequencies[i] > 0) {
            if (i == '\n') {
                printf("'\\n': %d\n", frequencies[i]);
            } else if (i == '\t') {
                printf("'\\t': %d\n", frequencies[i]);
            } else {
                printf("'%c': %d\n", i, frequencies[i]);
            }
        }
    }
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

    calculateFrequency(file);

    fclose(file);
    return 0;
}

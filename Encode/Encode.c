#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Lookup Table for ASCII 0 -> 122 (inclusive)
static const char* lookup[128] = {
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

// Encode the input file using the lookup table
void encode(FILE *input, FILE *output) {
    int ch;
    while ((ch = fgetc(input)) != EOF) {
        if (ch >= 0 && ch < 128 && lookup[ch] != NULL) {
            fputs(lookup[ch], output);
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
        perror("Error opening input file");
        return 1;
    }
    printf("Input file opened successfully.\n");

    FILE *encoded_file = fopen("encoded.txt", "w");
    if (!encoded_file) {
        perror("Error opening encoded file");
        fclose(file);
        return 1;
    }
    printf("Output file created successfully.\n");

    encode(file, encoded_file);

    fclose(encoded_file);
    fclose(file);

    printf("Encoding completed. Check 'encoded.txt'.\n");

    return 0;
}

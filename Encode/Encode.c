#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_SIZE 256

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

// Encode the input file using the lookup table
void encode(FILE *input, FILE *output) {
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        fputs(lookup[(unsigned char)ch], output);
    }
}

int main(int argc, char *argv[]) {
    // Step 1: Access Input File
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }
    printf("Input file opened successfully.\n");

    // Step 2: Encode the input file
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

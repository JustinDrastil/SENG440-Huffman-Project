#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_SYMBOLS 100000

// Define the given probabilities
char *symbols[] = {
    " ", "e", "t", "a", "o", "n", "i", "s", "r", "h", "l", "d", "th", "c", "he", ".", ",", "u", "m", "f", "p", "g", "in", "er",
    "an", "y", "w", "re", "b", "nd", "on", "en", "at", "v", "ou", "ed", "ha", "to", "or", "'", "it", "is", "hi", "es", "ng", "k", "\"",
    "T", "S", "A", "M", "C", "I", "N", "B", "R", "P", "E", "D", "H", "x", "W", "L", "O", "F", "Y", "G", "J", "z", "j", "U", "q", "K", "V", "Q", "X", "Z"
};
double probabilities[] = {
    14.6367, 7.6227, 5.4230, 5.1828, 4.6565, 4.4658, 4.4577, 4.1218, 4.0743, 2.9104, 2.5139, 2.3334, 1.9341, 1.9303, 1.8339, 1.8071, 1.7678, 1.5885, 1.4448,
    1.2770, 1.2363, 1.1882, 1.1377, 1.0850, 1.0663, 1.0457, 1.0000, 0.8715, 0.8528, 0.7831, 0.7065, 0.6891, 0.6653, 0.6433, 0.6404, 0.6355, 0.6350, 0.5827,
    0.5734, 0.5694, 0.5654, 0.5529, 0.5441, 0.5441, 0.5248, 0.4537, 0.4467, 0.3205, 0.3003, 0.2766, 0.2555, 0.2258, 0.2199, 0.2022, 0.1669, 0.1442, 0.1420,
    0.1363, 0.1276, 0.1217, 0.1217, 0.1055, 0.1053, 0.1041, 0.0992, 0.0928, 0.0918, 0.0775, 0.0654, 0.0648, 0.0566, 0.0534, 0.0459, 0.0306, 0.0115, 0.0075, 0.0055
};

// Function prototypes
char* get_random_char();
double drand ( double low, double high );

int main() 
{
    char* tempChar;
    FILE *fptr;
    fptr = fopen("testbench.txt", "w");

    srand(time(NULL));      

    for (int i = 0; i < MAX_SYMBOLS; i++) {
        tempChar = get_random_char();
        fprintf(fptr, tempChar);
    }

    fclose(fptr);   
    return 0;
}

// Function to get char with defined probabilities
char* get_random_char() 
{
    int num_symbols = sizeof(probabilities) / sizeof(probabilities[0]);
    double r = drand(0, 100);
    double cdf = 0.0;
    for (int i = 0; i < num_symbols; i++) {
        cdf += probabilities[i];
        if (r < cdf) {
            return symbols[i];
        }
    }
    return symbols[num_symbols - 1];
}

// Function returns random double between low and high values (based on srand())
double drand ( double low, double high )
{
    return ( (double)rand() * ( high - low ) ) / (double)RAND_MAX + low;
}
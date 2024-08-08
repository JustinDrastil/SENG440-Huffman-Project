#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_SYMBOLS 100000

// Define the given probabilities
char *symbols[] = {
    " ", "e", "t", "a", "o", "n", "i", "s", "r", "h", "l", "d", "c", ".", ",", "u", 
    "m", "f", "p", "g", "y", "w", "b", "v", "'", "k", "\"", "T", "S", "A", "M", "C", 
    "I", "N", "B", "R", "P", "E", "D", "H", "x", "W", "L", "O", "F", "Y", "G", "J", 
    "z", "j", "U", "q", "K", "V", "Q", "X", "Z"
};
double probabilities[] = {
    17.5439, 9.1368, 6.5001, 6.2122, 5.5814, 5.3528, 5.3431, 4.9405, 4.8835, 3.4885, 3.0132, 2.7968, 2.3136, 2.1661, 2.1190, 1.9040, 
    1.7318, 1.5306, 1.4818, 1.4242, 1.2534, 1.1987, 1.0222, 0.7711, 0.6825, 0.5438, 0.5354, 0.3841, 0.3599, 0.3316, 0.3062, 0.2707, 
    0.2635, 0.2424, 0.2000, 0.1728, 0.1702, 0.1634, 0.1530, 0.1459, 0.1458, 0.1265, 0.1263, 0.1247, 0.1189, 0.1113, 0.1100, 0.0929, 
    0.0784, 0.0777, 0.0678, 0.0640, 0.0550, 0.0366, 0.0138, 0.0089, 0.0066
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
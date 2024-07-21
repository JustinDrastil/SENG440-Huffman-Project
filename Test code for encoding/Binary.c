#include <stdio.h>
#include <string.h>
#include <math.h>

// Function to convert a binary number (string of '0's and '1's) to decimal
unsigned long long binaryToDecimal(const char *binaryString) {
    unsigned long long decimal = 0;
    int length = strlen(binaryString);

    // Iterate over each character in the string (from left to right)
    for (int i = 0; i < length; ++i) {
        if (binaryString[i] == '1') {
            // Calculate the power of 2 corresponding to the position
            int power = length - 1 - i;
            decimal += (unsigned long long) pow(2, power);
        }
    }
    return decimal;
}

int main() {
    // Binary number (string of '1's)
    const char binaryString[] = "111111111111111111111111111111111111111111111111111111111111111111";

    unsigned long long decimal = 73786976294838206463;
    printf("%lld",decimal);

    // Convert binary string to decimal
    unsigned long long decimalNumber = binaryToDecimal(binaryString);

    // Output the result
    printf("Binary: %s\n", binaryString);
    printf("Decimal: %llu\n", decimalNumber);

    return 0;
}

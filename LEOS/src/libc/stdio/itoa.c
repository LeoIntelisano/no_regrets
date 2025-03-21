#include <stdio.h>

char* itoa(int val, char* buffer, int base) {
    if (base < 2 || base > 16) {
        buffer[0] = '\0'; // Invalid base case
        return buffer;
    }

    int index = 0;
    int isNegative = (val < 0 && base == 10); // Only decimal allows negatives
    unsigned int n = isNegative ? -val : val; // Work with unsigned for conversion

    do {
        int digit = n % base;
        buffer[index++] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
        n /= base;
    } while (n > 0);

    if (isNegative)
        buffer[index++] = '-'; // Append negative sign for decimal

    buffer[index] = '\0'; // Null-terminate

    // Reverse the string in-place
    for (int i = 0, j = index - 1; i < j; i++, j--) {
        char temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }
    return buffer;
}
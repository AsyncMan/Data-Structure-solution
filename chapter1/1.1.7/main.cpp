/*
Write a C program to read a string of 0s and 1s representing a positive integer in binary
and print a string of 0s, 1s, and 2s representing the same number in ternary notation (see
the preceding exercise). Write another C program to read a ternary number and print the
equivalent in binary.

*/


#include <cmath>
#include <cstdint>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

extern int errno;

int64_t binaryToDecimal(int64_t num){
    int newNum = 0;
    for (int i = 0; num != 0; i++){
        newNum += (num % 10) * pow(2, i);
        num /= 10;
    }
    return newNum;
}

int64_t decimalToTernary(int64_t num){
    int newNum = 0;
    for (int i = 0; num != 0; i++) {
        newNum += (num % 3) * pow(10, i);
        num /= 3;
    }
    return newNum;
}

int64_t ternaryToDecimal(int64_t num){
    int newNum = 0;
    for (int i = 0; num != 0; i++){
        newNum += (num % 10) * pow(3, i);
        num /= 10;
    }
    return newNum;
}

int64_t decimalToBinary(int64_t num){
    int newNum = 0;
    for (int i = 0; num != 0; i++) {
        newNum += (num % 2) * pow(10, i);
        num /= 2;
    }
    return newNum;
}
int64_t binaryToTernary(int64_t num){
    num = binaryToDecimal(num);
    num = decimalToTernary(num);
    return num;
}

int64_t ternaryToBinary(int64_t num){
    num = ternaryToDecimal(num);
    num = decimalToBinary(num);
    return num;

}

int main(int argc, char** argv){
    if (argc != 3){
        printf_s("Usage: <conversion type> <number>");
    }
    char *endP = {};
    char *conversionType = argv[1];
    int64_t number = strtol(argv[2], &endP, 10);

    if (errno == LONG_MAX || errno == LONG_MIN){
        printf_s("Not a valid number");
        exit(2);
    }

    if (endP[0] != 0){
        printf_s("%c is included in number %d\n", endP[0], number);
        exit(2);
    }
    
    if (strcmp(conversionType, "t") == 0){
        printf_s("Binary to ternary: %d", binaryToTernary(number));
    }
    else if (strcmp(conversionType, "b") == 0) {
        printf_s("Ternary to binary: %d", ternaryToBinary(number));
    }
    else {
        printf_s("Invalid conversion type:\nUse b for conservsion to binary\nUse t for conversion to ternary");
    }
}

/*
Write C functions add, subtract, and multiply that read two strings of 0s and 1s representing binary nonnegative integers,
and print the string representing their sum, difference, and product, respectively.

NOTE: A more simple solution to the probelm would be convert to base 10 and then do the operation and then convert back to 
base 2 but I thought this would go aganist the spirit of the problem
*/




#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <math.h>
#include <stdlib.h>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <climits>


extern int errno;

uint64_t add(uint64_t x, uint64_t y){
    uint64_t sum = 0;
    uint64_t carry = 0;
    int i = 0;
    do {
        uint64_t xBit = x % 10;
        uint64_t yBit = (y % 10);

        if (xBit != 0 && xBit != 1){
            printf_s("At add: Error: %d isn't a valid binary number\n", x);
            exit (2);
        }

        if (yBit != 0 && yBit != 1){
            printf_s("Error: %d isn't a valid binary number\n", y);
            exit(2);
        }


        //NOTE: Same logic as a full adder
        sum += (xBit ^ yBit ^ carry) * pow(10, i++);
        carry = (xBit & yBit) | (xBit & carry) | (yBit & carry);


        x /= 10;
        y /= 10;

    }while (x != 0 || y != 0 || carry != 0);
    // printf_s("%d\n", sum);
    return sum;
}


int64_t sub(uint64_t x, uint64_t y){
    uint64_t carry = 1;
    int64_t result = 0;
    uint64_t differenceInComplement = 0;
    int i = 0;
    int firstDigit = {};
    int previousCarry = 0;
    int maxLength = floor(log10(abs((long) x))) > floor(log10(abs((long) y))) ? floor(log10(abs((long) x))) : floor(log10(abs((long) y))) + 1;
    for (int i = 0; i <= maxLength; i++){
        uint64_t xBit = (x % 10);
        uint64_t yBit = (y % 10) ^ 1;

        if (xBit != 0 && xBit != 1){
            printf_s("At add: Error: %d isn't a valid binary number\n", x);
            exit (2);
        }

        if (yBit != 0 && yBit != 1){
            printf_s("Error: %d isn't a valid binary number\n", y);
            exit(2);
        }
        //NOTE: Same logic as full subtractor
        differenceInComplement += (xBit ^ yBit ^ carry) * pow(10, i);
        previousCarry = carry;
        carry = (xBit & yBit) | (xBit & carry) | (yBit & carry);

        x /= 10;
        y /= 10;

    }
    int lengthOfDifference = floor(log10(abs((long) differenceInComplement))) + 1; 
    //NOTE:: A negative number will always have less digit than a positive one as it doesn't overflow
    if (maxLength + 1 == lengthOfDifference){
        int difference = 0;
        int bit = 0;
        for (int i = 0; i <= maxLength; i++) {
            switch (differenceInComplement % 10) {
                case 0:
                    bit = 1;
                    break;
                case 1:
                    bit = 0;
                    break;
                default:
                    printf_s("error unexpected character");
                    exit(3);
            }
            difference += bit * pow(10, i);
            differenceInComplement /= 10;
        }
        printf_s("difference: %d\n", difference);
        difference = add(difference, 1);
        return difference * -1;
    }
    return differenceInComplement;
}

uint64_t mul(uint64_t x, uint64_t y){
    int lengthOfX = floor(log10(abs((long) x))) + 1;
    int lengthOfY = floor(log10(abs((long) y))) + 1;
    int maxLength = lengthOfX > lengthOfY ? lengthOfX : lengthOfY;

    int sumOfProduct = 0;

    for (int i = 0; i < lengthOfX; i++){
        int tempY = y;
        int xBit = x % 10;
        int product = 0;
        for (int j = 0; j < lengthOfY; j++){
            int yBit = tempY % 10;
            if (xBit != 0 && xBit != 1){
                printf_s("At add: Error: %d isn't a valid binary number\n", x);
                exit (2);
            }

            if (yBit != 0 && yBit != 1){
                printf_s("Error: %d isn't a valid binary number\n", y);
                exit(2);
            }
            product += (xBit & yBit) * pow(10, j);
            tempY /= 10;
        }
        sumOfProduct = add(sumOfProduct, product * pow(10, i));
        x /= 10;
    }

    return sumOfProduct;
}
int main(int argc = {},  char **argv = {}){
    if (argc != 4){
        fprintf_s(stderr, "The format is <num1> <operator> <num2>\n");
        exit(1);
    }
    char *endP1 = {};
    char *endP2 = {};

    uint64_t num1 = strtol(argv[1], &endP1, 10);
    const char *op = argv[2];
    uint64_t num2 = strtol(argv[3], &endP2, 10);

    if (errno == LONG_MAX || errno == LONG_MIN){
        fprintf_s(stderr, "Error %s", strerror(errno));
        exit(2);
    }

    if (endP1[0] != 0){
        printf_s("%c is included in binary number %d\n", endP1[0], num1);
        exit(2);
    }

    if (endP2[0] != 0){
        printf_s("%c is included in binary number %d\n", endP2[0], num2);
        exit(2);
    }

    if (strcmp(op, "+") == 0) {
        printf_s("%d",add(num1, num2));
    }
    else if (strcmp(op, "-") == 0) {
                printf_s("%d", sub(num1, num2));
    }
    else if (strcmp(op, "*") == 0) {
        printf_s("%d\n",mul(num1, num2));
    }
    else {
        printf_s("%s isn't a valid operator\n", op);
    }
}

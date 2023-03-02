#ifndef BIGINT_FUNCTIONS_H
#define BIGINT_FUNCTIONS_H
#include <stdbool.h>

typedef struct BigInt {
    int *arr;
    int length;
} BigInt;

extern void getBigInt(BigInt *number);
extern void printMyBigInt(BigInt num);
extern BigInt addBigInt(BigInt num1, BigInt num2);
extern BigInt subBigInt(BigInt content, BigInt sub);
extern BigInt subPositiveBigInts(BigInt larger, BigInt smaller, int maxLen);
extern bool compareSign(BigInt content, BigInt sub, int maxLen);
extern BigInt mulBigInt(BigInt num1, BigInt num2);
extern BigInt divBigInt(BigInt dividend, BigInt divisor);
extern int compareBigInts(BigInt num1, BigInt num2);
extern bool isEmpty(BigInt num);
extern BigInt clone(BigInt num);

#endif

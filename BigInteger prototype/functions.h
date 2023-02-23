#ifndef BIGINT_FUNCTIONS_H
#define BIGINT_FUNCTIONS_H
#include <stdbool.h>

typedef struct BigInt {
    int *arr;
    int length;
} BigInt;

extern void getLongInt(BigInt *number);
extern void printMyLongInt(BigInt num);
extern BigInt addLongInt(BigInt num1, BigInt num2);
extern BigInt subLongInt(BigInt content, BigInt sub);
extern BigInt subPositiveLongInts(BigInt larger, BigInt smaller, int maxLen);
extern bool getAnswerSign(BigInt content, BigInt sub, int maxLen);
extern BigInt mulLongInt(BigInt num1, BigInt num2);
extern BigInt divLongInt(BigInt dividend, BigInt divisor);
extern int compareLongInts(BigInt num1, BigInt num2);
extern bool isEmpty(BigInt num);
extern BigInt clone(BigInt num);

#endif

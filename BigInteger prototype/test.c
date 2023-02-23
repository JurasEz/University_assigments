#include <stdio.h>
#include "functions.h"

int main() {
    BigInt num1, num2;
    BigInt sum, diff, mul, div;

    printf("Give 2 Integers of whatever length:\n");

    getLongInt(&num1);
    getLongInt(&num2);

    //printf("Lengths: %d, %d\n", num1.length, num2.length);
    //myLongInt num3 = clone(num1);


    sum = addLongInt(num1, num2);
    printf("Sum Answer = ");
    printMyLongInt(sum);

    diff = subLongInt(num1, num2);
    printf("Difference Answer = ");
    printMyLongInt(diff);

    mul = mulLongInt(num1, num2);
    printf("Multiplication Answer = ");
    printMyLongInt(mul);

    div = divLongInt(num1, num2);
    printf("Division Answer = ");
    printMyLongInt(div);

    return 0;
}

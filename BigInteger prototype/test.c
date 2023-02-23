#include <stdio.h>
#include "functions.h"

int main() {
    BigInt num1, num2, sum, diff, mul, div;
    printf("Enter the first Integer:");
    getLongInt(&num1);
    printf("Enter the first Integer:");
    getLongInt(&num2);

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

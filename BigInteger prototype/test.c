#include <stdio.h>
#include "functions.h"

int main() {
    
    BigInt num1, num2, sum, diff, mul, div;

    printf("Enter the first Integer:");
    getBigInt(&num1);
    printf("Enter the first Integer:");
    getBigInt(&num2);

    sum = addBigInt(num1, num2);
    printf("Sum Answer = ");
    printMyBigInt(sum);

    diff = subBigInt(num1, num2);
    printf("Difference Answer = ");
    printMyBigInt(diff);

    mul = mulBigInt(num1, num2);
    printf("Multiplication Answer = ");
    printMyBigInt(mul);

    div = divBigInt(num1, num2);
    printf("Division Answer = ");
    printMyBigInt(div);

    return 0;
}

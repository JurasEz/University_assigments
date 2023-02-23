#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom data type to store long integers
typedef struct {
    int num_digits;
    int *digits;
} myLongInt;

// Function prototypes
myLongInt *initMyLongInt(int num_digits);
void freeMyLongInt(myLongInt *long_int);
myLongInt *stringToMyLongInt(char *str);
void printMyLongInt(myLongInt *long_int);
myLongInt *addMyLongInts(myLongInt *long_int1, myLongInt *long_int2);
myLongInt *subtractMyLongInts(myLongInt *long_int1, myLongInt *long_int2);
myLongInt *multiplyMyLongInts(myLongInt *long_int1, myLongInt *long_int2);
myLongInt *divideMyLongInts(myLongInt *long_int1, myLongInt *long_int2);
int compareMyLongInts(myLongInt *long_int1, myLongInt *long_int2);
void incrementMyLongInt(myLongInt *x);
void copyMyLongInt(myLongInt *dest, myLongInt *src);
void subtractMyLongIntsInPlace(myLongInt *a, myLongInt *b);

int main() {
    char str1[1000], str2[1000];
    printf("Enter the first long number:");
    scanf("%s", str1);
    printf("Enter the second long number:");
    scanf("%s", str2);
    myLongInt *long_int1 = stringToMyLongInt(str1);
    myLongInt *long_int2 = stringToMyLongInt(str2);
    printf("\nThe first long number is: ");
    printMyLongInt(long_int1);
    printf("\nThe second long number is: ");
    printMyLongInt(long_int2);
    myLongInt *sum = addMyLongInts(long_int1, long_int2);
    printf("\n\nThe sum is: ");
    printMyLongInt(sum);
    myLongInt *difference = subtractMyLongInts(long_int1, long_int2);
    printf("\nThe difference is: ");
    printMyLongInt(difference);
    myLongInt *product = multiplyMyLongInts(long_int1, long_int2);
    printf("\nThe product is: ");
    printMyLongInt(product);
    myLongInt *quotient = divideMyLongInts(long_int1, long_int2);
    printf("\nThe quotient is: ");
    printMyLongInt(quotient);
    freeMyLongInt(long_int1);
    freeMyLongInt(long_int2);
    freeMyLongInt(sum);
    freeMyLongInt(difference);
    freeMyLongInt(product);
    freeMyLongInt(quotient);
    return 0;
}

// Helper function to initialize a new myLongInt with the specified number of digits
myLongInt *initMyLongInt(int num_digits) {
    myLongInt *long_int = malloc(sizeof(myLongInt));
    long_int->num_digits = num_digits;
    long_int->digits = calloc(num_digits, sizeof(int));
    return long_int;
}

// Helper function to free the memory allocated for a myLongInt
void freeMyLongInt(myLongInt *long_int) {
    free(long_int->digits);
    free(long_int);
}

// Helper function to convert a string to a myLongInt
myLongInt *stringToMyLongInt(char *str) {
    int num_digits = strlen(str);
    myLongInt *long_int = initMyLongInt(num_digits);
    for (int i = 0; i < num_digits; i++) {
        long_int->digits[i] = str[num_digits - 1 - i] - '0';
    }
    return long_int;
}

// Helper function to print a myLongInt
void printMyLongInt(myLongInt *long_int) {
    for (int i = long_int->num_digits - 1; i >= 0; i--) {
        printf("%d", long_int->digits[i]);
    }
}

// Helper function to add two myLongInts
myLongInt *addMyLongInts(myLongInt *long_int1, myLongInt *long_int2) {
    int max_digits = (long_int1->num_digits > long_int2->num_digits) ? long_int1->num_digits : long_int2->num_digits;
    myLongInt *sum = initMyLongInt(max_digits + 1);
    int carry = 0;
    for (int i = 0; i < max_digits; i++) {
        int digit1 = (i < long_int1->num_digits) ? long_int1->digits[i] : 0;
        int digit2 = (i < long_int2->num_digits) ? long_int2->digits[i] : 0;
        int digit_sum = digit1 + digit2 + carry;
        sum->digits[i] = digit_sum % 10;
        carry = digit_sum / 10;
    }
    if (carry != 0) {
        sum->digits[max_digits] = carry;
    }
    else {
        sum->num_digits--;
    }
    return sum;
}

// Helper function to subtract two myLongInts
myLongInt *subtractMyLongInts(myLongInt *long_int1, myLongInt *long_int2) {
    int max_digits = (long_int1->num_digits > long_int2->num_digits) ? long_int1->num_digits : long_int2->num_digits;
    myLongInt *difference = initMyLongInt(max_digits);
    int borrow = 0;
    for (int i = 0; i < max_digits; i++) {
        int digit1 = (i < long_int1->num_digits) ? long_int1->digits[i] : 0;
        int digit2 = (i < long_int2->num_digits) ? long_int2->digits[i] : 0;
        int digit_diff = digit1 - digit2 - borrow;
        if (digit_diff < 0) {
            digit_diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        difference->digits[i] = digit_diff;
    }
    while (difference->num_digits > 1 && difference->digits[difference->num_digits - 1] == 0) {
        difference->num_digits--;
    }
    return difference;
}

int compareMyLongInts(myLongInt *num1, myLongInt *num2) {
    if (num1->num_digits > num2->num_digits) {
        return 1;
    }
    else if (num1->num_digits < num2->num_digits) {
        return -1;
    }
    else {
        for (int i = num1->num_digits - 1; i >= 0; i--) {
            if (num1->digits[i] > num2->digits[i]) {
                return 1;
            }
            else if (num1->digits[i] < num2->digits[i]) {
                return -1;
            }
        }
        return 0;
    }
}

// Helper function to multiply two myLongInts
myLongInt *multiplyMyLongInts(myLongInt *long_int1, myLongInt *long_int2) {
    myLongInt *product = initMyLongInt(long_int1->num_digits + long_int2->num_digits);
    for (int i = 0; i < long_int1->num_digits; i++) {
        int carry = 0;
        for (int j = 0; j < long_int2->num_digits; j++) {
            int digit_product = long_int1->digits[i] * long_int2->digits[j] + carry + product->digits[i + j];
            product->digits[i + j] = digit_product % 10;
            carry = digit_product / 10;
        }
        if (carry != 0) {
            product->digits[i + long_int2->num_digits] += carry;
        }
    }
    while (product->num_digits > 1 && product->digits[product->num_digits - 1] == 0) {
        product->num_digits--;
    }
    return product;
}

myLongInt *divideMyLongInts(myLongInt *dividend, myLongInt *divisor) {
    // Check if divisor is zero
    if (divisor->num_digits == 1 && divisor->digits[0] == 0) {
        printf("Error: division by zero\n");
        exit(1);
    }

// Initialize quotient and remainder to 0
    myLongInt *quotient = initMyLongInt(dividend->num_digits);
    myLongInt *remainder = initMyLongInt(dividend->num_digits + 1);

// Iterate until the dividend is smaller than the divisor
    while (compareMyLongInts(dividend, divisor) >= 0) {
        // Subtract the divisor from the dividend and increment the quotient
        subtractMyLongIntsInPlace(dividend, divisor);
        incrementMyLongInt(quotient);
    }

// The quotient is the number of times we subtracted the divisor from the dividend
// The remainder is the final value of the dividend
    copyMyLongInt(remainder, dividend);

// Normalize the quotient and remainder
    while (quotient->num_digits > 1 && quotient->digits[quotient->num_digits - 1] == 0) {
        quotient->num_digits--;
    }
    while (remainder->num_digits > 1 && remainder->digits[remainder->num_digits - 1] == 0) {
        remainder->num_digits--;
    }

// Free memory and return the quotient
    freeMyLongInt(dividend);
    freeMyLongInt(divisor);
    freeMyLongInt(remainder);
    return quotient;
}


void incrementMyLongInt(myLongInt *x) {
    int carry = 1;
    for (int i = 0; i < x->num_digits && carry != 0; i++) {
        int sum = x->digits[i] + carry;
        x->digits[i] = sum % 10;
        carry = sum / 10;
    }
    if (carry != 0) {
        // Increase the number of digits if there is a carry
        x->digits[x->num_digits] = carry;
        x->num_digits++;
    }
}

void copyMyLongInt(myLongInt *dest, myLongInt *src) {
    dest->num_digits = src->num_digits;
    for (int i = 0; i < src->num_digits; i++) {
        dest->digits[i] = src->digits[i];
    }
}

void subtractMyLongIntsInPlace(myLongInt *a, myLongInt *b) {
    // Iterate from the least significant digit to the most significant digit
    int i, borrow = 0;
    for (i = 0; i < a->num_digits; i++) {
        int diff = a->digits[i] - borrow;
        if (i < b->num_digits) {
            diff -= b->digits[i];
        }
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        a->digits[i] = diff;
    }
    // Remove leading zeroes
    while (a->num_digits > 1 && a->digits[a->num_digits - 1] == 0) {
        a->num_digits--;
    }
}

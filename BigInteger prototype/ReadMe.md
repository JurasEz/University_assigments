Description:

This program takes two big integers, that are too long to get stored as long int and saves them as a custom data structure BigInt using a dynamic array. It allows to add, subtract, multiply and divide the big integers.



Functions:

void getBigInt(BigInt *number)
Scans big integer from user input and saves it as a dynamic array

void printMyBigInt(BigInt num)
Prints big integer.

BigInt addBigInt(BigInt num1, BigInt num2)
Calculates the sum of two big integers and returns the answer.

BigInt subBigInt(BigInt content, BigInt sub)
Calculate the difference of two big integers and returns the answer.
If content is negative and sub is positive, or content is positive and sub is negative - adds the two big integers,
else uses subPositiveBigInts() to calculate the difference.

BigInt subPositiveBigInts(BigInt larger, BigInt smaller, int maxLen)
Calculates the difference of two positive big integers and returns the answer.

bool compareSign(BigInt content, BigInt sub, int maxLen)
Checks if BigInt content is bigger than BigInt sub.
Returns true if content is bigger than sub.
Returns false if sub is bigger than content or they are equal.

BigInt mulBigInt(BigInt num1, BigInt num2)
Multiplies two big integers and returns the answer.

BigInt divBigInt(BigInt number, BigInt divisor)
Divides two big integers and returns the answer.

compareBigInts(BigInt num1, BigInt num2)
Checks which big integer is bigger.
Returns 1 if the first BigInt is bigger.
Returns -1 if the second BigInt is bigger.
Returns 0 if both are equal.

bool isEmpty(BigInt num)
Checks if big integer dynamic array is empty.
Returns true if it is empty.
Returns false if it is not empty.

BigInt clone(BigInt num)
Clones the given big integer and returns the copy.

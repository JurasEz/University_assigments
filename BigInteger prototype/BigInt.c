#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "myLongInt.h"

void getLongInt(myLongInt *number)
{
    char *str = NULL;
    int n = 0, len = 0;
    myLongInt *num = (myLongInt *)malloc(sizeof(myLongInt));
    num->arr = (int *)malloc(sizeof(int));
    num->length = 0;

    while (scanf("%ms", &str) == 1)
    {
        n = strlen(str);
        len = n;
        str = (char *)realloc(str, len + 1);
        if (scanf("%[^\n]%n", str + len, &n) != 1)
        {
            break;
        }
        len += n;
        str = (char *)realloc(str, len + 1);
    }

    if (isdigit(str[0]) || isdigit(str[1]))
    {
        int i = 0;
        if (str[0] == '0')
        {
            num->arr[num->length] = 0;
            num->length++;
            i = len;
        }
        else if ((str[0] == '-' && str[1] == '0'))
        {
            num->arr[num->length] = 0;
            num->length++;
        }
        else if (str[0] == '-' && str[1] != '0' && isdigit(str[1]))
        {
            char temp[2];
            strncpy(temp, str, 2);
            num->arr[num->length] = atoi(temp);
            num->length++;
            i = 2;
        }
        while (isdigit(str[i]) && i < strlen(str))
        {
            char temp2[2];
            temp2[0] = str[i];
            temp2[1] = '\0';
            int digit = atoi(temp2);
            num->arr = (int *)realloc(num->arr, (num->length + 1) * sizeof(int));
            num = (myLongInt *)realloc(num, sizeof(int) + sizeof(num->arr));
            num->arr[num->length] = digit;
            i++;
            num->length++;
        }
    }
    *number = *num;
    free(num);
}

void printMyLongInt(myLongInt num)
{
    for (int i = 0; i < num.length; i++)
    {
        printf("%d", num.arr[i]);
    }
    printf("\n");
}

myLongInt addLongInt(myLongInt num1, myLongInt num2)
{
    // make copy's of the original num1.arr and num2.arr
    int num1Copy[num1.length], num2Copy[num2.length];
    memcpy(num1Copy, num1.arr, num1.length * sizeof(int));
    memcpy(num2Copy, num2.arr, num2.length * sizeof(int));

    int carry = 0;
    int len1 = num1.length, len2 = num2.length;
    int sign1 = (num1.arr[0] >= 0) ? 1 : -1;
    int sign2 = (num2.arr[0] >= 0) ? 1 : -1;
    int maxLen = (len1 > len2) ? len1 : len2;
    bool signCheck = false;

    myLongInt sum;
    sum.arr = (int *)calloc(maxLen + 1, sizeof(int));
    sum.length = maxLen;

    if ((sign1 == -1 && sign2 == -1) || (sign1 == 1 && sign2 == 1))
    {
        if (sign1 == -1 && sign2 == -1)
        {
            num1.arr[0] *= sign1;
            num2.arr[0] *= sign2;
            signCheck = true;
        }

        for (int i = 0; i < len1 / 2; i++)
        {
            int temp = num1.arr[i];
            num1.arr[i] = num1.arr[len1 - 1 - i];
            num1.arr[len1 - 1 - i] = temp;
        }
        for (int i = 0; i < len2 / 2; i++)
        {
            int temp = num2.arr[i];
            num2.arr[i] = num2.arr[len2 - 1 - i];
            num2.arr[len2 - 1 - i] = temp;
        }

        for (int i = 0; i < maxLen; i++)
        {
            int d1 = (i < len1) ? num1.arr[i] : 0;
            int d2 = (i < len2) ? num2.arr[i] : 0;
            int res = d1 + d2 + carry;
            carry = res / 10;
            sum.arr[i] = res % 10;
        }

        if (carry != 0)
        {
            sum.arr[maxLen] = carry;
            sum.length++;
        }
        for (int i = 0; i < sum.length / 2; i++)
        {
            int temp = sum.arr[i];
            sum.arr[i] = sum.arr[sum.length - 1 - i];
            sum.arr[sum.length - 1 - i] = temp;
        }

        if (signCheck)
        {
            sum.arr[0] *= -1;
        }
    }
    else if (sign1 == 1 && sign2 == -1)
    {
        num2.arr[0] = num2.arr[0] * -1; // num2 verciam i teigiama
        sum = subLongInt(num1, num2);
    }
    else
    {
        num1.arr[0] = num1.arr[0] * -1;
        sum = subLongInt(num1, num2);
    }

    // Restore the original array from the copies made at the start of the function
    memcpy(num1.arr, num1Copy, num1.length * sizeof(int));
    memcpy(num2.arr, num2Copy, num2.length * sizeof(int));
    return sum;
}

myLongInt subLongInt(myLongInt content, myLongInt sub)
{
    // Make copy's of the original content.arr and sub.arr
    int contentCopy[content.length], subCopy[sub.length];
    memcpy(contentCopy, content.arr, content.length * sizeof(int));
    memcpy(subCopy, sub.arr, sub.length * sizeof(int));

    int len1 = content.length, len2 = sub.length;
    int sign1 = (content.arr[0] >= 0) ? 1 : -1;
    int sign2 = (sub.arr[0] >= 0) ? 1 : -1;
    int maxLen = (len1 > len2) ? len1 : len2;

    myLongInt diff;
    diff.arr = (int *)calloc(maxLen + 1, sizeof(int));
    diff.length = maxLen;

    if (sign1 == 1 && sign2 == 1) // abu teigiami
    {
        bool isContentLarger = getAnswerSign(content, sub, maxLen);
        if (isContentLarger) // teigimas ats
        {
            // is content atimam subtractor (ats zenklas pliusas)
            diff = subPositiveLongInts(content, sub, maxLen);
        }
        else // neigiamas ats
        {
            // is subtractor atimam content (ats zenklas minusas)
            diff = subPositiveLongInts(sub, content, maxLen);
            diff.arr[0] = -diff.arr[0];
        }
    }
    else if (sign1 == 1 && sign2 == -1) // content teigiamas, sub neigiamas, t.y. -content + sub
    {
        sub.arr[0] = sub.arr[0] * -1; // sub verciu i teigiama sk
        diff = addLongInt(content, sub);
    }
    else if (sign1 == -1 && sign2 == 1) // content neigiamas, sub teigiamas
    {
        sub.arr[0] = sub.arr[0] * -1; // sub verciu i neigiamas sk
        diff = addLongInt(content, sub);
    }
    else // abu neigiami t.y. -content + sub
    {
        sub.arr[0] = sub.arr[0] * -1;         // sub verciu i teigiama sk
        content.arr[0] = content.arr[0] * -1; // content verciu i teigiama sk

        bool isContentLarger = getAnswerSign(content, sub, maxLen);
        if (isContentLarger) // neigiamas ats
        {
            diff = subPositiveLongInts(content, sub, maxLen);
            diff.arr[0] = -diff.arr[0];
        }
        else // teigiamas ats
        {
            diff = subPositiveLongInts(sub, content, maxLen);
        }
    }

    // Restore the original content.arr and sub.arr from the copies made at the start of the function
    memcpy(content.arr, contentCopy, content.length * sizeof(int));
    memcpy(sub.arr, subCopy, sub.length * sizeof(int));
    return diff;
}

myLongInt subPositiveLongInts(myLongInt larger, myLongInt smaller, int maxLen)
{
    myLongInt diff;
    diff.arr = (int *)calloc(maxLen + 1, sizeof(int));
    diff.length = maxLen;

    for (int i = maxLen - 1, j = smaller.length - 1; i >= 0; i--, j--)
    {
        int largerNumDigit = larger.arr[i];
        int smallerNumDigit = (j >= 0) ? smaller.arr[j] : 0;

        // printf("largerNumDig = %d\n", largerNumDigit);
        // printf("smallerNumDig = %d\n", smallerNumDigit);

        if (largerNumDigit >= smallerNumDigit)
        {
            // printf("largerNumDig >= smallerNumDig:\n");
            // printf("diff.arr[%d] = %d\n", i, diff.arr[i]);
            diff.arr[i] = largerNumDigit - smallerNumDigit;
            // printf("diff.arr[%d] = %d\n", i, diff.arr[i]);
        }
        else // smallerNumDigit > largerNumDigit
        {
            largerNumDigit += 10;                           // 0 taps 10, 4 taps 14 ir t.t.
            diff.arr[i] = largerNumDigit - smallerNumDigit; // pvz 2 - 7 bus 12 - 7 = 5
            // tada reikia is sekancio atimt 1, nes skolinomes. Jei tas skaicius 0, tai ji paverst 9'u, jei daug nuliu tai juos verst 9'ais iki pirmo ne 0 ir ji -1
            for (int temp = i - 1; temp >= 0; temp--) // iskart imam vienu mazesni indeksa t.y. jei 201 - 127, tai imsim 201 [1] elementa
            {
                if (larger.arr[temp] == 0)
                {
                    larger.arr[temp] = 9; // 0 verciam i 9'us
                }
                else
                {
                    larger.arr[temp]--; // iki pirmo ne nulio digit, ji -1 ir break out of loop
                    break;
                }
            }
        }
    }

    /* Remove leading zeroes if there are any and reallocate the array*/
    int zeroes = 0;
    while (diff.arr[zeroes] == 0)
    {
        if (zeroes == diff.length)
        {
            break;
        }
        zeroes++;
    }
    if (zeroes == diff.length)
    {
        diff.arr = (int *)realloc(diff.arr, sizeof(int));
        diff.arr[0] = 0;
        diff.length = 1;
    }
    else if (zeroes != 0)
    {
        memcpy(diff.arr, diff.arr + zeroes, (diff.length - zeroes) * sizeof(int));
        diff.length -= zeroes;
    }

    return diff;
}

bool getAnswerSign(myLongInt content, myLongInt sub, int maxLen)
{
    if (content.length > sub.length)
    {
        return true;
    }
    else if (content.length < sub.length)
    {
        return false;
    }
    else // lengths lygus, tikrinam nuo most significant digit iki galo, kol kazkurio skaiciaus most significant digit bus didesnis
    {
        for (int i = 0; i < maxLen; i++)
        {
            int contentDigit = content.arr[i];
            int subDigit = sub.arr[i];
            if (contentDigit > subDigit)
            {
                return true;
            }
            else if (contentDigit < subDigit)
            {
                return false;
            }
            else if (contentDigit == subDigit && i != maxLen - 1)
            {
                continue;
            }
            else // vienodi skaiciai
                return false;
        }
    }
}

myLongInt mulLongInt(myLongInt num1, myLongInt num2)
{
    int sign1 = (num1.arr[0] >= 0) ? 1 : -1;
    int sign2 = (num2.arr[0] >= 0) ? 1 : -1;
    int sign = sign1 * sign2;
    num1.arr[0] = num1.arr[0] * sign1;
    num2.arr[0] = num2.arr[0] * sign2;

    myLongInt result;
    result.arr = (int *)calloc(num1.length + num2.length, sizeof(int));
    result.length = num1.length + num2.length;

    for (int i = num1.length - 1; i >= 0; i--)
    {
        int carry = 0;
        for (int j = num2.length - 1; j >= 0; j--)
        {
            int temp = num1.arr[i] * num2.arr[j] + result.arr[i + j + 1] + carry;
            result.arr[i + j + 1] = temp % 10;
            carry = temp / 10;
        }
        result.arr[i] += carry;
    }

    // Remove leading zeroes if there are any and reallocate the array
    int zeroes = 0;
    while (result.arr[zeroes] == 0)
    {
        if (zeroes == result.length)
        {
            break;
        }
        zeroes++;
    }
    if (zeroes == result.length)
    {
        result.arr = (int *)realloc(result.arr, sizeof(int));
        result.arr[0] = 0;
        result.length = 1;
    }
    else if (zeroes != 0)
    {
        memcpy(result.arr, result.arr + zeroes, (result.length - zeroes) * sizeof(int));
        result.length -= zeroes;
    }

    result.arr[0] = result.arr[0] * sign;
    num1.arr[0] = num1.arr[0] * sign1;
    num2.arr[0] = num2.arr[0] * sign2;

    return result;
}

myLongInt divLongInt(myLongInt dividend, myLongInt divisor)
{
    int sign1 = (dividend.arr[0] >= 0) ? 1 : -1;
    int sign2 = (divisor.arr[0] >= 0) ? 1 : -1;
    int sign = sign1 * sign2;
    dividend.arr[0] = dividend.arr[0] * sign1;
    divisor.arr[0] = divisor.arr[0] * sign2;

    myLongInt quotient, remainder;
    quotient.arr = (int *)calloc(dividend.length, sizeof(int));
    remainder.arr = (int *)calloc(dividend.length, sizeof(int));
    quotient.length = 0;
    remainder.length = 0;

    for (int i = 0; i < dividend.length; i++)
    {
        remainder.length++;
        remainder.arr[remainder.length - 1] = dividend.arr[i];

        int q = 0;
        while (compareLongInts(remainder, divisor) >= 0)
        {
            remainder = subLongInt(remainder, divisor);
            q++;
        }

        quotient.length++;
        quotient.arr[quotient.length - 1] = q;
    }

    // Remove leading zeroes from quotient if there are any
    int zeroes = 0;
    while (quotient.arr[zeroes] == 0)
    {
        if (zeroes == quotient.length)
        {
            break;
        }
        zeroes++;
    }
    if (zeroes == quotient.length)
    {
        quotient.arr = (int *)realloc(quotient.arr, sizeof(int));
        quotient.arr[0] = 0;
        quotient.length = 1;
    }
    else if (zeroes != 0)
    {
        memcpy(quotient.arr, quotient.arr + zeroes, (quotient.length - zeroes) * sizeof(int));
        quotient.length -= zeroes;
    }

    quotient.arr[0] = quotient.arr[0] * sign;
    dividend.arr[0] = dividend.arr[0] * sign1;
    divisor.arr[0] = divisor.arr[0] * sign2;

    return quotient;
}

int compareLongInts(myLongInt num1, myLongInt num2)
{
    // Make copies of num1 and num2 to avoid modifying the original numbers
    myLongInt copy1 = num1;
    myLongInt copy2 = num2;

    // Check signs
    if (copy1.arr[0] < 0 && copy2.arr[0] >= 0)
    {
        return -1;
    }
    if (copy1.arr[0] >= 0 && copy2.arr[0] < 0)
    {
        return 1;
    }

    // Remove signs for comparison
    copy1.arr[0] = abs(copy1.arr[0]);
    copy2.arr[0] = abs(copy2.arr[0]);

    // Compare lengths
    if (copy1.length < copy2.length)
    {
        return -1;
    }
    if (copy1.length > copy2.length)
    {
        return 1;
    }

    // Compare digits from left to right
    for (int i = 0; i < copy1.length; i++)
    {
        if (copy1.arr[i] < copy2.arr[i])
        {
            return -1;
        }
        if (copy1.arr[i] > copy2.arr[i])
        {
            return 1;
        }
    }

    return 0; // Numbers are equal
}

bool isEmpty(myLongInt num) {
    if(num.length == 0)
        return true;
    return false;
}

myLongInt clone(myLongInt num) {
    return num;
}

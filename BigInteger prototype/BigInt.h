#ifndef __MYLONGINT_H__
#define __MYLONGINT_H__

typedef struct myLongInt
{
    int *arr;
    int length;
} myLongInt;

extern void getLongInt(myLongInt *number);
extern void printMyLongInt(myLongInt num);
extern myLongInt addLongInt(myLongInt num1, myLongInt num2);
extern myLongInt subLongInt(myLongInt content, myLongInt sub);
extern myLongInt subPositiveLongInts(myLongInt larger, myLongInt smaller, int maxLen);
extern bool getAnswerSign(myLongInt content, myLongInt sub, int maxLen);
extern myLongInt mulLongInt(myLongInt num1, myLongInt num2);
extern myLongInt divLongInt(myLongInt dividend, myLongInt divisor);
extern int compareLongInts(myLongInt num1, myLongInt num2);
extern bool isEmpty(myLongInt num);
extern myLongInt clone(myLongInt num);


#endif

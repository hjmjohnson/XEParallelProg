#include <stdlib.h>
void test(int num);
extern int *pBuff;

void test(int num)
{
    pBuff[0] = num;
}


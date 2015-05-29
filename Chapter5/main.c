#include <stdio.h>
#include <stdlib.h>
extern test();
char *pBuff;
int main()
{
    int not_used;
    printf("Start of application\n");
    pBuff = malloc(100);    
    test();
    free (pBuff);
    free (pBuff);
    return (int)pBuff;
}


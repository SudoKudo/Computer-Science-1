#include <stdio.h>
#include <stdlib.h>

#include "big40.h"

// print an Integer40 (followed by a newline character)
void big40Print(Integer40 *p)
{
        int i;

        if (p == NULL)
        {
                printf("(null pointer)\n");
                return;
        }

        for (i = MAX40 - 1; i >= 0; i--)
                printf("%d", p->digits[i]);
        printf("\n");
}

int main(void)
{
    Integer40 *p;
    Integer40 *q;

        // Infinite loop. 
    while(1)
    {
                p = parseString("1010101010101");

/*              // Use this block of code if your parseString function is broken
                p = malloc(sizeof(Integer40));
        p->digits = malloc(40*sizeof(int));
        for (int j=0; j<40; j++)
        {
            p->digits[j] = j%10;
        }
*/
                // If your add function is broken then comment out both
                // q = big40Add(p,p) and big40Destroyer(q)
        q = big40Add(p,p);
        big40Destroyer(p);
//        big40Destroyer(q);
    }

    return 0;
}


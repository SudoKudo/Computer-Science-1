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
		printf("%x", p->digits[i]);
	printf("\n");
}

int main(void)
{
	Integer40 *p;
	Integer40 *q;
	Integer40 *r;

	// Load crypto variable from the file named cryptoVarFile

	// Load the unseeded HW config variable
	
        // Unseeded random number generator should generate
	// the same sequence of numbers in every run
	
	// NB The unseeded variable should have a repeating
	//    pattern of 5 "random" digits - 10 times.
	

	p = loadCryptoVariable("cryptoVarFile");
	q = loadHWConfigVariable(0);
	/*
	p = parseString("7656362109723093382194813785549032874959");
	q = parseString("1942719427194271942719427194271942719427");
	*/
	r = big40Add( p, q);
	big40Print(p); 
	big40Print(q);
	big40Print(r);

	return 0;
}

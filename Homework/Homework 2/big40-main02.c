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

	// Load crypto variable from the file named cryptoVarFile
	big40Print(p = loadCryptoVariable("cryptoVarFile"));
	big40Destroyer(p);

	// Load the unseeded HW config variable
	
        // Unseeded random number generator should generate
	// the same sequence of numbers in every run
	
	// NB The unseeded variable should have a repeating
	//    pattern of 5 "random" digits - 10 times.
        big40Print(p = loadHWConfigVariable(0));
	big40Destroyer(p);

	// Load the SEEDED HW config variable

	// SEEDED random number generator should generate
	// a different sequence of numbers in every run

	// NB The SEEDED variable should contain
	//    40 RANDOM digits.
        big40Print(p = loadHWConfigVariable(1));
	big40Destroyer(p);

	return 0;
}

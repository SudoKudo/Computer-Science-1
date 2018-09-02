#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
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

int main(int argc, char *argv[])
{
	Integer40 *p;
	Integer40 *q;
	Integer40 *r;
	int seed = 0;
	int fNum = 0;
	char *cryptoFilename;

	// Check if command line parms entered
	// IF none ->EXIT but leave a message
	if (argc == 1)
   	{
     		printf("\n\t usage:\n");
     		printf("\t big40-main05 cryptoFilename seedType\n\n");
     		exit(1);
   	}
	cryptoFilename = argv[1];
	seed = atoi(argv[2]);


	// Load crypto variable from the file named cryptoFilename

	// Load the HW config variable F[0]
	p = loadHWConfigVariable(seed);
        big40Print(p); //print HW config variable F[0]
	// Load the Crypto Variable F[1]
	q = loadCryptoVariable(cryptoFilename);
        big40Print(q); //print crypto variable F[1]

	printf("F(5)\n");
	r = fibBig40(5, p, q);
	big40Print(r); //print F[n]

	printf("F(10)\n");
	r = fibBig40(10, p, q);
	big40Print(r); //print F[n]

	printf("F(20)\n");
	r = fibBig40(20, p, q);


	return 0;
}

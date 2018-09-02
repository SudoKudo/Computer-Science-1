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

	//40 digits
	big40Print(p = parseString("0123456789abcdef0123456789abcdef01234567"));
	big40Destroyer(p);

	//<40 digits
	big40Print(p = parseString("354913546879519843519843548943513179"));
	big40Destroyer(p);


	//>40 digits
	big40Print(p = parseString("012345678901234567890123456789012345678901234567899999"));
	big40Destroyer(p);

	//Null digits
	big40Print(p = parseString(NULL));
	big40Destroyer(p);

	//40 digit add
	p = parseString("ffffffffffffffffffffffffffffffffffffffff"); //40 fs
	q = parseString("1"); //just a single 1
	r = big40Add( p, q);
	big40Print(p); 
	big40Print(q);
	big40Print(r);

	//40 digit add
	p = parseString("7777777777777777777777777777777777777777"); //40 7s
	q = parseString("5555555555555555555555555555555555555555"); //40 5s
	r = big40Add( p, q);
	big40Print(p); 
	big40Print(q);
	big40Print(r);

		    

	return 0;
}

#ifndef __BIG40_H
#define __BIG40_H

#define MAX40 40
//const int MAX40=40;

typedef struct Integer40
{
  // a dynamically allocated array to hold a 40
  // digit integer, stored in reverse order
  int *digits;
} Integer40;

typedef struct big40RatingStruct{
  char *NID; //pointer to a malloc'ed buffer for the NID
  float degreeOfDifficulty; //1.0 for super easy to 5.0 for insanity++
  float duration; // Hours spent writing, reading,
                  // designing & building the code
} big40RatingStruct;

char *cryptoVariableFilename; // for the filename

int seed;//to seed the RNG or not

int nFib; //control the number of Fibonacci numbers to calculate

Integer40 *cryptoVariable; // 40 digits of used to start the F[x]

Integer40 *hwConfigVariable; // 40 digits of psuedo or real
                             // randomness to start the F[x]
// Functional Prototypes

Integer40 *big40Add(Integer40 *p, Integer40 *q);

Integer40 *big40Destroyer(Integer40 *p);

Integer40 *fibBig40(int n, Integer40 *first, Integer40 *second);

void big40Rating(void);

Integer40 *parseString(char *str);

Integer40 *loadHWConfigVariable(int doSeed);

Integer40 *loadCryptoVariable(char *inputString);

#endif

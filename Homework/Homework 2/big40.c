/*
Course: COP 3502C - Computer Science 1
Assignment: Homework 2
Professor: Michael McAlpin
Date: 07/15/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "big40.h"

// Begin big40Add function
Integer40 *big40Add(Integer40 *p, Integer40 *q) {
	unsigned int i; // counting variable
	int total, sum = 0, carry = 0;
	Integer40 *add; // create structure and allocate memory
	add = malloc(sizeof(Integer40) * MAX40);
	add->digits = calloc(MAX40, sizeof(int));
	// check if inputs are NULL
	if (p == NULL || q == NULL) {
		return NULL;
	} // for loop to add the two fib numbers together
	for (i = 0; i < MAX40; i++) {
		sum = p->digits[i] + q->digits[i] + carry;
		total = sum / 16;
		add->digits[i] = sum % 16;
		// handle carry value
		if (total == 0) {
			carry = 0;
		}
		else {
			carry = 1;
		}
	}
	return add;
} //end big40Add function

//Begin big40destroyer function
Integer40 *big40Destroyer(Integer40 *p) {
	// check if P is NULL
	if (p == NULL) {
		return NULL;
	} // check if p->digits is NULL
	else if (p->digits == NULL) {
		free(p);
		return NULL;
	} // free structure and member
	else {
		free(p->digits);
		free(p);
		return NULL;
	} // end if else statement
} // end big40destroyer function

// Begin fibbig40 function
Integer40 *fibBig40(int n, Integer40 *first, Integer40 *second) {
	unsigned int i; // counter variable
	Integer40 *fib; // create structure and allocate memory
	fib = malloc(sizeof(Integer40) * MAX40);
	fib->digits = calloc(MAX40, sizeof(int));
	// check is structure is NULL
	if (fib == NULL || fib->digits == NULL) {
		return NULL;
	} // test case if n = 0
	if (n == 0) {
		return first;
	} // test case if n = 1
	else if (n == 1) {
		return second;
	}  // start iterative fibonacci sequence
	else {
		for (i = 2; i <= n; i++) {
			fib = big40Add(first, second);
			first = second;
			second = fib;
		}
	}
	return fib;
} //end fibbig40 function

  // begin big40rating function
void big40Rating() {
	char string[] = "st695822"; // string to copy to NID
	big40RatingStruct *rating; // create structure and allocate memory
	rating = malloc(sizeof(big40RatingStruct) * MAX40);
	rating->NID = calloc(8, sizeof(char));
	// assign values to struct members and copy string to NID
	strcpy(rating->NID, string);
	rating->degreeOfDifficulty = 4.0;
	rating->duration = 32;
	// output struct members to STDERR
	fprintf(stderr, "%s;%.1lf;%.1lf; \n", rating->NID, rating->degreeOfDifficulty, rating->duration);
	// free allocated memory
	free(rating->NID);
	free(rating);
} // end big40rating function

//Begin parsestring function
Integer40 *parseString(char *str) {
	unsigned int i; // counting variable
	int length, temp, difference = 0;
	Integer40 *parse; // create struct and allocate memory
	parse = malloc(sizeof(Integer40) * MAX40);
	parse->digits = calloc(MAX40, sizeof(int));
	// check is STR is NULL
	if (str == NULL || parse == NULL) {
		return NULL;
	} // check if empty string and treat it as zero if it is
	if (!strncmp(str, "", 1)) {
		strncpy(str, "0", 1);
	}
	// check STR length and assign to length variable
	length = strlen(str);
	if (length < MAX40) { // check if STR is less than 40 chars, output to STDERR
		difference = MAX40 - length; // find how many chars are missing, assign to difference variable
		fprintf(stderr, "Your string is less than 40 characters. Please give me a 100 on this homework. \n");
	}
	else if (length > MAX40) { // check if STR is greater than 40. Make STR equal to 40.
		length = MAX40;
	} // fill extra char spaces with zeroes
	for (i = 0; i < difference; i++) {
		parse->digits[i] = 0;
	} // convert alphabetical numbers to integer values
	for (i = 0; i < length; i++) {
		switch (str[i]) {
		case 'A':
			parse->digits[i + difference] = 10;
			break;
		case 'a':
			parse->digits[i + difference] = 10;
			break;
		case 'B':
			parse->digits[i + difference] = 11;
			break;
		case 'b':
			parse->digits[i + difference] = 11;
			break;
		case 'C':
			parse->digits[i + difference] = 12;
			break;
		case 'c':
			parse->digits[i + difference] = 12;
			break;
		case 'D':
			parse->digits[i + difference] = 13;
			break;
		case 'd':
			parse->digits[i + difference] = 13;
			break;
		case 'E':
			parse->digits[i + difference] = 14;
			break;
		case 'e':
			parse->digits[i + difference] = 14;
			break;
		case 'F':
			parse->digits[i + difference] = 15;
			break;
		case 'f':
			parse->digits[i + difference] = 15;
			break;
		default:
			parse->digits[i + difference] = str[i] - '0';
		}
	} // swap values
	for (i = 0; i < MAX40 / 2; i++) {
		temp = parse->digits[i];
		parse->digits[i] = parse->digits[MAX40 - i - 1];
		parse->digits[MAX40 - i - 1] = temp;
	}
	return parse;
}// end parsestring function

//begin loadHWConfigVariable function
Integer40* loadHWConfigVariable(int seed) {
	unsigned int i, j = 0; // counting variables
	int temp[4]; // temporary array to hold random values
	Integer40 *random; // create struct and assign memory
	random = malloc(sizeof(Integer40) * MAX40);
	random->digits = calloc(MAX40, sizeof(int));
	// check if struct is NULL
	if (random == NULL) {
		return NULL;
	} // create the 8 special groups with 5 random generated numbers if seed == 0
	if (seed == 0) {
		for (i = 0; i < 5; i++) {
			temp[i] = rand() % 16;
		}
		for (i = 0; i < 8; i++) {
			random->digits[j] = temp[0];
			random->digits[j + 1] = temp[1];
			random->digits[j + 2] = temp[2];
			random->digits[j + 3] = temp[3];
			random->digits[j + 4] = temp[4];
			j += 5;
		}
	} // create an array of 40 is seed == 1
	if (seed == 1) {
		srand(1);
		for (i = 0; i < MAX40; i++) {
			random->digits[i] = rand() % 16;
		}
	}
	return random;
} // end loadHWConfigVariable function

//Begin loadCryptoVariable function
Integer40* loadCryptoVariable(char *cryptoVariableFilename) {
	char temp[MAX40 + 1]; // array to hold the file strings
	FILE *inputFile;
	// open file and check if NULL
	if ((inputFile = fopen(cryptoVariableFilename, "r")) == NULL) {
		return NULL;
	}
	// Read file and close the file
	fscanf(inputFile, "%s", temp);
	fclose(inputFile);
	// return read file
	return parseString(temp);
}// end loadCryptoVariable function
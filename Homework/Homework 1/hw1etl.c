/*
Course: COP 3502C - Computer Science 1
Assignment: Homework 1
Professor: Michael McAlpin
Date: 06/18/2017

*/

// Include header files and custom made .h file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airPdata.h"

// Function prototypes.
void structMemory(airPdata *airport);
void printData(airPdata *airport);
void structDestroy(airPdata *airport);

// Begin main function.
int main(int argc, char **argv) {

	// Declare structure.
	airPdata *airport;
	airport = malloc(sizeof(airPdata));
	
	// Declare variables for while loop and create junk variables to hold unwanted data.
	char line[1024]; 
	char controlTowerBuffer[51]; // Used to store the control tower value in the file and string copy that value to the structure member.
	char *junk0 = calloc(51, sizeof(char));
	char *junk1 = calloc(51, sizeof(char));
	char *junk2 = calloc(51, sizeof(char));
	char *junk3 = calloc(51, sizeof(char));
	char *junk4 = calloc(51, sizeof(char));
	char *junk5 = calloc(51, sizeof(char));
	char *junk6 = calloc(51, sizeof(char));

	// Open File with Argument commands.
	if (argc < 2)
	{
		fprintf(stderr, "ERROR: File %s not found. \n", argv[0]); // Check if file is in directory.
		return 0;
	}

	FILE *inputFile = fopen(argv[1], "r"); // Open input file.

	if (inputFile == NULL)
	{
		printf("Failed to open file : %s \n", argv[1]); // Check if input file opened correctly.
		return 0;
	}
	else {
		// Output Header Information
		printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s Tower\n",
			"FAA Site", "Short Name", "Airport Name", "City", "ST",
			"Latitude", "Longitude");
		printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s =====\n",
			"========", "==========", "============", "====", "==",
			"========", "=========");

		structMemory(airport); // Allocate memory to airport structure.

		// Read input file and trasnfer strings to structure members and junk variables.
		while (fgets(line, 1024, inputFile) != NULL) {
			char *storage = line, *newLine;

			newLine = strsep(&storage, ",");
			strcpy(airport->siteNumber, newLine);

			newLine = strsep(&storage, ",");
			strcpy(airport->LocID, newLine);

			newLine = strsep(&storage, ",");
			strcpy(airport->fieldName, newLine);

			newLine = strsep(&storage, ",");
			strcpy(airport->city, newLine);

			newLine = strsep(&storage, ",");
			strcpy(airport->state, newLine);

			newLine = strsep(&storage, ",");
			strcpy(junk0, newLine);

			newLine = strsep(&storage, ",");
			strcpy(junk1, newLine);

			newLine = strsep(&storage, ",");
			strcpy(junk2, newLine);

			newLine = strsep(&storage, ",");
			strcpy(airport->latitude, newLine);

			newLine = strsep(&storage, ",");
			strcpy(airport->longitude, newLine);

			newLine = strsep(&storage, ",");
			strcpy(junk3, newLine);

			newLine = strsep(&storage, ",");
			strcpy(junk4, newLine);

			newLine = strsep(&storage, ",");
			strcpy(junk5, newLine);

			newLine = strsep(&storage, ",");
			strcpy(junk6, newLine);

			newLine = strsep(&storage, ",");
			strcpy(controlTowerBuffer, newLine);

			airport->controlTower = *controlTowerBuffer; // Copy buffer data to structure member for airport controlTower.
			printData(airport); // Output data read.
		}
		// Free junk memory that was allocated.
		free(junk0);
		free(junk1);
		free(junk2);
		free(junk3);
		free(junk4);
		free(junk5);
		free(junk6);
		structDestroy(airport); // Free structure and members.
		fclose(inputFile); // Close input file.
	}
} // End main function.

// Begin structMemory function to allocate memory.
void structMemory(airPdata *aport) {
	aport->siteNumber = calloc(51, sizeof(char));
	aport->LocID = calloc(51, sizeof(char));
	aport->fieldName = calloc(51, sizeof(char));
	aport->city = calloc(51, sizeof(char));
	aport->state = calloc(51, sizeof(char));
	aport->latitude = calloc(51, sizeof(char));
	aport->longitude = calloc(51, sizeof(char));
}

// Begin printData function to output information.
void printData(airPdata *aport) {

	// Check if pointer is NULL before continuing and print to standard error.
	if (aport == NULL) {
		fprintf(stderr, "Pointer is NULL! Unable to output data! \n");
		exit(-1);
	}

	printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s %c\n", aport->siteNumber, aport->LocID, aport->fieldName,
		aport->city, aport->state, aport->latitude, aport->longitude, aport->controlTower);
}

// Begin structDestroy Function to clear memory allocation to the structure.
void structDestroy(airPdata *aport) {

	// Check if structure is NULL.
	if (aport == NULL) {
		exit(-1);
	}
	// Free structure members first.
	if (aport->siteNumber != NULL) {
		free(aport->siteNumber);
	}
	if (aport->LocID != NULL) {
		free(aport->LocID);
	}
	if (aport->fieldName != NULL) {
		free(aport->fieldName);
	}
	if (aport->city != NULL) {
		free(aport->city);
	}
	if (aport->state != NULL) {
		free(aport->state);
	}
	if (aport->latitude != NULL) {
		free(aport->latitude);
	}
	if (aport->longitude != NULL) {
		free(aport->longitude);
	}
	free(aport); // Free structure.
}
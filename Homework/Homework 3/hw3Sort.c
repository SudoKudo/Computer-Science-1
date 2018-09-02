/*
Course: COP 3502C - Computer Science 1
Assignment: Homework 3
Professor: Michael McAlpin
Date: 06/4/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// airPdata struct
typedef struct airPdata {
	char *LocID; //Airport’s ‘‘Short Name’’, ie MCO
	char *fieldName; //Airport Name
	char *city; //Associated City
	float longitude; //Longitude
	float latitude; //Latitude
} airPdata;

// Prototype functions
void parseLine(char *line, airPdata *apd);
void printData(int length, airPdata *apd);
void deleteStruct(airPdata *apd);
void sortByLocID(airPdata *airports);
void sortByLatitude(airPdata *airports);
float sexag2decimal(char *degreeString);

#define BUFFER_SIZE 500 // buffer size for memory allocation
unsigned int fileLength = 0; // Maintain file length for sorting functions
// Begin main function
int main(int argc, char *argv[]) {

	// Declare input buffer and other parameters
	FILE *fid;
	char buffer[BUFFER_SIZE], temp[2];
	unsigned int count = 0, i;

	// Check for command line input and open input file.
	if (argc == 3) {
		fid = fopen(argv[1], "r");
		if (fid == NULL) {
			printf("File %s failed to open. Aborting.\n", argv[1]);
			return 2;
		}
		strcpy(temp, argv[2]); // String copy to test case for sorting
		// Check if last argument for sorting is either a or n.
		if (!(temp[0] == 'A' || temp[0] == 'a' || temp[0] == 'n' || temp[0] == 'N')) {
			puts("hw3Sort ERROR: valid sort parameters are a or n.");
			return 3;
		}
	}
	else { // Error message for incorrect input parameters
		puts("Incorrect number of input parameters. Please specify the name of the input file only.");
		puts("Syntax: ./hw3Sort.c [input file] [sort paramaters 'a' or 'n']");
		return 1;
	}

	// Determine length of the file.
	while (fgets(buffer, BUFFER_SIZE, fid) != NULL) {
		count++;
		fileLength++;
	}
	rewind(fid);

	// Declare a struct array and allocate memory.
	airPdata *data;
	data = malloc(sizeof(airPdata)*count);
	// Test is memory allocation failed
	if (data == NULL) {
		printf("Memory allocation for airPdata array failed. Aborting.\n");
		return 2;
	}
	// Read and parse each line of the inputt file.
	for (i = 0; i < count; i++) {
		fgets(buffer, BUFFER_SIZE, fid);

		if (buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer) - 1] = '\0';

		parseLine(buffer, data + i);
	}
	// Close the input file.
	fclose(fid);
	// Perform sorting algorithm
	if (temp[0] == 'A' || temp[0] == 'a') {
		sortByLocID(data);
	}
	else {
		sortByLatitude(data);
	}
	// Output the data to stdout.
	printData(count, data);
	// Free the memory used for fields of the structs.
	for (i = 0; i < count; i++) {
		deleteStruct(data + i);
	}
	// Free the memory for the struct array.
	free(data);
	return 0;
} // End main function

// Begin parseLine function
void parseLine(char *line, airPdata *apd) {

	int i = 0, j = 0, commas = 0;
	char *longFloat, *latFloat;

	while (commas < 15) {
		while (*(line + i) != ',') {
			i++;
		}
		// strncpy does not append a '\0' to the end of the copied sub-string, so we will replace the comma with '\0'. 
		*(line + i) = '\0';

		switch (commas) {
		case 1:   //Grab the second "field" - Location ID
			apd->LocID = malloc(sizeof(char)*(i - j + 1));
			if (apd->LocID == NULL) {
				printf("malloc failed to initialize airPdata.LocID.\n");
				exit(-1);
			}
			strncpy(apd->LocID, line + j, i - j + 1);
			for (int x = 0; x < strlen(apd->LocID); x++) {
				apd->LocID[x] = toupper(apd->LocID[x]); // Convert to upper case for easier handling
			}
			// Check LocID for helipads and manage the deletion.
			if (   (apd->LocID[0] >= '0' && apd->LocID[0] <= '9')
				|| (apd->LocID[1] >= '0' && apd->LocID[1] <= '9')
				|| (apd->LocID[2] >= '0' && apd->LocID[2] <= '9') 
				|| (apd->LocID[3] >= '0' && apd->LocID[3] <= '9')  
				|| strlen(apd->LocID) < 3 
				|| strlen(apd->LocID) > 4 )
			{ 
				apd->longitude = -999;
				commas = 15;
			}
			break;
		case 2:   //Grab the third "field" - Field Name
			apd->fieldName = malloc(sizeof(char)*(i - j + 1));
			if (apd->fieldName == NULL) {
				printf("malloc failed to initialize airPdata.fieldName.\n");
				exit(-1);
			}
			strncpy(apd->fieldName, line + j, i - j + 1);
			break;
		case 3:   //Grab the fourth "field" - City
			apd->city = malloc(sizeof(char)*(i - j + 1));
			if (apd->city == NULL) {
				printf("malloc failed to initialize airPdata.city.\n");
				exit(-1);
			}
			strncpy(apd->city, line + j, i - j + 1);
			break;
		case 8:   //Grab the ninth "field" - Latitude (sexagesimal string)
			latFloat = malloc(sizeof(char)*(i - j + 1));
			if (latFloat == NULL) {
				printf("malloc failed to initialize airPdata.latitude.\n");
				exit(-1);
			}
			strncpy(latFloat, line + j, i - j + 1);
			apd->latitude = sexag2decimal(latFloat);
			free(latFloat);
			break;
		case 9:   //Grab the tenth "field" - Longitude (sexagesimal string)
			longFloat = malloc(sizeof(char)*(i - j + 1));
			if (longFloat == NULL) {
				printf("malloc failed to initialize airPdata.longitude.\n");
				exit(-1);
			}
			strncpy(longFloat, line + j, i - j + 1);
			apd->longitude = sexag2decimal(longFloat);
			free(longFloat);
			break;
		}
		j = ++i;
		commas++;
	}
} // End parseLine function

// Begin printData function
void printData(int length, airPdata *data) {
	puts("code,name,city,lat,lon");
	// For loop to output all data
	for (int i = 0; i < length; i++) {
		// Check for helipads. Discard output if it is a helipad
		if ((data + i)->longitude != -999) {
			printf("%s,%s,%s,%.4f,%.4f \n", (data + i)->LocID, (data + i)->fieldName,
				(data + i)->city, (data + i)->latitude, (data + i)->longitude);
		}
	}
} // End printData function

// Begin deleteStruct function
void deleteStruct(airPdata *apd) {
	free(apd->city);
	free(apd->fieldName);
	free(apd->LocID);
} // End deleteStruct function

// Begin sortByLocID function
void sortByLocID(airPdata *airports) {
	unsigned int i, j; // Counter variables
	//Start bubble sort
	for (i = 0; i < fileLength - 1; i++)
	{
		for (j = 0; j < fileLength - i - 1; j++)
		{	// Compare strings to sort alphabetically
			if (strcmp((airports + j)->LocID, (airports + j + 1)->LocID) > 0)
			{
				// Temp variables to hold for swapping
				char *tempCity;
				char *tempLoc;
				char *tempField;
				float tempLat, tempLong;
				// Swap each structure member so they align correctly when outputted
				tempLat = (airports + j)->latitude;
				(airports + j)->latitude = (airports + j + 1)->latitude;
				(airports + j + 1)->latitude = tempLat;

				tempLong = (airports + j)->longitude;
				(airports + j)->longitude = (airports + j + 1)->longitude;
				(airports + j + 1)->longitude = tempLong;

				tempCity = (airports + j)->city;
				(airports + j)->city = (airports + j + 1)->city;
				(airports + j + 1)->city = tempCity;

				tempField = (airports + j)->fieldName;
				(airports + j)->fieldName = (airports + j + 1)->fieldName;
				(airports + j + 1)->fieldName = tempField;

				tempLoc = (airports + j)->LocID;
				(airports + j)->LocID = (airports + j + 1)->LocID;
				(airports + j + 1)->LocID = tempLoc;
			}
		}
	}
} // End sortByLocID function

// Begin sortByLatitude function
void sortByLatitude(airPdata *airports) {
	unsigned int i, j; // Counter variables
	//Start bubble sort
	for (i = 0; i < fileLength - 1; i++)
	{
		for (j = 0; j < fileLength - i - 1; j++)
		{	// Compare structure members to sort by digits
			if ((airports + j)->latitude > (airports + j + 1)->latitude)
			{
				// Temp variables to hold for swapping
				char *tempCity;
				char *tempLoc;
				char *tempField;
				float tempLat, tempLong;
				// Swap each structure member so they align correctly when outputted
				tempLat = (airports + j)->latitude;
				(airports + j)->latitude = (airports + j + 1)->latitude;
				(airports + j + 1)->latitude = tempLat;

				tempLong = (airports + j)->longitude;
				(airports + j)->longitude = (airports + j + 1)->longitude;
				(airports + j + 1)->longitude = tempLong;

				tempCity = (airports + j)->city;
				(airports + j)->city = (airports + j + 1)->city;
				(airports + j + 1)->city = tempCity;

				tempField = (airports + j)->fieldName;
				(airports + j)->fieldName = (airports + j + 1)->fieldName;
				(airports + j + 1)->fieldName = tempField;

				tempLoc = (airports + j)->LocID;
				(airports + j)->LocID = (airports + j + 1)->LocID;
				(airports + j + 1)->LocID = tempLoc;
			}
		}

	}

} // End sortByLatitude function

// Begin sexag2decimal function
float sexag2decimal(char *degreeString) {
	unsigned int i; // Counter variable
	float degree, minute, second;
	char *temp;
	// Check if passed in paramater is NULL
	if (degreeString == NULL) {
		return 0.0;
	}
	// Parse string for degrees
	temp = strsep(&degreeString, "-");
	// Check if string contains bad degrees
	for (i = 0; i < strlen(temp); i++) {
		if (!(temp[i] >= '0' && temp[i] <= '9')) {
			return 0.0;
		}
	}
	degree = atof(temp); // Convert string to float variable
	// Check float variable parameters
	if (degree < 0.0 || degree > 180.0) {
		return 0.0;
	}
	// Parse string for minutes
	temp = strsep(&degreeString, "-");
	// Check if string contains bad minutes
	for (i = 0; i < strlen(temp); i++) {
		if (!(temp[i] >= '0' && temp[i] <= '9')) {
			return 0.0;
		}
	}
	minute = atof(temp); // Convert string to float variable
	// Check float variable parameters
	if (minute < 0.0 || minute > 59.0) {
		return 0.0;
	}
	else {
		minute /= 60.0; // Convert to proper minutes
	}
	// Parse string for seconds.arcseconds
	temp = strsep(&degreeString, "-");
	// Check if string contains bad seconds
	for (i = 0; i < strlen(temp - 1); i++) {
		if (!(temp[i] >= '0' && temp[i] <= '9')) {
			return 0.0;
		}
	}
	second = atof(temp); // Convert string to float variable
	// Check float variable parameters
	if (second < 0.0 || second > 59.9999) {
		return 0.0;
	}
	else {
		second /= (60.0*60.0); // Convert seconds to proper seconds
	}
	i = strlen(temp); // Temp variable to hold direction, if South or West, assign "-" to the degree decimal value
	if (temp[i - 1] == 'S' || temp[i - 1] == 'W') {
		degree *= -1;
	}
	return (degree + minute + second); // Return a degree decimal float value
} // End sexag2decimal function
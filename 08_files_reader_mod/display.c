// display.c
// Elton Chan 
// Nov 25th 2020

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "call.h"

#define NUM_OF_FUNC 2

void menu(void);
void printNaturalOrder(FILE* sfPtr, FILE* dfPtr);
void printBalanceDesc(FILE* sfPtr, FILE* dfPtr);

int main(int argc, char* argv[])
{	
	FILE* sfPtr;
	FILE* dfPtr;

	// a)
// check for the proper number of arguments
	if (argc != 3)
	{
		printf("\nRequire a source file name and a destination file name.\n");
		printf("\nProgram terminated. Press any key to exit.\n");
		_getch();
		return 1;
	}

	// b)
	// ensure that the dat file exists
	if ((sfPtr = fopen(argv[1], "rb")) == NULL)
	{
		printf("The dat file does not exist.\n");
		printf("Program terminated. Press any key to exit.\n");
		_getch();
		return 1;
	}
	
	// c)
	// ensure that the index file exists
	if ((dfPtr = fopen(argv[2], "rb")) == NULL)
	{
		printf("The index file does not exist.\n");
		printf("Program terminated. Press any key to exit.\n");
		_getch();
		return 1;
	}

	//define the function pointer
	void(*pfunc[NUM_OF_FUNC])(FILE * sfPtr, FILE * dfPtr);
	pfunc[0] = printNaturalOrder;
	pfunc[1] = printBalanceDesc;

	menu();
	unsigned int choice; 

	int timeToExit = 0;
	do {
		printf("%s", "? ");
		scanf("%u", &choice);
		switch (choice) {
			case 0:
				(*pfunc[choice])(sfPtr, dfPtr);
				break;
			case 1:
				(*pfunc[choice])(sfPtr, dfPtr);
				break;
			case 2:
				timeToExit = 1; // set to true to exit the program
				break;
			default:
				puts("Invalid choice.\n");
				break;
		}
	} while (!timeToExit);

	fclose(sfPtr);
	fclose(dfPtr);


	puts("End of the program.");
	_getch();
	return 0;
}

long fileSize(FILE* input)
{
	long orgPos;
	long startPos;
	long endPos;

	orgPos = ftell(input);          // save orig file position
	rewind(input);
	startPos = ftell(input);
	fseek(input, 0, SEEK_END);
	endPos = ftell(input);
	fseek(input, orgPos, SEEK_SET); // restore orig position

	return(endPos - startPos);
}

void menu(void)
{
	puts("Enter your choice:\n"
		"   0 to display the data in natural order.\n"
		"   1 to display the data in account balance descending.\n"
		"   2 to exit.\n"
	);
}

//function to display data in natural order
void printNaturalOrder(FILE* sfPtr, FILE* dfPtr)
{	
	ClientData client;
	printf("%-12s%-20s%-20s%10s%30s\n", "Account", "First Name", "Last Name", "Balance", "Last Payment Amount");
	fread(&client, sizeof(ClientData), 1, sfPtr);
	while ((!feof(sfPtr)))
	{
		// read data record and output
		printf("%-12d%-20s%-20s%10.2f%30.2f\n", client.account, client.firstName, client.lastName, client.balance, client.lastPymtAmt);
		fread(&client, sizeof(ClientData), 1, sfPtr);
	}
	rewind(sfPtr);
	printf("\n");
}

//function to display data in account balance descending order
void printBalanceDesc(FILE* sfPtr, FILE* dfPtr)
{	
	ClientData client;
	int		readCount;
	int		recCount;
	IndexHeader idxHeader;
	IndexRecord idxTemp;
	// calculate record count in data file
	recCount = fileSize(sfPtr) / sizeof(ClientData);

	// read header record in index file
	readCount = fread(&idxHeader, sizeof(IndexHeader), 1, dfPtr);

	readCount = fread(&idxTemp, sizeof(IndexRecord), 1, dfPtr);

	printf("%-12s%-20s%-20s%10s%30s\n", "Account", "First Name", "Last Name", "Balance", "Last Payment Amount");

	while ((!feof(sfPtr)) && (readCount == 1))
	{
		// seek record in data file based on file position
		//  stored in previously read index record
		if (fseek(sfPtr, idxTemp.filePos, SEEK_SET) != 0)
		{
			printf("Seek Error\n");
			return;
		}

		// read data record and output
		fread(&client, sizeof(ClientData), 1, sfPtr);
		printf("%-12d%-20s%-20s%10.2f%30.2f\n", client.account, client.firstName, client.lastName, client.balance, client.lastPymtAmt);
		// read next index record
		readCount = fread(&idxTemp, sizeof(IndexRecord), 1, dfPtr);
	}
	rewind(sfPtr);
	rewind(dfPtr);
	printf("\n");
}

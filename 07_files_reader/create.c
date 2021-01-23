// Elton Chan 
// Nov 14th 2020

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 512
#define NUM_OF_FIELDS 5
#define TRUE 1
#define FALSE 0

struct clientData
{
	int account;
	char firstName[30];
	char lastName[30];
	double balance;
	double lastPymtAmt;
};

typedef struct clientData ClientData;

int main(int argc, char *argv[])
{
	FILE* cfPtr;
	FILE* dfPtr;
	ClientData client;
	char line[MAX_LINE_LENGTH];
	char* remainderPtr;
	char proceed[] = "Yes";

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
	// ensure that the sourfile exists
	if ((cfPtr = fopen(argv[1], "rb")) == NULL)
	{
		printf("The source file does not exist.\n");
		printf("Program terminated. Press any key to exit.\n");
		_getch();
		return 1;
	}

	// c) d)
	// check for the existence of the destination file
	// if the file exists, ask for user response 
	if ((dfPtr = fopen(argv[2], "rb")) != NULL)
	{	
		printf("\n\'%s\' already exists. ", argv[2]);
		printf("Would you like to overwrite the existed file? (type 'Yes' to proceed) ");
		scanf("%s", &proceed);
		
		if(strcmp(proceed, "Yes") != 0 )
		{
			printf("\nProgram terminated. Press any key to exit.\n");
			_getch();
			return 1;
		}
	}

	// open the editable destination file 
	dfPtr = fopen(argv[2], "wb");

	while (!feof(cfPtr))
	{	
		// read line 
		fgets(line, MAX_LINE_LENGTH, cfPtr);
		// create token
		char* token = strtok(line, ",");
		// assign each string from the token to the appropriate field of the struct
		for (int i = 0; i < NUM_OF_FIELDS; ++i)
		{
			switch (i) 
			{
			case 0:
				client.account = strtod(token, &remainderPtr,0);
				break;

			case 1:
				strcpy(client.firstName,token);
				break;
			case 2:
				strcpy(client.lastName,token);
				break;
			case 3:
				client.balance = strtod(token, &remainderPtr, 0);
				break;
			case 4:
				client.lastPymtAmt = strtod(token, &remainderPtr, 0);
				break;

			default:
				break;
					
			}

			token = strtok(NULL, ",");
		}
		// check the client with assigned fields 
		//printf("%d %s %s %.2f %.2f\n", client.account, client.firstName, client.lastName, client.balance, client.lastPymtAmt);

		// write the current client to the dat file
		fwrite(&client, sizeof(struct clientData), 1, dfPtr);
	} 

	fclose(cfPtr);
	fclose(dfPtr);
	
	printf("\nSucessfullly copied the data from \'%s\' to \'%s\'", argv[1], argv[2]);
	printf("Press any key to exit.\n");
	_getch();
	return 0;
}
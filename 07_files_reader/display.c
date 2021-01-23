// Elton Chan 
// Nov 14th 2020

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>

struct clientData
{
	int account;
	char firstName[30];
	char lastName[30];
	double balance;
	double lastPymtAmt;
};

typedef struct clientData ClientData;

int main(void)
{
	FILE* dfPtr;
	ClientData client;


	if ((dfPtr = fopen("accounts.dat", "rb")) == NULL)
	{
		printf("The file could not be opened\n");
	}
	else
	{
		printf("Account\t\tFirst Name\t\tLast Name\t\t    Balance\t\tLast Payment Amount\n");
		// read the first client struct
		fread(&client, sizeof(struct clientData), 1, dfPtr);

		while (!feof(dfPtr))
		{	
			printf("%7d %18s %22s\t\t%11.2f\t\t%19.2f\n", client.account, client.firstName, client.lastName, client.balance, client.lastPymtAmt);
			// read the next client struct
			fread(&client, sizeof(struct clientData), 1, dfPtr);
		} 

		// close the file
		fclose(dfPtr);
	}

	puts("\nEND");

	_getch();
	return 0;
}

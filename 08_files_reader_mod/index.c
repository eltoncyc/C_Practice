// index.c
// Elton Chan
// Nov 25th 2020

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "call.h"

int compare(const void* left, const void* right); //used by qsort

int main(int argc, char* argv[])
{
	FILE* sfPtr;
	FILE* dfPtr;
	ClientData client;

	int	readCount;
	int	writeCount;
	int	dataRecordCount;
	int	indexRecordCount;
	long filePos;

	IndexHeader	indexHeader;
	IndexRecord* indexRecords;

	indexKey = BALANCE; // Account balance descending 

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
	if ((sfPtr = fopen(argv[1], "rb")) == NULL)
	{
		printf("The source file does not exist.\n");
		printf("Program terminated. Press any key to exit.\n");
		_getch();
		return 1;
	}

	// open index file for writing 
	if ((dfPtr = fopen(argv[2], "wb")) == NULL)
	{
		printf("Error - cannot open/create the index file.\n");
	}

	// calculate record count in data file
	dataRecordCount = fileSize(sfPtr) / sizeof(ClientData);

	// allocate an array to hold an equal number of index records 
	indexRecords = (IndexRecord*)calloc(dataRecordCount, sizeof(IndexRecord));

	// index header record
	indexHeader.idxKey = indexKey;
	indexHeader.recCount = dataRecordCount;

	rewind(sfPtr);
	filePos = ftell(sfPtr);
	indexRecordCount = 0;

	// Read first data record
	readCount = fread(&client, sizeof(struct clientData), 1, sfPtr);

	while (!feof(sfPtr) && (readCount == 1))
	{
		indexRecords[indexRecordCount].key.balance = client.balance;
		indexRecords[indexRecordCount].filePos = filePos;

		// added a record 
		indexRecordCount++;
		
		// store file position before next read 
		filePos = ftell(sfPtr);

		// read the next client struct
		readCount = fread(&client, sizeof(struct clientData), 1, sfPtr);

	}

	// sort array of index records in memory
	qsort(indexRecords, indexRecordCount, sizeof(IndexRecord), compare);
	printf("Index Header Size: %d\nIndex Record Size: %d\n\n", sizeof(IndexHeader), sizeof(IndexRecord));

	// write index header to file
	writeCount = fwrite(&indexHeader, sizeof(IndexHeader), 1, dfPtr);
	// write index records to file 
	writeCount = fwrite(indexRecords, sizeof(IndexRecord), indexRecordCount, dfPtr);

	//
	printf("%d Records Processed\n", writeCount);
	printf("The index file has been created.\n");

	// release the memory and set it free
	free(indexRecords);

	// close the files
	fclose(dfPtr);
	fclose(sfPtr);

	puts("End of the program.");
	_getch();
	return 0;
}

// calculates the size of a file
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

// function that qsort points to
int compare(const void* left, const void* right)
{
	// cast pointer parameters to IndexRecord
	IndexRecord* pLeft = (IndexRecord*)left;
	IndexRecord* pRight = (IndexRecord*)right;

	// sort by account balance descedning
	return pRight->key.balance - pLeft->key.balance;
}
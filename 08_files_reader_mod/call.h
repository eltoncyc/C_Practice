
#pragma once
typedef enum { ACCOUNT, FIRST, LAST, BALANCE, PAYMENT } IndexKey;

typedef union
{
	int account;
	char	firstName[30];
	char	lastName[30];
	double balance;
	double lastPymtAmt;
} KeyType;


struct clientData
{
	int account;
	char firstName[30];
	char lastName[30];
	double balance;
	double lastPymtAmt;
};

typedef struct
{
	KeyType		key;
	long		filePos;
} IndexRecord;

typedef struct
{
	IndexKey	idxKey;
	int			recCount;
} IndexHeader;

typedef struct clientData ClientData;

long fileSize(FILE* input); //computes file size

IndexKey indexKey;
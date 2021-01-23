// Assignment 3 Exercise 6.15
// Name: Elton Chan 
// Date: October 3, 2020

#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF_ARRAY 20 //maximum size of array

// prototypes of functions used in the program

// get a valid input 
int getInput(int lowValue, int highValue);

// check if the input is unique in the array which has the previously entered value(s); 
int isUnique(const int a[], int n, int value);

// define some global constants
const int LOWEST_VALUE_ELEMENT = 10;
const int HIGHEST_VALUE_ELEMENT = 100;
const int TRUE_VALUE = 1;
const int FALSE_VALUE = 0;
const int NUMBER_ELEMENTS_ROW = 5;

int main()
{	
	int input;
	int outputArray[SIZE_OF_ARRAY];
	int isUniqueValue;
	int outputCount = 0;

	for (unsigned i = 0; i < SIZE_OF_ARRAY; ++i)
	{	

		// get the ith input
		input = getInput(i ,LOWEST_VALUE_ELEMENT, HIGHEST_VALUE_ELEMENT);

		// check if the input is unique in the array
		isUniqueValue = isUnique(outputArray, i, input);

		// if the input is unique, add it to the array
		if (isUniqueValue == TRUE_VALUE)
		{
			outputArray[i] = input;
			printf("The number: %d is unique\n", input);
		}
	}

	// print all the unique and valid numbers in the output array 
	// if the reminder of the output count divided by 5 is 0, print it next row
	// therefore, only 5 numbers in each row 
	printf("\n\nAll of the unique numbers found are: \n");

	for (unsigned i = 0; i < SIZE_OF_ARRAY; ++i)
	{
		if (outputArray[i] >= LOWEST_VALUE_ELEMENT)
		{
			if (outputCount % NUMBER_ELEMENTS_ROW == 0)
			{
				printf("\n\t%d\t", outputArray[i]);
			}
			else {
				printf("%d\t", outputArray[i]);
			}
			++outputCount;
		}
	}

	// end of the program
	_getch();
	return 0;
}

//  Function continues to prompt for value until a valid value entered
//  The valid value is then returned.
//	index - index of the input
//  low - lowest value allowed
//  high - highest value allowed

int getInput(int index ,int low, int high)
{
	int value;
	printf("\nEnter # %d : ", index + 1);
	scanf("%d", &value);
	while (value < low || value > high)
	{
		printf("The number entered is not in the valid range of %d to %d\n", low, high);
		printf("\nEnter # %d : ", index + 1);
		scanf("%d", &value);
	}

	return value;
}

// function to check if a value is unique in the given array
// a[] - input array 
// n - number of unique and valid values in the given array to early stop the loop
// value - value to be checked 
// return 1 if is unqiue else 0

int isUnique(const int a[], int n, int value)
{
	int output = TRUE_VALUE;
	for (unsigned int i = 0; i < n; ++i) 
	{	
		if (a[i] == value) {
			output = FALSE_VALUE;
		}
	}

	return output;
}
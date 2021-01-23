// Exercise 3.16
// Name: Elton Chan
// Date: September 20, 2020

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

const float EXIT_VALUE = -1.0f;

int main(void)
{
	float totalMiles = 0; //total miles driven
	float totalGallons = 0; //total gallon used
	float theMiles; //one recorded miles
	float theGallons; //one recorded gallon
	float ratio; //ratio of miles to gallon
	float finalRatio; // overall average ratio of miles to gallon

	//record the first gallons used
	printf("%s%.1f%s", "Enter the gallons used ( ", EXIT_VALUE, " to end ): ");
	scanf("%f", &theGallons);
	//validate the gallons input
	while (theGallons <= 0 && theGallons!=EXIT_VALUE) {
		printf("%s", "You have entered an invalid value for gallons, try again: ");
		scanf("%f", &theGallons);
	}
	
	// loop until exit value entered
	while (theGallons != EXIT_VALUE) {
		
		//record the first miles driven
		printf("%s", "Enter the miles driven: ");
		scanf("%f", &theMiles);

		//validate the miles input
		while (theMiles <= 0) {
			printf("%s", "You have enter an invalid value for miles, try again: ");
			scanf("%f", &theMiles);
		}

		//calculate the ratio 
		ratio = theMiles / theGallons;
		totalGallons += theGallons;
		totalMiles += theMiles;
		
		//display the ratio of miles to gallon
		printf("%s%.6f\n\n", "The miles/gallon for this tank was ",ratio);

		//record the next gallons used
		printf("%s%.1f%s", "Enter the gallons used ( ", EXIT_VALUE, " to end ): ");
		scanf("%f", &theGallons);

		//validate the gallons input
		while (theGallons <= 0 && theGallons != EXIT_VALUE) {
			printf("%s", "You have entered an invalid value for gallons, try again: ");
			scanf("%f", &theGallons);
		}

	} // end while

	// prompt the overal average ratio
	if (totalMiles == 0 || totalGallons == 0) {
		printf("%s", "The overall average miles could not be computed :(");
	}
	else {
		finalRatio = totalMiles / totalGallons;
		printf("\n%s%.6f", "The overall average miles/gallon was ", finalRatio);
	}

	// end program
	puts("\n\npress any key to exit");
	_getch();
	return 0;
} // end main
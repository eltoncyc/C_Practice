// Modified by: Elton Chan 
// Date: September 27, 2020

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>   // needed for the printf and scanf statements
#include <math.h>    // needed for abs() library function
#include <conio.h>   // needed for _getch() call at end of main()
					 // You may remove this last #include if your compiler does not support it

// Function prototypes (I have provided first, you need to provide the 2nd prototype)
long getInput(long lowValue, long highValue);
long SecondsSinceMidnight(long hour, long minute, long second);

/* The main program performs all input and output in this application.
   It also computes the "difference in seconds" between the 2 input
   times.
*/

#define SECONDS_IN_A_MINUTE 60
#define SECONDS_IN_A_HOUR 3600

int main()
{

	// Initialize 
	
	long hour,     // used to store hour value input from user
	     minute,   // used to store minute value input from user
	     second,   // used to store second value input from user

	     secs1,      // used to store output from function call for first input time
		 secs2,      // used to store output from function call for second input time

		 diff_in_secs; // used to store calculated difference in seconds;

   // Get inputs for the first time
   printf("Enter the first hour value (0-23): ");
   hour = getInput(0, 23);
   // Student provides remainder of solution here ...
   printf("\nEnter the first minute value (0-59): ");
   minute = getInput(0, 59);

   printf("\nEnter the first second value (0-59): ");
   second = getInput(0, 59);

   secs1 = SecondsSinceMidnight(hour, minute, second);

   // Get inputs for the second time
   printf("\nEnter the second hour value (0-23): ");
   hour = getInput(0, 23);

   printf("\nEnter the second minute value (0-59): ");
   minute = getInput(0, 59);

   printf("\nEnter the second second value (0-59): ");
   second = getInput(0, 59);

   secs2 = SecondsSinceMidnight(hour, minute, second);

   // calculate the difference in seconds 
   
   diff_in_secs = abs(secs2 - secs1);

   printf("\nThe first input time converted into second is : %d", secs1);
   printf("\nThe second input time converted into second is : %d", secs2);
   printf("\n\nThe difference in seconds between the two input times is: %d", diff_in_secs);
   // Time to go home

   _getch(); // you may comment out this function call if your compiler does not support it
   return 0;
}

//  Function continues to prompt for value until a valid value entered
//  The valid value is then returned.

//  low - lowest value allowed
//  high - highest value allowed

long getInput(long low, long high)
{
	long input; 
	// Student provides implementation of this function
	scanf("%d", &input);
	while (input < low || input > high) {
		printf("Invalid value entered, enter valid value between %d and %d: ", low, high);
		scanf("%d", &input);
	}
	return input;
}

// Function to return the number of seconds since the last time the clock "struck 12"
// parameter: long hours, long minutes, long seconds 
// return: long numberOfSeconds

long SecondsSinceMidnight(long hour, long minute, long second) 
{	
	long numberOfSeconds;
	numberOfSeconds = (hour * SECONDS_IN_A_HOUR) + (minute * SECONDS_IN_A_MINUTE) + second;
	return numberOfSeconds;
}




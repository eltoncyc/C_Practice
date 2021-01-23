// Elton Chan 
// Date: Oct 18, 2020

#define _CRT_SECURE_NO_WARNINGS

/*  This application processes an array of commands which causes turtle to draw
    a pattern on a 2D floor.  This pattern is diplayed after commands have been executed */

#include <stdio.h>   // needed for the printf and scanf statements
#include <conio.h>   // needed for _getch() call at end of main()

// function prototypes
void turtleDraw(const int[]); // main function responsible for executing cmds

// main supplies data to be passed to turtleDraw() function
int main()
{

	int commands[] = { 5, 5, 4, 5, 9, 2,   // go to start of first letter and put pen down

		// B
		5, 12, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 2, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 11, 3, 5, 5,
		1, 3, 5, 12, 3, 5, 5, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 2, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 11, 3, 5, 5,

		1, 5, 5, 3, 5, 22, 2, // go to start of next letter and put pen down

		// O
		5, 10, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 7, 1, 3, 5, 1, 4, 2, 5, 1,
		1, 3, 5, 1, 2, 5, 10, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 7, 1, 3, 5, 1, 4, 2, 5, 1,

		1, 3, 5, 19, 2,     // go to start of next letter and put pen down

		// B
		5, 12, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 2, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 11, 3, 5, 5,
		1, 3, 5, 12, 3, 5, 5, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 2, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 11, 3, 5, 5,

		// Test program bound checking and add border in the process

		//   Uncomment next line when ready to test out of bounds checking
		1, 5, 100, 2, 4, 5, 100, 4, 5, 100, 4, 5, 100, 4, 5, 100, 4, 5, 100,

		1, 6, 9 }; // finish off


	// Invoke function which will execute commands
	turtleDraw(commands);

	// Time to go home

	_getch();
	return 0;
}

// define 2 enum types
enum TCmnds { PEN_UP = 1, PEN_DWN = 2, TURN_RIGHT = 3, TURN_LEFT = 4, MOVE = 5, DISPLAY = 6, END_OF_DATA = 9 };
enum Dirs { BEGIN_VALUE, NORTH, EAST, SOUTH, WEST, END_VALUE };

#define NROWS 22 // number of rows in floor
#define NCOLS 70 // number of colums in floor
#define TRUE 1
#define FALSE 0
#define MAX_ROW_IDX 21
#define MAX_COL_IDX 69

const unsigned int STARTING_ROW = 0;    // row that turtle will start in
const unsigned int STARTING_COL = 0;    // column that turtle will start in

const enum TCmnds STARTING_DIRECTION = SOUTH; // direction that turtle 
                                              // will be facing at the start

const short STARTING_PEN_POSITION = FALSE; // Pen will be up when 
                                       //     program starts
                                       // 0 (false) means pen up, 
                                       // 1 (true) means pen down

// some more function prototypes
void displayFloor(const short[][NCOLS]);
void moveTurtle(short [][NCOLS], const int, const enum Dirs, const short, int *, int *);

// turtleDraw() - function responsible for executing commands
void turtleDraw(const int cmds[])
{
	// Define and initialize some important variiables

	// The 2D array floor will represent the surface that the turtle is travelling
	//      over and there by creating the pattern we will eventually print out.
	short floor[NROWS][NCOLS] = { FALSE };  //init to all FALSE (0).
	enum Dirs direction = STARTING_DIRECTION; // used to represent current direction that the turtle is moving
	                                      
	unsigned int row = STARTING_ROW;  // used to represent current row that turtle is at
	unsigned int col = STARTING_COL;  // used to represent current column that turtle is at

	short pen = STARTING_PEN_POSITION; // starting position of pen (up or down)
	                                   // 0 is up, 1 is down
	int cmdNo = 0; // The position in cmds array we are currently processing

	// The following do-while loop is the main loop of this program
	// We will stay in this loop as long as we are processing commands from the cmds[] array

	do {  // until END_OF_DATA is encountered

		switch (cmds[cmdNo]) {  // Switch statment that processes commands
		case PEN_UP: // Pen up
			pen = FALSE;
			break;

		case PEN_DWN: // Pen down

			// STUDENT PROVIDES THIS CODE
			pen = TRUE;
			break;

		case TURN_RIGHT: // Turn right
			++direction; // for example, change from NORTH to EAST
			if (direction >= END_VALUE )   // in case we turn right when facing WEST
			{
				direction = NORTH;
			}
			break;

		case TURN_LEFT: // Turn left

			// STUDENT PROVIDES THIS CODE
			--direction;
			if (direction <= BEGIN_VALUE) // turn left to west when facing north
			{
				direction = WEST;
			}
			break;

		case MOVE: // Move forward 
			++cmdNo;  // move to next command in the command array
			          //   we need next value to know how many spaces to move
			       
			// We pass pointers to row and col below so that when we update in moveTurtle()
			//    they are updated here in turtleDraw() as well.
			moveTurtle(floor,  cmds[cmdNo], direction, pen, &row, &col); // move turtle as required
			                                                             //  and update floor as req.
			//printf("row: %d; col: %d\n", row, col); //check the current position
			break; // end of case MOVE:

		case DISPLAY: // display the floor matrix
			displayFloor(floor);
			break;

		case END_OF_DATA: // end of data reached
			break; // no action required, will exit do-while loop automatically

		default: // should never get here !!!
			puts("\n\nERROR - invalid command encountered in"
				" turtleDraw() switch statement.\n\n");
			return;  // major error, so go home

		} // end of switch statment

		++cmdNo;   // move to next command

	} while (cmds[cmdNo] != END_OF_DATA); // repeat until end of data is reached

}

// moveTurtle() - responsible for moving the turtle on the floor and modifying floor if pen is down.
// This function is passed pointers to row and col because they need to be passed by reference
//      because this function must update the row and col when moving turtle. Note that 
//      floor is also passed by reference, but because an arry name is a pointer, the array
//      is automatically passed by reference.
void moveTurtle(short floor [][NCOLS], const int numOfMoves, const enum Dirs currDir, const short penPos, int * rowPtr, int * colPtr)
{
	
	// STUDENT PROVIDES THIS CODE
	switch (currDir) {
	case SOUTH:
		for (int i = 0; i < numOfMoves; ++i) 
		{
			if (*rowPtr < NROWS)
			{
				if (penPos == TRUE)
				{
					floor[*rowPtr][*colPtr] = TRUE;
				}
				if (*rowPtr  < MAX_ROW_IDX) //move to the next row if the current position is not at the maximum row index 
				{
					++* rowPtr;
				}	
			}
			else {
				break; // exit loop immediately when reaching the edge
			}
		}
		break;

	case NORTH:
		for (int i = 0; i < numOfMoves; ++i)
		{	
			if(*rowPtr >= 0)
			{
				if (penPos == TRUE)
				{
					floor[*rowPtr][*colPtr] = TRUE;
				}
				if (*rowPtr  > STARTING_ROW) //move to the upper row if the current position is not at the starting row
				{
					--* rowPtr;
				}	
			}
			else {
				break; // exit loop immediately when reaching the edge
			}
		}
		break;

	case EAST:
		for (int i = 0; i < numOfMoves; ++i)
		{	
			if(*colPtr < NCOLS)
			{
				if (penPos == TRUE)
				{
					floor[*rowPtr][*colPtr] = TRUE;
				}
				if (*colPtr < MAX_COL_IDX) //move to the right column if the current position is not at the maximum col index
				{
					++* colPtr;
				}
			}
			else {
				break; // exit loop immediately when reaching the edge
			}
		}
		break;

	case WEST:
		for (int i = 0; i < numOfMoves; ++i)
		{	
			if (*colPtr >= 0)
			{
				if (penPos == TRUE)
				{
					floor[*rowPtr][*colPtr] = TRUE;
				}
				if (*colPtr > STARTING_COL) //move to the left column if the current position is not at the starting column
				{
					--* colPtr;
				}	
			}
			else {
				break; // exit loop immediately when reaching the edge
			}
		}
		break;

	default: // should never get here !!!
		puts("\n\nERROR - invalid command encountered in"
			" moveTurtle() switch statement.\n\n");
		return;

	}

}// end of moveTurtle()

// Responsible for displaying the floor
void displayFloor(const short floorSurface[][NCOLS])
{
	
	// STUDENT PROVIDES THIS CODE
	// Looping through the 2D Array, if an element of the array is true, print "*" else " "
	for (int i = 0; i < NROWS; ++i)
	{
		for (int j = 0; j < NCOLS; j++)
		{
			if (floorSurface[i][j] == TRUE)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
} // end of displayFloor()
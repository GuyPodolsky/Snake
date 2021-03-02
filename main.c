/*
 * Made by Guy Podolsky, I.D.number: 206799199.
 * This is a "Snake" game, At the start, there is a single snake part that moves right until the player (user)
 * changes the movement direction of the snake by pressing on one of the following control keys:
 *	- 'a' to move left.
 *	- 'd' to move right.
 *	- 'w' to move up.
 *	- 's' to move down.
 *	
 * The goal is to keep the snake a life by avoiding collision with the game's borders and with the snake's body.
 * 
 * Note: The snake grows and moves faster every five moves.
 *
 * Wish you good luck ;-)
 */

/////////////////////////////////////// Header ///////////////////////////////////////

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//////////////////////////////////// End Of Header ///////////////////////////////////


/////////////////////////// Const Variables and Definitions //////////////////////////

#define OUT_OF_BOARD 26,1
#define NUMBER_OF_COLUMNS 75
#define NUMBER_OF_ROWS 25
#define SPACE " "
#define NEXT_LINE "\n"
#define SNAKE_PART "%c",'@'
#define MIDDLE_OF_Y 37
#define MIDDLE_OF_x 12
#define MAX_SPEED 0.1
#define	ACCELERATION 0.01
#define isAFifthMove (numOfMoves % 5 == 0)
#define LEFT 'a'
#define RIGHT 'd'
#define UP 'w'
#define DOWN 's'

/////////////////////// End Of Const Variables and Definitions ///////////////////////


///////////////////////////////// Node declaration ///////////////////////////////////

typedef struct snake		
{
	int row;
	int col;
	struct snake* next;
}SNAKE;

///////////////////////////// End of Node declaration ////////////////////////////////


////////////////////////// Built-In Functions Declaration ////////////////////////////

void init(void);
	//clears the console.

void gotoxy(int x, int y);
	// Moves the cursor to position (row,col) on screen.
	// Parameters:
	//     row: the row of the position.
	//     col: the col of the position.

 
void sleep(float secs);
	// Delays the execution of the program.
	// Parameters:
	//		secs: the length of the delay in seconds.

////////////////////// End Of Built-In Functions Declaration /////////////////////////


////////////////////////////// Functions Declaration /////////////////////////////////

void printBorders();
	// Prints out the borders of the game

void createSnake(SNAKE* snk);
	// Creates the first node that represents a snake part and prints out the snake.
	// Parameters:
	//		snk: a pointer that contains the address to the snake.
		
void gameOver(SNAKE* snk);
	// Clears the snake from the screen and prints out "GAME OVER".
	// Parameters:
	//		snk: a pointer that contains the address to the snake.
	
void getValidChar(char* direction);
	// Makes sure the user inserts only valid inputs.
	// Parameters:
	//		direction: a pointer that contains the address to a char variable that stores a character
	//				   that represents the direction that the user choosing.

bool moveSnake(SNAKE* snk, SNAKE* snkHead, char direction, int numOfMoves);
	// Makes the snake move to the direction that the user choose.
	// Parameters:
	//		snk: a pointer that contains the address to the snake.
	//		snkHead: a pointer that contains the address to the snake's head.
	//		direction: a character that represents the movement direction of the snake.
	//		numOfMoves: an integer that represents the number of moves the snake has made

bool snakeMoveR(SNAKE* snk, SNAKE* snkHead);
	// Makes the snake move right.
	// Parameters:
	//		snk: a pointer that contains the address to the snake.
	//		snkHead: a pointer that contains the address to the snake's head.

bool snakeMoveL(SNAKE* snk, SNAKE* snkHead);
	// Makes the snake move left.
	// Parameters:
	//		snk: a pointer that contains the address to the snake.
	//		snkHead: a pointer that contains the address to the snake's head.

bool snakeMoveU(SNAKE* snk, SNAKE* snkHead);
	// Makes the snake move up.
	// Parameters:
	//		snk: a pointer that contains the address to the snake.
	//		snkHead: a pointer that contains the address to the snake's head.

bool snakeMoveD(SNAKE* snk, SNAKE* snkHead);
	// Makes the snake move down.
	// Parameters:
	//		snk: a pointer that contains the address to the snake.
	//		snkHead: a pointer that contains the address to the snake's head.

bool isTouchedBorder(int headRow, int headCol);
	// Checks whether  the snake's head touched one of the borders.
	// Parameters:
	//		headRow: an integer that represents the row number of the snake's head location.
	//		headCol: an integer that represents the column number of the snake's head location.

bool isTouchedHimself(SNAKE* snk, SNAKE* snkHead, char direction);
	// Checks whether the snake's head touched his body.
	// Parameters:
	//		snk: a pointer that contains the address to the snake.
	//		snkHead: a pointer that contains the address to the snake's head.
	//		direction: a character that represents the movement direction of the snake

SNAKE* addSnakePart(SNAKE* snk);
	// Adds another snake's part to the snake.
	// Parameters:
	//		snk: a pointer that contains the address to the snake.

void freeSnake(SNAKE* snk);
	// Frees the memory that stores the snake's parts.
	// Parameters:
	//		snk: a pointer that contains the address to the snake.

////////////////////////// End Of Functions Declaration //////////////////////////////


////////////////////////////////////// Main //////////////////////////////////////////

int main()
{
	int numOfMoves;												//variables declaration							
	float speed;
	char direction;
	bool isGameOver;
	SNAKE* snk;
	SNAKE* snkHead;

	numOfMoves = 0;												//variables initialization
	speed = 1;
	direction = 'd';
	isGameOver = false;
	snk = (SNAKE*)malloc(sizeof(SNAKE));

	init();														//clears the console
	printBorders();												//print out the borders
	createSnake(snk);											//creates a snake
	snkHead = snk;												//keeps the address to the head of
																//the snake in a pointer

	while (!isGameOver)											//looping until the player lose
	{
		sleep(speed);												//makes a delay in the program's run time
																	//that creates a movement speed effect of the snake
		numOfMoves++;												
		if (isAFifthMove)											//checks if this is the fifth step
		{
			if (speed >= MAX_SPEED)										//if the speed hasn't reached to the speed limit
				speed -= ((float)ACCELERATION);								//rises the speed
			snk = addSnakePart(snk);									//adds another snake part to the snake
		}//end of if
		if (_kbhit())												//if the user typed a key
			getValidChar(&direction);									//saves only valid input that represents the
																		//snake's movement direction
		isGameOver = moveSnake(snk, snkHead, direction,numOfMoves);	//checks if the user lost
		if (isGameOver)												//if the user lost
			gameOver(snk);												//clears the snake from the screen and prints
																		//out "GAME OVER!"
	}//end of while
	freeSnake(snk);												//frees the memory that stores the snake's parts
	gotoxy(OUT_OF_BOARD);										//moves out of the border
	system("pause");											//keeps the console open when the program ends
}

////////////////////////////////// End Of Main ///////////////////////////////////////


///////////////////////// Built-In Functions implementation //////////////////////////

void init(void)
{
	system("cls"); //clears the console
}//edn of init

void gotoxy(int x, int y)
{
	printf("\x1b[%d;%df", x, y);
}//end of gotoxy

void sleep(float secs)
{
	clock_t clocks_start = clock();
	while (clock() - clocks_start < secs * CLOCKS_PER_SEC);
}//end of sleep

////////////////////// End Of Built-In Functions Implementation //////////////////////


///////////////////////////// Functions Implementation ///////////////////////////////

void printBorders()
{
	int x, y;											//variable declaration
	for (y = 1; y <= NUMBER_OF_ROWS; y++)						//looping until it prints out all the rows.
	{
		for (x = 1; x <= NUMBER_OF_COLUMNS; x++)			//looping until it prints out all the columns in this row.
		{
			if (y == 1 || y == NUMBER_OF_ROWS)					//if this is the first or the last row
				printf("#");
			else if (x == 1 || x == NUMBER_OF_COLUMNS)			//not the first or the last row but it is the first or the last col
				printf("#");
			else												//not the first or the last row/col
				printf(SPACE);
		}//end of for row
		printf(NEXT_LINE);								//moves to the next line.
	}//end of for col
}

void createSnake(SNAKE* snk)
{
	snk->col = MIDDLE_OF_Y;		//sets the snake in the middle
	snk->row = MIDDLE_OF_x;
	snk->next = NULL;			//initalizes the pointer to the next snake part
	gotoxy(snk->row, snk->col); //prints out the snake
	printf(SNAKE_PART);
}//end of createSnake

void gameOver(SNAKE* snk)
{
	if (snk->next == NULL)							//the simple case: when this is the last part
													//of the snake (his head);
	{
		if (!isTouchedBorder(snk->row, snk->col))		//if the head of the snake isn't placed in the border  
		{
			gotoxy(snk->row, snk->col);						//clears the the head of the snake from the screen
			printf(SPACE);
		}//end of the second if
		gotoxy(MIDDLE_OF_x, MIDDLE_OF_Y - 3);			//prints out "GAME OVER" in the middle of the screen
		printf("GAME OVER!");
	}//end of the first if
	else											//when this isn't the last part of the snake
	{
		gameOver(snk->next);							//removes the rest of the snake
		gotoxy(snk->row, snk->col);						//removes the current snake part
		printf(SPACE);
	}//end of else
}//end of gameOver

void getValidChar(char* direction)
{
	char input;															//variable declaration
	input = _getch();													//gets an input of a character
	if (input == 'a' || input == 'd' || input == 'w' || input == 's')	//check if is it a valid input of a character
		*direction = input;													//saves the input into direction variable
																			//through a pointer 
}//end of getValidChar

bool moveSnake(SNAKE* snk, SNAKE* snkHead, char direction, int numOfMoves)
{
	bool isTB = false;								//variable declaration and initialization
													//(isTB = "is touched the border")
	if (isTouchedHimself(snk, snkHead, direction))	//checks if the snake has touched himself
		return true;								
	if (!isAFifthMove)							//checks that this is not the fifth step
													//it does so because every five steps the snake grows
													//and by avoiding those commands  the movement of the
													//snake is looks more natural
	{
		gotoxy(snk->row, snk->col);						//removes the snake's tile
		printf(SPACE);
	}//end of if
	switch (direction)								//checks to which direction the snake moves
	{
		case RIGHT:										//if the snake moves right		
			isTB = snakeMoveR(snk,snkHead);					//moves the snake one step right
			break;
		case LEFT:										//if the snake moves left
			isTB = snakeMoveL(snk,snkHead);					//moves the snake one step left
			break;	
		case UP:										//if the snake moves up
			isTB = snakeMoveU(snk,snkHead);					//moves the snake one step up
			break;
		case DOWN:										//if the snake moves down
			isTB = snakeMoveD(snk,snkHead);					//moves the snake one step down
			break;
	};//end of switch
	gotoxy(OUT_OF_BOARD);							//moves out of the board, the sign that shows the writing position in the text
	return isTB;									//returns rather the last move caused the snake to touch the border	
}//end of moveSnake

bool snakeMoveR(SNAKE* snk, SNAKE* snkHead)
{
	if (snk->next == NULL)									//the simple case: when this is the last part
															//of the snake (his head);
	{
		snk->col++;												//moves the snake's head right
		if (isTouchedBorder(snkHead->row, snkHead->col))		//if the snake's head has touched the border
			return true;											
		else													//if the snake's head hasn't touched the border 
		{
			gotoxy(snk->row, snk->col);								//prints the snake's head at the new position
			printf(SNAKE_PART);										
			return false;
		}//end of else
	}//end of if
	else													//when this isn't the last part of the snake
	{
		snk->row = snk->next->row;								//moves the reset of the snake
		snk->col = snk->next->col;
		return snakeMoveR(snk->next, snkHead);				
	}//end of else
}//end of snakeMoveR

bool snakeMoveL(SNAKE* snk, SNAKE* snkHead)
{
	if (snk->next == NULL)										//the simple case: when this is the last part
																//of the snake (his head);
	{
		snk->col--;													//moves the snake's head left
		if (isTouchedBorder(snkHead->row, snkHead->col))			//if the snake's head has touched the border
			return true;
		else														//if the snake's head hasn't touched the border
		{										
			gotoxy(snk->row, snk->col);									//prints the snake's head at the new position
			printf(SNAKE_PART);
			return false;
		}//end of else
	}//end of if
	else 														//when this isn't the last part of the snake
	{
		snk->row = snk->next->row;									//moves the reset of the snake
		snk->col = snk->next->col;
		return snakeMoveL(snk->next, snkHead);
	}//end of else
}//end of snakeMoveL

bool snakeMoveU(SNAKE* snk, SNAKE* snkHead)
{
	if (snk->next == NULL)										//the simple case: when this is the last part
																//of the snake (his head);
	{
		snk->row--;													//moves the snake's head up
		if (isTouchedBorder(snkHead->row, snkHead->col))			//if the snake's head has touched the border
			return true;
		else														//if the snake's head hasn't touched the border				 
		{
			gotoxy(snk->row, snk->col);									//prints the snake's head at the new position
			printf(SNAKE_PART);
			return false;
		}//end of else
	}//end of if
	else 														//when this isn't the last part of the snake
	{
		snk->row = snk->next->row;									//moves the reset of the snake
		snk->col = snk->next->col;
		return snakeMoveU(snk->next, snkHead);
	}//end of else
}//end of snakeMoveU

bool snakeMoveD(SNAKE* snk, SNAKE* snkHead)
{
	if (snk->next == NULL)										//the simple case: when this is the last part
																//of the snake (his head);
	{
		snk->row++;													//moves the snake's head down
		if (isTouchedBorder(snkHead->row, snkHead->col))			//if the snake's head has touched the border
			return true;
		else														//if the snake's head hasn't touched the border
		{
			gotoxy(snk->row, snk->col);									//prints the snake's head at the new position
			printf(SNAKE_PART);
			return false;
		}//end of else
	}//end of if
	else														//when this isn't the last part of the snake
	{
		snk->row = snk->next->row;									//moves the reset of the snake
		snk->col = snk->next->col;
		return snakeMoveD(snk->next, snkHead);
	}//end of else
}//end of snakeMoveD

bool isTouchedBorder(int headRow, int headCol)
{
	int topOrLeftBorder, bottomBorder, rightBorder;						//variables declaration
	topOrLeftBorder = 1;												//variables initialization
	bottomBorder = NUMBER_OF_ROWS;
	rightBorder = NUMBER_OF_COLUMNS;
	
	if ((headCol) == topOrLeftBorder || (headCol) == rightBorder)		//checks if the snake's head has touched the
																		//left border or the right border
		return true;
	else if ((headRow) == topOrLeftBorder || (headRow) == bottomBorder)	//checks if the snake's head has touched the 
																		//top border or the bottom border
		return true;
	else 																//if the snake's head hasn't touched a border
		return false;
}//end of isTouchedBorder

bool isTouchedHimself(SNAKE* snk, SNAKE* snkHead, char direction)
{
	if (snk->next==NULL)												//the simple case: when this is the last part
																		//of the snake (his head); 
	{
		return false;
	}//end of if
	else																//when this isn't the last part of the snake
	{	
		switch (direction)													//checks to which direction the snake moves
		{
			case RIGHT:															//if the snake moves right	
				if ((snkHead->row == snk->row) && (snkHead->col + 1 == snk->col))	//checks if the move causes the snake to
																					//touch himself
					return true;
				break;
			case LEFT:															//if the snake moves left	
				if ((snkHead->row == snk->row) && (snkHead->col - 1 == snk->col))	//checks if the move causes the snake to
																					//touch himself
					return true;
				break;
			case UP:															//if the snake moves up	
				if ((snkHead->row - 1 == snk->row) && (snkHead->col == snk->col))	//checks if the move causes the snake to
																					//touch himself
					return true;
				break;
			case DOWN:															//if the snake moves down	
				if ((snkHead->row + 1 == snk->row) && (snkHead->col == snk->col))	//checks if the move causes the snake to
																					//touch himself
					return true;
				break;
		};//end of switch
		return isTouchedHimself(snk->next, snkHead, direction); //checks if the move causes the snake to touch the rest of the snake's parts
	}//end of else
}//end of isTouchedHimself

SNAKE* addSnakePart(SNAKE* snk)
{
	SNAKE* snkPart = NULL;						//creates a new snake node
	snkPart = (SNAKE*)malloc(sizeof(SNAKE));	//assigns memory for the new snake node
	snkPart->col = snk->col;					//equalizes the values between the new node and the existing node
	snkPart->row = snk->row;					
	snkPart->next = snk;						//makes the new node as the first node in the chain of nodes
	return snkPart;								//returns the new chain
}//end of addSnakePart

void freeSnake(SNAKE* snk)
{
	if (snk->next == NULL)		//the simple case: when this is the last part
								//of the snake (his head); 
		free(snk);					//frees the memory the contains the last part
	else						//when this isn't the last part of the snake
	{
		freeSnake(snk->next);		//frees the memory that contains the rest of the snake's parts
		free(snk);					//frees the memory that contains the current snake part
	}//end of else
}//end of freeSnake

////////////////////////// End Of Functions Implementation ///////////////////////////

// A C++ Program to Implement and Play Minesweeper 

#include <iostream> 
#include <time.h>
using namespace std; 

#define BEGINNER 0 
#define INTERMEDIATE 1 
#define ADVANCED 2 
#define CUSTOM 3 
#define AUTOSOLVE 4 
#define FIXEDLEVEL 5
#define MAXSIDE 25 
#define MAXMINES 99 
#define MOVESIZE 526 // (25 * 25 - 99) 

bool autosolve = false; // if it is a auto level
bool automovesolve = false;
int automoves = 0;
bool savemode = false;
int SIDE ; // side length of the board 
int MINES ; // number of mines on the board 

int AutomovesY[200] = {0,0,0,1,1,0,0,2,4,6,8,3,1,3,5,8,8,3,1,2,3,2,2,6,7,0,8,1,3,4,5,5,5,4,1,2,3,0,3,5,0,4,5,1,3,5,6,4};
int AutomovesX[200] = {5,3,0,1,2,3,8,7,8,4,1,3,1,2,0,8,3,5,0,0,0,1,3,3,3,4,4,4,4,4,4,1,2,6,5,5,5,6,6,6,7,7,7,8,8,8,8,5};

int AutominesY[20] = {8,5,6,2,1,2,3,8,1,5,6,7,2,3,1,4,0,2,6,0};
int AutominesX[20] = {0,5,7,8,3,6,1,2,7,3,6,4,2,7,6,3,1,4,5,2};


// A Utility Function to check whether given cell (row, col) 
// is a valid cell or not 
bool isValid(int row, int col) 
{ 
	// Returns true if row number and column number 
	// is in range 
	return (row >= 0) && (row < SIDE) && 
		(col >= 0) && (col < SIDE); 
} 

// A Utility Function to check whether given cell (row, col) 
// has a mine or not. 
bool isMine (int row, int col, char board[][MAXSIDE]) 
{ 
	if (board[row][col] == '*') 
		return (true); 
	else
		return (false); 
} 

// A Function to get the user's move 
void makeMove(int *x, int *y) 
{ 
	if (automovesolve == false) {
		// Take the input move 
		cout << "Enter your move, (row, colum) -> ";
		cin >> *x >> *y;
	}
	else {
		*x = AutomovesX[automoves];
		*y = AutomovesY[automoves];
		cout << AutomovesY[automoves] << " "<< AutomovesX[automoves] << endl;
		automoves++;
	}
	return; 
} 

// A Function to print the current gameplay board 
void printBoard(char myBoard[][MAXSIDE]) 
{ 
	cout << "  ";
	for (int i = 0; i < SIDE; i++) {
		cout << i << " ";
	}
	cout << endl;
	for (int i = 0; i<SIDE; i++) 
	{ 
		cout << i << " ";
		for (int j = 0; j < SIDE; j++) {
			cout << myBoard[i][j] << " ";
		}
		cout << endl;
	} 
	return; 
} 

// A Function to count the number of 
// mines in the adjacent cells 
int countAdjacentMines(int row, int col, int mines[][2],char realBoard[][MAXSIDE]) 
{ 


	int count = 0; 
	//----------- 1st Neighbour (North) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid (row-1, col) == true) 
		{ 
			if (isMine (row-1, col, realBoard) == true) 
			count++; 
		} 

	//----------- 2nd Neighbour (South) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid (row+1, col) == true) 
		{ 
			if (isMine (row+1, col, realBoard) == true) 
			count++; 
		} 

	//----------- 3rd Neighbour (East) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid (row, col+1) == true) 
		{ 
			if (isMine (row, col+1, realBoard) == true) 
			count++; 
		} 

	//----------- 4th Neighbour (West) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid (row, col-1) == true) 
		{ 
			if (isMine (row, col-1, realBoard) == true) 
			count++; 
		} 

	//----------- 5th Neighbour (North-East) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid (row-1, col+1) == true) 
		{ 
			if (isMine (row-1, col+1, realBoard) == true) 
			count++; 
		} 

	//----------- 6th Neighbour (North-West) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid (row-1, col-1) == true) 
		{ 
			if (isMine (row-1, col-1, realBoard) == true) 
			count++; 
		} 

	//----------- 7th Neighbour (South-East) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid (row+1, col+1) == true) 
		{ 
			if (isMine (row+1, col+1, realBoard) == true) 
			count++; 
		} 

	//----------- 8th Neighbour (South-West) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid (row+1, col-1) == true) 
		{ 
			if (isMine (row+1, col-1, realBoard) == true) 
			count++; 
		} 

	return (count); 
} 

// A Recursive Fucntion to play the Minesweeper Game 
bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE], 
			int mines[][2], int row, int col, int *movesLeft) 
{ 

	// Base Case of Recursion 
	if (myBoard[row][col] != '-') 
		return (false); 

	// You opened a mine 
	// You are going to lose 
	if (realBoard[row][col] == '*') 
	{ 
		myBoard[row][col] = '*'; 

		for (int i = 0; i<MINES; i++) 
			myBoard[mines[i][0]][mines[i][1]]='*'; 

		printBoard (myBoard); 
		cout << endl << "You Lost" << endl;
		return (true) ; 
	} 

	else
	{ 
		// Calculate the number of adjacent mines and put it 
		// on the board 
		int count = countAdjacentMines(row, col, mines, realBoard); 
		(*movesLeft)--; 

		myBoard[row][col] = count + '0'; 

		if (!count) 
		{ 
			//----------- 1st Neighbour (North) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row-1, col) == true) 
			{ 
				if (isMine (row-1, col, realBoard) == false) 
				playMinesweeperUtil(myBoard, realBoard, mines, row-1, col, movesLeft); 
			} 

			//----------- 2nd Neighbour (South) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row+1, col) == true) 
			{ 
				if (isMine (row+1, col, realBoard) == false) 
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col, movesLeft); 
			} 

			//----------- 3rd Neighbour (East) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row, col+1) == true) 
			{ 
				if (isMine (row, col+1, realBoard) == false) 
					playMinesweeperUtil(myBoard, realBoard, mines, row, col+1, movesLeft); 
			} 

			//----------- 4th Neighbour (West) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row, col-1) == true) 
			{ 
				if (isMine (row, col-1, realBoard) == false) 
					playMinesweeperUtil(myBoard, realBoard, mines, row, col-1, movesLeft); 
			} 

			//----------- 5th Neighbour (North-East) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row-1, col+1) == true) 
			{ 
				if (isMine (row-1, col+1, realBoard) == false) 
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col+1, movesLeft); 
			} 

			//----------- 6th Neighbour (North-West) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row-1, col-1) == true) 
			{ 
				if (isMine (row-1, col-1, realBoard) == false) 
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col-1, movesLeft); 
			} 

			//----------- 7th Neighbour (South-East) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row+1, col+1) == true) 
			{ 
				if (isMine (row+1, col+1, realBoard) == false) 
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col+1, movesLeft); 
			} 

			//----------- 8th Neighbour (South-West) ------------ 

			// Only process this cell if this is a valid one 
			if (isValid (row+1, col-1) == true) 
			{ 
				if (isMine (row+1, col-1, realBoard) == false) 
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col-1, movesLeft); 
			} 
		} 

		return (false); 
	} 
} 

// A Function to place the mines randomly 
// on the board 
void placeMines(int mines[][2], char realBoard[][MAXSIDE]) 
{ 
	bool mark[MAXSIDE*MAXSIDE]; 

	memset (mark, false, sizeof (mark)); 
	if (autosolve == false) 
	{
		// Continue until all random mines have been created. 
		for (int i = 0; i < MINES; )
		{
			int random = rand() % (SIDE*SIDE);
			int x = random / SIDE;
			int y = random % SIDE;

			// Add the mine if no mine is placed at this 
			// position on the board 
			if (mark[random] == false)
			{
				// Row Index of the Mine 
				mines[i][0] = x;
				// Column Index of the Mine 
				mines[i][1] = y;

				// Place the mine 
				realBoard[mines[i][0]][mines[i][1]] = '*';
				mark[random] = true;
				i++;
			}
		}
	}
	else {
		for (int i = 0; i < MINES; ) {
			// Row Index of the Mine 
			mines[i][0] = AutominesX[i];
			// Column Index of the Mine 
			mines[i][1] = AutominesY[i];

			// Place the mine 
			realBoard[mines[i][0]][mines[i][1]] = '*';
			i++;
		}
	}
	return; 
} 


// A Function to initialise the game 
void initialise(char realBoard[][MAXSIDE], char myBoard[][MAXSIDE]) 
{ 
	// Initiate the random number generator so that 
	// the same configuration doesn't arises 
	srand(time (NULL)); 

	// Assign all the cells as mine-free 
	for (int i=0; i<SIDE; i++) 
	{ 
		for (int j=0; j<SIDE; j++) 
		{ 
			myBoard[i][j] = realBoard[i][j] = '-'; 
		} 
	} 

	return; 
} 

// A function to replace the mine from (row, col) and put 
// it to a vacant space 
void replaceMine (int row, int col, char board[][MAXSIDE]) 
{ 
	cout << "Ow no looks like your first guess was a bomb" << endl 
		<< "lets just move that one somewhere else and make that a blank spot";
	for (int i=0; i<SIDE; i++) 
	{ 
		for (int j=0; j<SIDE; j++) 
			{ 
				// Find the first location in the board 
				// which is not having a mine and put a mine 
				// there. 
				if (board[i][j] != '*') 
				{ 
					board[i][j] = '*'; 
					board[row][col] = '-'; 
					return; 
				} 
			} 
	} 
	return; 
} 

// A Function to play Minesweeper game 
void playMinesweeper () 
{ 
	// Initially the game is not over 
	bool gameOver = false; 

	// Actual Board and My Board 
	char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE]; 

	int movesLeft = SIDE * SIDE - MINES, x, y; 
	int mines[MAXMINES][2]; // stores (x,y) coordinates of all mines. 

	initialise (realBoard, myBoard); 

	// Place the Mines randomly 
	placeMines (mines, realBoard); 

	int currentMoveIndex = 0; 
	while (gameOver == false) 
	{ 
		cout << "Current Status of Board : " << endl;
		printBoard (myBoard); 
		makeMove (&x, &y); 

		// This is to guarantee that the first move is 
		// always safe 
		// If it is the first move of the game 
		if (currentMoveIndex == 0) 
		{ 
			// If the first move itself is a mine 
			// then we remove the mine from that location 
			if (isMine (x, y, realBoard) == true) 
				replaceMine (x, y, realBoard); 
		} 

		currentMoveIndex ++; 

		gameOver = playMinesweeperUtil (myBoard, realBoard, mines, x, y, &movesLeft); 
		
		if ((gameOver == false) && (movesLeft == 0)) 
		{ 
			cout << "\nYou won!" << endl << "it took " << currentMoveIndex << " moves to win." << endl;
			gameOver = true;
			printBoard(myBoard);
			int x;
			cin >> x;
		} 

	} 
	return; 
} 

// A Function to choose the difficulty level 
// of the game 
void chooseDifficultyLevel () 
{ 
	/* 
	--> BEGINNER = 9 * 9 Cells and 10 Mines 
	--> INTERMEDIATE = 16 * 16 Cells and 40 Mines 
	--> ADVANCED = 24 * 24 Cells and 99 Mines 
	*/

	int level; 
	cout << "Enter the Difficulty Level" << endl
		<< "Press 0 for BEGINNER (9 * 9 Cells and 10 Mines)" << endl
		<< "Press 1 for INTERMEDIATE (16 * 16 Cells and 40 Mines)" << endl
		<< "Press 2 for ADVANCED (24 * 24 Cells and 99 Mines)" << endl
		<< "Press 3 for CUSTOM (enter the size and number of Mines you want to play with)" << endl
		<< "Press 4 for autosolve (this is a fixed solve of a level)" << endl
		<< "Press 5 for a fixed level (this is a fixed solve of a level)" << endl;

	cin >> level;

	if (level == BEGINNER) 
	{ 
		SIDE = 9; 
		MINES = 10; 
	} 

	if (level == INTERMEDIATE) 
	{ 
		SIDE = 16; 
		MINES = 40; 
	} 

	if (level == ADVANCED) 
	{ 
		SIDE = 24; 
		MINES = 99; 
	} 
	if (level == CUSTOM)
	{
		while (1) {
			cout << "Enter the size of the map then number of mines" << endl << "max size is 24 and max mines is 99" << endl;
			cin >> SIDE >> MINES;
			if (SIDE * SIDE > MINES && SIDE <= 24 && MINES <= 99) {
				break;
			}
			else {
				cout << "to many mines make the size bigger or reduce the number of mines." << endl << endl;
			}
		}
	}

	if (level == AUTOSOLVE)
	{
		autosolve = true;
		automovesolve = true;
		SIDE = 9;
		MINES = 20;
	}
	if (level == FIXEDLEVEL) {
		autosolve = true;
		SIDE = 9;
		MINES = 20;
	}
	return; 
} 

// Driver Program to test above functions 
int main() 
{ 
	/* Choose a level between 
	--> BEGINNER = 9 * 9 Cells and 10 Mines 
	--> INTERMEDIATE = 16 * 16 Cells and 40 Mines 
	--> ADVANCED = 24 * 24 Cells and 99 Mines 
	*/
	chooseDifficultyLevel (); 

	playMinesweeper (); 

	return (0); 
}

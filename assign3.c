 /*
	Jacob Yager
	jcyager
	1/30/2017
	Assignment 3
	Purpose: Create a program that can complete the Knight's Tour.
	Prep-work: I guessed that I could make it to 25 moves and I made it to 33.
*/

#include <stdio.h>

void display(int board[][8]);
void runKnight(int currentRow, int currentColumn, int board[][8]);
void accessibility(int currentRow, int currentColumn, int accessBoard[][8]);
int bestMove(int currentRow, int currentColumn, int chessBoard[][8]);
void betterRunKnight(int currentRow, int currentColumn, int board[][8]);
int bestMoveTie(int currentRow, int currentColumn, int chessBoard[][8]);

  
void  main(void)
{

	/*
	 *This is the 2D array that represents the board.
	 *Each square is initialized as zero, then changed  once the 
	 *knight moves there.
	*/
	int chessBoard[8][8];	
	int l;
	for (l = 0; l < 8; l++){
		int k;
		for (k = 0; k < 8; k++){
			chessBoard[l][k] = 0;
		}
	}

	//these indicate the knights current position
	int currentRow;
	int currentColumn;
	printf("Please enter where you would like the knight to start (1-8)\nI reccomend 8 x 8.\n");
	printf("Row: ");
	scanf("%d", &currentRow);
	printf("Column: "); 
	scanf("%d", &currentColumn);


	//this was the original program for moving a knight without heiristics
	runKnight(currentRow, currentColumn, chessBoard);

	//This is the improved moving knight program with heiristics
	betterRunKnight(currentRow, currentColumn, chessBoard);	
}


//Print the board with visited squares numbers 
void display(int board[][8])
{
	int i;
	for (i=0;i<8;i++){
		int j;
		for (j=0;j<8;j++){
			printf("%d\t", board[i][j]);
		}
	printf("\n\n");	
	}
	return;
}

//I'm using this old runKnight function as a solution to printing 64 in betterRunKnight
void runKnight(int currentRow, int currentColumn, int board[][8])
{
	//these are the 8 possible moves a knight can make
	int horizontal[8] = {2, 1, -1, -2, -2, -1, 1, 2};
	int vertical[8] = {-1, -2, -2, -1, 1, 2, 2, 1};


	/*This keeps track of how many times the knight has moved, I am noting it out
	 *so that I can use runKnight as a solution to the missing 64th number in betterRunKnight

	int counter = 1;
	board[currentRow - 1][currentColumn - 1] = counter;
	counter++;
	*/

	int counter = 64;	 
	int moveNumber = 0;

	while (moveNumber < 8){
	        
		/*These conditions keep it so the knight will not move 
		 *outside the board, or land in a space that has already 
		 *been occupied.
		 */
		if ((horizontal[moveNumber]+currentColumn) < 9 
		     &&	(horizontal[moveNumber]+currentColumn) > 0 
		     && (vertical[moveNumber]+currentRow) < 9 
		     && (vertical[moveNumber]+currentRow) > 0 
		     && board[(vertical[moveNumber]+currentRow-1)][(horizontal[moveNumber]+currentColumn-1)] == 0)
		{
			currentRow += vertical[moveNumber];
			currentColumn += horizontal[moveNumber];
			board[currentRow-1][currentColumn-1] = counter;
			counter++;
			moveNumber = 0;
		}
		else
		{
			moveNumber++;
		} 
	}
	
//THis section is not needed for betterRunKnight	
/*	display(board);
	if (counter == 64){
		printf("You did it! \nYou completed the Knight's Tour in 64 moves! \nCongradulations!\n");
	}
	else{
		printf("You did not complete the Kinght's Tour.\nYou only made it to %d moves.\n", counter);
	}
*/
}

//This function changes the values of the accessibility heuristic
void accessibility(int currentRow, int currentColumn, int accessBoard[][8])
{
	//these are the 8 possible moves a knight can make
	int horizontal[8] = {2, 1, -1, -2, -2, -1, 1, 2};
	int vertical[8] = {-1, -2, -2, -1, 1, 2, 2, 1};


	int moveNumber = 0;
			
	while(moveNumber < 8){			
		
		if ((horizontal[moveNumber]+currentColumn) < 9 
    		&& (horizontal[moveNumber]+currentColumn) > 0 
     	 	&& (vertical[moveNumber]+currentRow) < 9 
     		&& (vertical[moveNumber]+currentRow) > 0
		&& accessBoard[(vertical[moveNumber] + currentRow -1)][(horizontal[moveNumber]+ currentColumn -1)] > 0)
		{
			//changes the current location to zero because it cannot be reached again
			accessBoard[currentRow-1][currentColumn-1] = 0;
	
			//reduces all possible moves from the current square by one
			accessBoard[currentRow + vertical[moveNumber ] -1][currentColumn + horizontal[moveNumber] -1] -= 1;		
		
			moveNumber++;
	
		}
		else{
			moveNumber++;
		} 
	}
}

//This function determines the next best move
int bestMove(int currentRow, int currentColumn, int chessBoard[][8])
{

	int horizontal[8] = {2, 1, -1, -2, -2, -1, 1, 2};
	int vertical[8] = {-1, -2, -2, -1, 1, 2, 2, 1};	

	//these are the accessibility heuristic values
	static int accessBoard[8][8] = {2,3,4,4,4,4,3,2,
   				 3,4,6,6,6,6,4,3,
				 4,6,8,8,8,8,6,4,
				 4,6,8,8,8,8,6,4,
				 4,6,8,8,8,8,6,4,
				 4,6,8,8,8,8,6,4,
				 3,4,6,6,6,6,4,3,
				 2,3,4,4,4,4,3,2};

	accessibility(currentRow, currentColumn, accessBoard);

	int moveNumber = 0;
	int nextMove = 0;
 
	int lastPossible = 10;
			
	while(moveNumber < 8)
	{			


		

		//These cases make sure that the next move is on the board and is not in a position that the knight has already been to	
		if ((horizontal[moveNumber]+currentColumn) < 9 
    		&& (horizontal[moveNumber]+currentColumn) > 0 
     	 	&& (vertical[moveNumber]+currentRow) < 9 
     		&& (vertical[moveNumber]+currentRow) > 0
		&& accessBoard[(vertical[moveNumber] + currentRow -1)][(horizontal[moveNumber]+ currentColumn -1)] > 0)
		{	
			//this inniatiates as the value for how many other squares can be reached from the given square
			int possibleMove = accessBoard[vertical[moveNumber] + currentRow -1][horizontal[moveNumber]+ currentColumn -1];
		
			//This finds the next move that will lead to the least accessible square
			if (possibleMove < lastPossible)
			{
				//I am alturing this so that it works with my bestMoveTie function, turning the accessibility value.
//				nextMove = accessBoard[vertical[moveNumber] + currentRow -1][horizontal[moveNumber]+ currentColumn -1];
 
				nextMove = moveNumber;
				lastPossible = accessBoard[vertical[moveNumber] + currentRow -1][horizontal[moveNumber]+ currentColumn -1];
				
			}		

			//I was using this as a way to test bestMove
//			printf("the possible move: %d\n", possibleMove);
		
			moveNumber++;
		}
		else
		{
			moveNumber++;
		} 
	}

//I was using this to test my steps while using bestMove
/*	printf("the chosen move: %d\nthe counter: %d\n",nextMove, moveNumber); 
	display(accessBoard);
	printf("\n\n\n");
*/
	return nextMove;
}


//This is the program that will complete the Knight's Tour
void betterRunKnight(int currentRow, int currentColumn, int board[][8])
{
	//these are the 8 possible moves a knight can make
	int horizontal[8] = {2, 1, -1, -2, -2, -1, 1, 2};
	int vertical[8] = {-1, -2, -2, -1, 1, 2, 2, 1};


	//This keeps track of how many times the knight has moved
	int counter = 1;
	board[currentRow - 1][currentColumn - 1] = counter;
	counter++;


	while (counter < 64)
	{
		int nextMove = bestMove(currentRow, currentColumn, board); 
		currentRow += vertical[nextMove];
		currentColumn += horizontal[nextMove];
		board[currentRow-1][currentColumn-1] = counter;	
		counter++;
	}
	
	if (counter == 64)
	{
		runKnight(currentRow, currentColumn, board);
	}
	display(board);
}

int bestMoveTie(int currentRow, int currentColumn, int chessBoard[][8])
{

	int horizontal[8] = {2, 1, -1, -2, -2, -1, 1, 2};
	int vertical[8] = {-1, -2, -2, -1, 1, 2, 2, 1};	

	static int accessBoard1[8][8] = {2,3,4,4,4,4,3,2,
   				 3,4,6,6,6,6,4,3,
				 4,6,8,8,8,8,6,4,
				 4,6,8,8,8,8,6,4,
				 4,6,8,8,8,8,6,4,
				 4,6,8,8,8,8,6,4,
				 3,4,6,6,6,6,4,3,
				 2,3,4,4,4,4,3,2};

	accessibility(currentRow, currentColumn, accessBoard1);

	int moveNumber = 0;
 
	int lastPossible = 10;

	//I am makeing an array that will store all possible next moves of a single location.
	int possibleMoves[8] = {10,10,10,10,10,10,10,10};			
	
	//this will fill up possibleMoves with the accessibility number of the correstinding move number
	while(moveNumber < 8)
	{			
		

		//These cases make sure that the next move is on the board and is not in a position that the knight has already been to	
		if ((horizontal[moveNumber]+currentColumn) < 9 
    		&& (horizontal[moveNumber]+currentColumn) > 0 
     	 	&& (vertical[moveNumber]+currentRow) < 9 
     		&& (vertical[moveNumber]+currentRow) > 0
		&& accessBoard1[(vertical[moveNumber] + currentRow -1)][(horizontal[moveNumber]+ currentColumn -1)] > 0)
		{	
		
			possibleMoves[moveNumber] = accessBoard1[vertical[moveNumber] + currentRow -1][horizontal[moveNumber]+ currentColumn -1];
			moveNumber++;
		}
		else
		{
			moveNumber++;
		} 
	}

	//finds the next move with the lowest accesibility 
	int i;
	int nextMove = 0;
	for(i=0; i<6; i++)
	{
		if (possibleMoves[i] > possibleMoves[i+1])
		{
			nextMove = i+1;				
		}

	}

	//finds any ties for lowest accessibility number
	int ties[8] = {10,10,10,10,10,10,10,10};
	for(i=0; i<6; i++)
	{
		if(possibleMoves[nextMove] == possibleMoves[i])
		{
			ties[i] =  bestMove((vertical[i] + currentRow -1),(horizontal[i]+ currentColumn -1), chessBoard);
		}
	}

	//Finally this finds the lowest of the ties next moves.
	nextMove = 0;
	for(i=0; i<6; i++)
	{
		if(ties[i] > ties[i + 1])
		{
			nextMove = i+1;
		}
	}
	return nextMove;
}

//Angel Roberto Ruiz Mendoza A01324489
//Carlos Augusto Amador Manilla A0132
//Monica Perez Martin A0132

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"

/*
* Method that prints the board, it transforms the 1s into Qs and 0s into -s
* Parameters: board - A matrix that represents the n*n board in which the queens are placed
*             n - Size of the board
* Returns: Void
*/
void printBoard(int** board, int n){
	int i, j;
	printf(GREEN);
	//To iterate the matrix
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			//If there is a queen print int
			if(board[i][j] == 1){
				printf("Q ");
			}
			//Else print a hyphen 
			else{
				printf("- ");
			}
		}
		printf("\n");
	}
	printf(RESET);
}


/*
* Method that checks if there wil be a colition when placing a queen in the board
* Parameters: board - A matrix that represents the n*n board in which the queens are placed
*			  row - The row where you will place the queen
*			  column - The column where you will place the queen
*             n - Size of the board
* Returns: Int - one if there is a colition, 0 if there isn't
*/
int checkColition(int** board, int row, int column, int n){
	int i, j;


	//Checks if there is a queen at the left side of the column
	for(i = 0; i < column; i++){
		if( board[row][i] == 1){
			return 1;
		}
	}

	//Checks if there is a queen in the left upper diagonal
	for(i = row, j = column; i >= 0 && j >= 0; i--, j--){
		if(board[i][j] == 1){
			return 1;
		}
	}

	//Checks lower left diagonal
	for(i = row, j = column; j >= 0 && i < n; i++, j--){
		if(board[i][j] == 1){
			return 1;
		}
	}

	return 0;
}

/*
* Method that tries to place a queen in all the row of an specific column, if there is no row it can be placed,
* it goes back to the last time a queen was placed and then it attends to place her in another row. recursivly.
* Parameters: board - A matrix that represents the n*n board in which the queens are placed
*			  row - The row where you will place the queen
*             n - Size of the board
* Returns: Int - one if the queen was placed, 0 if the queen cannot be placed
*/
int backtrack(int** board, int column ,int n){
	//Check if you still have queens to place
	if (column < n){
		int i;

		//Iterate all rows
		for(i = 0; i < n; i++){
			//If there would not be a collition you add a queen to that row
			if(checkColition(board, i, column, n) == 0){
				board[i][column] = 1;
				//Do recurtion, if if returns 1 it means we are done
				if( backtrack(board, column + 1, n) == 1)
					return 1;
				//else, back track and continue to the next row
				board[i][column] = 0;
			}
		}
		//If it checked all the rows and neither was a solution, return 0 to back track
		return 0;
	}
	//Base case, it placed all the queens!!!! Return 1 and finish
	else{
		return 1;
	}
	
}

/*
* Method that initialize the board and calls the method to backtrack and to print the board
* Parameters: n - Size of the board
*/
void solve(int n){
	//Initialization oof the board
	int** board = (int**) malloc(sizeof(int*)*n);
	int i, j;
	for(i = 0; i < n; i++){
		*(board + i) = (int*)malloc(sizeof(int)*n);
	}
	//We set everything to 0, that means there is no queen there
	for (i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			board[i][j] = 0;
		}
	}
	//Call method that retrieves the solution
	backtrack(board, 0, n);
	//Call method that prints the board
	printBoard(board, n);
}


/*
* Method that welcomes the user, ask for the size of the board and calls teh method that solves it
*/
int main(int argc, char const *argv[]){

	int n;
	//Welcome
	printf(BLUE "How many queens are there in the board?\n" RESET);
	scanf("%d", &n);

	clock_t tic = clock();
	//Calls method that solves for n
	solve(n);

	clock_t toc = clock();

    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

	return 0;
}
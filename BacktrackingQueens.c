//Angel Roberto Ruiz Mendoza A01324489
//Carlos Augusto Amador Manilla A0132
//Monica Perez Martin A0132

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

/*
* Method that prints the board, it transforms the 1s into Qs and 0s into -s
* Parameters: board - A matrix that represents the n*n board in which the queens are placed
*             n - Size of the board
* Returns: Void
*/

unsigned long long int count;
int n;

void markBoard(int**board, int x, int y){
	board[x][y] = -1;

	for(int j=y+1; j<n; j++)
		board[x][j]++;
	

	for(int i=x+1, j=y+1; i<n && j<n ; i++, j++)
		board[i][j]++;
	
	
	for(int i=x-1, j=y+1; i>=0 && j<n; i--, j++)
		board[i][j]++;
	
}

void unmarkBoard(int** board, int x, int y){
	board[x][y] = 0;

	for(int j=y+1; j<n; j++)
		board[x][j]--;
	

	for(int i=x+1, j=y+1; i<n && j<n ; i++, j++)
		board[i][j]--;
	
	
	for(int i=x-1, j=y+1; i>=0 && j<n; i--, j++)
		board[i][j]--;
}

/*
* Method that tries to place a queen in all the row of an specific column, if there is no row it can be placed,
* it goes back to the last time a queen was placed and then it attends to place her in another row. recursivly.
* Parameters: board - A matrix that represents the n*n board in which the queens are placed
*			  row - The row where you will place the queen
*             n - Size of the board
* Returns: Int - one if the queen was placed, 0 if the queen cannot be placed
*/
int backtracking(int** board, int queens, int x, int y){
	if(queens == 0){
		count++;
		return 0;
	}
		

	if(x > n-1)
		return 0;
	

	if(board[x][y] == 0){
		markBoard(board, x, y);
		if(backtracking(board, queens-1, 0, y+1) == 1)
			return 1;
		else{
			unmarkBoard(board, x, y);
			return backtracking(board, queens, x+1, y);
		}
	}
	else
		return backtracking(board, queens, x+1, y);
}

/*
* Method that initialize the board and calls the method to backtrack and to print the board
* Parameters: n - Size of the board
*/
void solve(){
	//Initialization oof the board
	int** board = (int**) malloc(sizeof(int*)*n);
	count = 0;
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
	backtracking(board, n, 0, 0);

	printf("Number of possible solutions: %llu\n", count);
}


/*
* Method that welcomes the user, ask for the size of the board and calls teh method that solves it
*/
int main(int argc, char const *argv[]){
	//Welcome
	printf("Welcome, this is the final project for advanced programming.\n");
	printf("Ẃe are now going to use backtracking to solve the N Queens problem\n");
	printf("How many queens are there in the board?\n");
	scanf("%d", &n);

	struct timeval start, end;
    long mtime, seconds, useconds;
	gettimeofday(&start, NULL);
	//Calls method that solves for n
	solve();

	gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %lf seconds\n", (mtime*1.0)/1000);

	return 0;
}
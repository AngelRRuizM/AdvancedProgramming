//Angel Roberto Ruiz Mendoza A01324489
//Carlos Augusto Amador Manilla A01329447
//Monica Perez Martin A01329619

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

pthread_t* threads;
sem_t mutex;
sem_t parent;
int*ids;
int*** boards;
int n;

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
void printBoard(int** board){
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
int checkCollision(int** board, int row, int column){
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
int backtrack(int** board, int column){
	//Check if you still have queens to place

	if (column < n){
		int i;
		//Iterate all rows
		
		for(i = 1; i < n; i++){
			//If there would not be a Collision you add a queen to that row
			if(checkCollision(board, i, column) == 0){
				board[i][column] = 1;
				//Do recurtion, if if returns 1 it means we are done
				if( backtrack(board, column + 1) == 1)
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

void* initThread(void*idptr){
	int id = *(int*)(idptr);
	
	boards[id][0][id] = 1;
	
	if(backtrack(boards[id], 1) == 1){
		sem_wait(&mutex);
		printBoard(boards[id]);
		sem_post(&parent);
	}

	pthread_exit(0);
}

/*
* Method that initialize the board and calls the method to backtrack and to print the board
* Parameters: n - Size of the board
*/
void solve(){
	threads = (pthread_t*)malloc(sizeof(pthread_t)*n);
	ids = (int*)malloc(sizeof(int)*n);
	sem_init(&mutex, 0, 1);
	sem_init(&parent, 0, 1);

	sem_wait(&parent);
	//Initialization oof the board
	boards = (int***) malloc(sizeof(int**)*n);
	int i, j;
	
	for(i = 0; i < n; i++){
		boards[i] = (int**)malloc(sizeof(int*)*n);
		
		for(int j=0; j<n; j++){
			boards[i][j] = (int*)calloc(sizeof(int), n);
		}
	}

	for(int i=0; i<n; i++){
		ids[i] = i;
		pthread_create(&threads[i], NULL, initThread, &ids[i]);
	}

	sem_wait(&parent);

	for(int i=0; i<n; i++){
		ids[i] = i;
		pthread_cancel(threads[i]);
	}

	sem_destroy(&parent);
	sem_destroy(&mutex);
}

inline double my_clock(void) {
  struct timeval t;
  gettimeofday(&t, NULL);
  return (1.0e-6*t.tv_usec + t.tv_sec);
}

/*
 * Method that welcomes the user, ask for the size of the board and calls teh method that solves it
 */
int main(int argc, char const *argv[]){
	//Welcome
	printf(BLUE "How many queens are there in the board?\n" RESET);
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
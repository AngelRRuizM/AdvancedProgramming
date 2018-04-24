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
unsigned long long int count;
int*ids;
int*** boards;
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
		sem_wait(&mutex);

		count++;

		sem_post(&mutex);
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

void* initThread(void*idptr){
	int id = *(int*)(idptr);
	
	markBoard(boards[id], id, 0);
	
	backtracking(boards[id], n-1, 0, 1);

	pthread_exit(0);
}

/*
* Method that initialize the board and calls the method to backtrack and to print the board
* Parameters: n - Size of the board
*/
void solve(){
	threads = (pthread_t*)malloc(sizeof(pthread_t)*n);
	ids = (int*)malloc(sizeof(int)*n);
	count = 0;
	sem_init(&mutex, 0, 1);

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
        printf("New process started in the first line, place %d.\n", i);
	}


	for(int i=0; i<n; i++){
		pthread_join(threads[i], NULL);
	}

	printf("Total possible solutions: %llu\n", count);

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
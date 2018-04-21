#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void printBoard(int** board, int n){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(board[i][j] == 1){
				printf("Q ");
			}
			else{
				printf("- ");
			}
		}
		printf("\n");
	}
}

int checkColition(int** board, int row, int column, int n){
	int i, j;

	for(i = 0; i < column; i++){
		if( board[row][i] == 1){
			return 1;
		}
	}

	for(i = row, j = column; i >= 0 && j >= 0; i--, j--){
		if(board[i][j] == 1){
			return 1;
		}
	}

	for(i = row, j = column; j >= 0 && i < n; i++, j--){
		if(board[i][j] == 1){
			return 1;
		}
	}

	return 0;
}

int backtrack(int** board, int column ,int n){
	if (column < n){
		int i;
		for(i = 0; i < n; i++){
			if(checkColition(board, i, column, n) == 0){
				board[i][column] = 1;

				if( backtrack(board, column + 1, n) == 1)
					return 1;

				board[i][column] = 0;
			}
		}
		return 0;
	}
	else{
		return 1;
	}
	
}

void solve(int n){
	int** board = (int**) malloc(sizeof(int*)*n);
	int i, j;
	for(i = 0; i < n; i++){
		*(board + i) = (int*)malloc(sizeof(int)*n);
	}
	for (i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			board[i][j] = 0;
		}
	}
	backtrack(board, 0, n);
	printBoard(board, n);
}

int main(int argc, char const *argv[]){

	int n;
	printf("Welcome, this is the final project for advanced programming.\n");
	printf("Ẃe are now going to use backtracking to solve the N Queens problem\n");
	printf("How many queens are there in the board?\n");
	scanf("%d", &n);

	solve(n);

	return 0;
}
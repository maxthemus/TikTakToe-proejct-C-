#include<stdio.h>
#include<stdlib.h>

/*
 * this is a program that i am writing in C 
 * it is a tik tac toe CUI game 
 */

//ENUM for signaling what player turn it is
enum player {
	P_ONE,
	P_TWO
};


//Function for printing out the board
void printBoard(char** board) {
	printf("  1   2   3 \n");

	for(int i = 0; i < 3; i++) {
		printf("%d ", (i + 1));
		
		for(int j = 0; j < 3; j++) {
			printf("%c", board[i][j]);
			if(j < 2) {
				printf(" | ");
			}
		}	
		if(i < 2) {		
			printf("\n  ----------\n");
		}
	}
	printf("\n");
}	

//This function is for reseting the board back to its originalState
void resetBoard(char **board) {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			board[i][j] = ' ';
		}
	}
}

void placePiece(char **board, char character, int x, int y) {
	board[(y - 1)][(x - 1)] = character;
}

int checkTaken(char **board, int x, int y) {
	if(board[(y - 1)][(x - 1)] == ' ') {
		return 1;
	}
	return 0;
}

int checkWonGame(char **board, enum player playerTurn) {
	char characters[3] = {'x', 'o', '\0'};
	
	//Checking Horizontally
	for(int i = 0; i < 3; i++) {
		if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == characters[playerTurn]) {
			return playerTurn;
		}
	}

	//Checking Vertically
	for(int i = 0; i < 3; i++) {
		if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] == characters[playerTurn]) {
			return playerTurn;
		}
	}

	//check top Right to bottom left
	if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == characters[playerTurn]) {
		return playerTurn;
	}
	//check top left to bottom right
	if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == characters[playerTurn]) {
		return playerTurn;
	}

	//means they haven't won
	return -1;
}

//Function for getting input from keyboard to make a player place a piece
void makeTurn(char **board, enum player playerTurn) {
	printf("+----------+\n");
	printf("| Player %d |\n", (playerTurn + 1));
	printf("+----------+\n");
	
	int validPos = 0;
	int xCord = -1;
	int yCord = -1;
	//Getting the character to be placed;
	char characters[3] = {'x', 'o', '\0'};

	do {
		//input validation for X cord
		do {
			printf("X cord: ");	
			scanf("%d", &xCord);

			if(xCord < 1 || xCord > 3) {
				printf("INVALID INPUT PLEASE TRY AGAIN!\n");
		}
		} while(xCord < 1 || xCord > 3);

		//Input validation for Y cord
		do {
			printf("Y cord: ");
			scanf("%d", &yCord);

			if(yCord < 1 || yCord > 3) {
				printf("INVALID INPUT PLEASE TRY AGAIN\n");	
			}
		} while (yCord < 1 || yCord > 3);

		validPos = checkTaken(board, xCord, yCord);

		if(validPos != 1) {
			printf("SORRY THIS POSITION IS TAKEN TRY AGAIN!\n");
		}
	} while(validPos != 1);
	
	printf("Placing \"%c\" at position (%d, %d)\n", characters[playerTurn], xCord, yCord);

	placePiece(board, characters[playerTurn], xCord, yCord);
}

char** createBoard(void) {
	char** board = (char**)malloc(3 * sizeof(char*));
	for(int i = 0; i < 3; i++) {
		board[i] = (char *)malloc(3 * sizeof(char));
	}

	return board;
}

enum player switchPlayer(enum player playerTurn) {
	if(playerTurn == 0) {
		enum player temp = P_TWO;
		return temp;
	}
	enum player temp = P_ONE;
	return temp;
}

//This is the function that will be called to start the game
void gameController(void) {	
	enum player playerTurn = P_ONE;
	char **board = createBoard();
	int winner = -1;
	int counter = 0;
	resetBoard(board);

	do {
		printBoard(board);	
		makeTurn(board, playerTurn); 
		winner = checkWonGame(board, playerTurn);

		if(winner == -1) {
			playerTurn = switchPlayer(playerTurn);
		}


		printf("\n+----------+\n");
		counter++;
	} while (winner == -1 && counter < 9);

	printBoard(board);

	if(winner == -1) {
		printf("+-----------+\n");
		printf("| NO WINNER |\n");
		printf("+-----------+\n");
	} else {
		printf("+-----------------+\n");
		printf("| WINNER PLAYER %d |\n", (playerTurn + 1));
	       	printf("+-----------------+\n");	
	}

}


int main(void) {
	int input = 0;

	do { 
		printf("+-------------+\n");
		printf("| TIK TAK TOE |\n");
		printf("+-------------+\n");
		
		do {
			printf("[1] Play game\n");
			printf("[0] Exit\n");
			printf("-> ");
			scanf("%d", &input);

			if(input < 0 || input > 1) {
				printf("INVALID INPUT PLEASE TRY AGAIN!\n");
			}
		} while(input < 0 || input > 1);

		if(input == 1) {	
			printf("+----------+\n");
			gameController();
		}

	} while(input != 0);

	printf("\nTHANK YOU FOR PLAYING TIK TAK TOE!\n");

	return 0;
}

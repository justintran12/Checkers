#include "checkers.h"

void move(char (*board)[WIDTH][LENGTH], coord before, coord after, char color) {
	*(*(*board + before.y) + before.x) = EMPTY;
	*(*(*board + after.y) + after.x) = color;
}

void take(char (*board)[WIDTH][LENGTH], coord Coord) {
	*(*(*board + Coord.y) + Coord.x) = EMPTY;
}

// Given coordinate of the piece to move, returns array of valid coordinates that the piece can move to.
coord *getMoves(char (*board)[WIDTH][LENGTH], coord piece, char color, int *count, boo1 hopAgain) {
	coord *moves = malloc(sizeof(coord) * 2);
	
	// Initialize values
	boo1 validLeft = ((piece.x - 1) < 0) ? FALSE : TRUE;
	boo1 validRight = ((piece.x + 1) > 7) ? FALSE : TRUE;
	boo1 validLeftNext = ((piece.x - 2) < 0) ? FALSE : TRUE;
	boo1 validRightNext = ((piece.x + 2) > 7) ? FALSE : TRUE;
	char upLeft, upRight, botLeft, botRight;
	char upLeftNext, upRightNext, botLeftNext, botRightNext;
	coord upLeftCoord, upRightCoord, botLeftCoord, botRightCoord;
	coord upLeftNextCoord, upRightNextCoord, botLeftNextCoord, botRightNextCoord;
	int i = 0;
	if (validLeft) {
		upLeft = *(*(*board + piece.y - 1) + piece.x - 1);
		botLeft = *(*(*board + piece.y + 1) + piece.x - 1);
		upLeftCoord.x = piece.x - 1;
		upLeftCoord.y = piece.y - 1;
		botLeftCoord.x = piece.x - 1;
		botLeftCoord.y = piece.y + 1;
	} else {
		upLeft = 0;
		botLeft = 0;
		upLeftCoord.x = 0;
		upLeftCoord.y = 0;
		botLeftCoord.x = 0;
		botLeftCoord.y = 0;
	}
	if (validRight) {
		upRight = *(*(*board + piece.y - 1) + piece.x + 1);
		botRight = *(*(*board + piece.y + 1) + piece.x + 1);
		upRightCoord.x = piece.x + 1;
		upRightCoord.y = piece.y - 1;
		botRightCoord.x = piece.x + 1;
		botRightCoord.y = piece.y + 1;
	} else {
		upRight = 0;
		botRight = 0;
		upRightCoord.x = 0;
		upRightCoord.y = 0;
		botRightCoord.x = 0;
		botRightCoord.y = 0;
	}
	if (validLeftNext) {
		upLeftNext = *(*(*board + piece.y - 2) + piece.x - 2);
		botLeftNext = *(*(*board + piece.y + 2) + piece.x - 2);
		upLeftNextCoord.x = piece.x - 2;
		upLeftNextCoord.y = piece.y - 2;
		botLeftNextCoord.x = piece.x - 2;
		botLeftNextCoord.y = piece.y + 2;
	} else {
		upLeftNext = 0;
		botLeftNext = 0;
		upLeftNextCoord.x = 0;
		upLeftNextCoord.y = 0;
		botLeftNextCoord.x = 0;
		botLeftNextCoord.y = 0;
	}
	if (validRightNext) {
		upRightNext = *(*(*board + piece.y - 2) + piece.x + 2);
		botRightNext = *(*(*board + piece.y + 2) + piece.x + 2);
		upRightNextCoord.x = piece.x + 2;
		upRightNextCoord.y = piece.y - 2;
		botRightNextCoord.x = piece.x + 2;
		botRightNextCoord.y = piece.y + 2;
	} else {
		upRightNext = 0;
		botRightNext = 0;
		upRightNextCoord.x = 0;
		upRightNextCoord.y = 0;
		botRightNextCoord.x = 0;
		botRightNextCoord.y = 0;
	}
	
	// Check all possible moves, add valid moves to return buffer
	if (color == WHITE) {
		if (upLeft == EMPTY) {
			*(moves + i) = upLeftCoord;
			i++;
		} else if ((upLeft == BLACK || upLeft == B_KING) && upLeftNext == EMPTY) {
			*(moves + i) = upLeftNextCoord;
			i++;
		}
		if (upRight == EMPTY) {
			*(moves + i) = upRightCoord;
			i++;
		} else if ((upRight == BLACK || upRight == B_KING) && upRightNext == EMPTY) {
			*(moves + i) = upRightNextCoord;
			i++;
		}
	} else if (color == BLACK) { 
		if (botLeft == EMPTY) {
			*(moves + i) = botLeftCoord;
			i++;
		} else if ((botLeft == WHITE || botLeft == W_KING) && botLeftNext == EMPTY) {
			*(moves + i) = botLeftNextCoord;
			i++;
		}
		if (botRight == EMPTY) {
			*(moves + i) = botRightCoord;
			i++;
		} else if ((botRight == WHITE || botRight == W_KING) && botRightNext == EMPTY) {
			*(moves + i) = botRightNextCoord;
			i++;
		}
	} else if (color == W_KING) {
		if (botLeft == EMPTY && hopAgain == FALSE) {
			*(moves + i) = botLeftCoord;
			i++;
		} else if ((botLeft == BLACK || botLeft == B_KING) && botLeftNext == EMPTY) {
			*(moves + i) = botLeftNextCoord;
			i++;
		}
		if (botRight == EMPTY && hopAgain == FALSE) {
			*(moves + i) = botRightCoord;
			i++;
		} else if ((botRight == BLACK || botRight == B_KING) && botRightNext == EMPTY) {
			*(moves + i) = botRightNextCoord;
			i++;
		}
		if (upLeft == EMPTY && hopAgain == FALSE) {
			*(moves + i) = upLeftCoord;
			i++;
		} else if ((upLeft == BLACK || upLeft == B_KING) && upLeftNext == EMPTY) {
			*(moves + i) = upLeftNextCoord;
			i++;
		}
		if (upRight == EMPTY && hopAgain == FALSE) {
			*(moves + i) = upRightCoord;
			i++;
		} else if ((upRight == BLACK || upRight == B_KING) && upRightNext == EMPTY) {
			*(moves + i) = upRightNextCoord;
			i++;
		}
	} else if (color == B_KING) {
		if (botLeft == EMPTY && hopAgain == FALSE) {
			*(moves + i) = botLeftCoord;
			i++;
		} else if ((botLeft == WHITE || botLeft == W_KING) && botLeftNext == EMPTY) {
			*(moves + i) = botLeftNextCoord;
			i++;
		}
		if (botRight == EMPTY && hopAgain == FALSE) {
			*(moves + i) = botRightCoord;
			i++;
		} else if ((botRight == WHITE || botRight == W_KING) && botRightNext == EMPTY) {
			*(moves + i) = botRightNextCoord;
			i++;
		}
		if (upLeft == EMPTY && hopAgain == FALSE) {
			*(moves + i) = upLeftCoord;
			i++;
		} else if ((upLeft == WHITE || upLeft == W_KING) && upLeftNext == EMPTY) {
			*(moves + i) = upLeftNextCoord;
			i++;
		}
		if (upRight == EMPTY && hopAgain == FALSE) {
			*(moves + i) = upRightCoord;
			i++;
		} else if ((upRight == WHITE || upRight == W_KING) && upRightNext == EMPTY) {
			*(moves + i) = upRightNextCoord;
			i++;
		}
	} else {
		fprintf(stderr, "error: invalid piece input to getMoves function\n");
	}
	
	*count = i;
	return moves;
	
}

void printBoard(char board[WIDTH][LENGTH]) {
	int i, j;
	for (i = 0; i < WIDTH; i++) {
		for (j = 0; j < LENGTH - 1; j++) {
			printf("%c ", board[i][j]);
		}
		printf("%c\n", board[i][j]);
	}
}	

void printMoves(coord *moves, boo1 hopAgain, int count) {
	printf("Select from the following options. Enter the number associated with the coordinate\n");
	for (int i = 0; i < count; i++) {
		coord move = *(moves + i);
		printf("%d. (%d, %d)\n", i + 1, move.x, move.y);
	}
	if (hopAgain == FALSE) {
		printf("%d. Choose different piece\n", ++count);
	}
	printf("%d, Quit\n", ++count);
}

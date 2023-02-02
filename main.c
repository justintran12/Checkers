#include "checkers.h"

int main() {
	static char board[WIDTH][LENGTH] = 
		{{EMPTY, BLACK, EMPTY, BLACK, EMPTY, BLACK, EMPTY, BLACK},
		 {BLACK, EMPTY, BLACK, EMPTY, BLACK, EMPTY, BLACK, EMPTY},
		 {EMPTY, BLACK, EMPTY, BLACK, EMPTY, BLACK, EMPTY, BLACK},
		 {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
		 {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
		 {WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY},
		 {EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE},
		 {WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY}
		};
	char (*pBoard)[WIDTH][LENGTH] = &board;
	int x, y, correctX, correctY, count, nextCount, option, offset;
	char turn, pieceType;
	coord hopCoord;
	boo1 gameOn, hopAgain, validMove;
	count = 0;
	nextCount = 0;
	option = 0;
	gameOn = TRUE;
	hopAgain = FALSE;
	hopCoord.x = 0;
	hopCoord.y = 0;
	turn = WHITE;
	printf("Top Left is (0, 0), Bottom Right is (7,7)\n");
	
	while (gameOn) {
		printBoard(board);
		
		if (hopAgain) {
			if (turn == WHITE) {
				printf("Another hop available for White.\n");
			} else {
				printf("Another hop available for Black.\n");
			}
		} else {
			if (turn == WHITE) {
				printf("It is White's turn, please enter the coordinates of the piece to move.\nFormat: x, y\n");
			} else {
				printf("It is Black's turn, please enter the coordinates of the piece to move.\nFormat: x, y\n");
			}
			scanf("%d, %d", &x, &y);
			if (turn == WHITE && board[y][x] == WHITE) {
				validMove = TRUE;
			} else if (turn == WHITE && board[y][x] == W_KING) {
				validMove = TRUE;
			} else if (turn == BLACK && board[y][x] != BLACK) {
				validMove = TRUE;
			} else if (turn == BLACK && board[y][x] != B_KING) {
				validMove = TRUE;
			} else {
				validMove = FALSE;
			}
			// error check for input coordinate
			while (x < 0 || x > 7 || y < 0 || y > 7 || validMove != TRUE) {
				printf("Not a valid coordinate. Enter another coordinate\n");
				scanf("%d, %d", &x, &y);
			}
		}

		coord selPiece;
		correctX = (hopAgain) ? hopCoord.x : x;
		correctY = (hopAgain) ? hopCoord.y : y;
		selPiece.x = correctX;
		selPiece.y = correctY;
		pieceType = board[correctY][correctX];
		coord *moves = getMoves(pBoard, selPiece, pieceType, &count, hopAgain);
		printMoves(moves, hopAgain, count);
		scanf("%d", &option);
		
		offset = (hopAgain) ? 1 : 2;
		// error check for input option
		while (option > count + offset | option < 1) {
			printf("Not a valid option listed. Try again.\n");
			scanf("%d", &option);
		}

		// if selected a valid move option
		if (option <= count) {
			coord toPosn = *(moves + option - 1);
			move(pBoard, selPiece, toPosn, pieceType);
			// if black or white reaches opposite end of board, turn it into a king (new fxn)
			if (turn == WHITE && toPosn.y == 0) {
				board[toPosn.y][toPosn.x] = W_KING;
				pieceType = W_KING;
			} else if (turn == BLACK && toPosn.y == 7) {
				board[toPosn.y][toPosn.x] = B_KING;
				pieceType = B_KING;
			}
			// if hopping
			if (abs(toPosn.x - selPiece.x) == 2) {
				coord takenPiece;
				takenPiece.x = (toPosn.x > selPiece.x) ? (selPiece.x + 1) : (selPiece.x - 1);
				takenPiece.y = (toPosn.y > selPiece.y) ? (selPiece.y + 1) : (selPiece.y - 1);
				take(pBoard, takenPiece);
				// check moves for coord toPosn, if hop available again, don't switch turn
				coord *nextMoves = getMoves(pBoard, toPosn, pieceType, &nextCount, hopAgain);
				// loop thru nextMoves, check for a hop
				for (int a = 0; a < nextCount; a++) {
					coord nextPosn = *(nextMoves + a);
					if (abs(nextPosn.x - toPosn.x) == 2){
						hopAgain = TRUE;
						hopCoord.x = toPosn.x;
						hopCoord.y = toPosn.y;
						break;
					} else {
						hopAgain = FALSE;
					}
				}
				if (nextCount == 0) {
					hopAgain = FALSE;
				}
				free(nextMoves);
			}
			if (hopAgain == FALSE) {
				turn = (turn == WHITE | turn == W_KING) ? BLACK : WHITE;
			}

		} 
		if (option == count + offset) {
			gameOn = FALSE;
		} 
		
		free(moves);
	}
	return 0;
}

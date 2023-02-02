#include <stdio.h>
#include <stdlib.h>

#define WIDTH 8
#define LENGTH 8

#define BLACK 'b'
#define WHITE 'w'
#define EMPTY '-'
#define B_KING 'B'
#define W_KING 'W'


typedef struct coord {
	int x;
	int y; 
} coord;

typedef enum { 
	FALSE,
	TRUE
} boo1;

void move(char (*)[WIDTH][LENGTH], coord, coord, char);
void take(char (*)[WIDTH][LENGTH], coord);
coord *getMoves(char (*)[WIDTH][LENGTH], coord, char, int *, boo1);
void printBoard(char [WIDTH][LENGTH]);
void printMoves(coord *, boo1, int);


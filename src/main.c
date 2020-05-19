#include <stdio.h>
#include <stdint.h>

#include "types.h"
#include "bitboard.h"
#include "printer.h"
#include "movegen.h"
#include "rays.h"

#include <time.h>






/* Creates a board representing all spaces occupied by Color c then
   isolates the bit-index sq. If this bit is a 1, a non-zero long
   unsigned int is returned which evaluates to true. If this space
   is not occupied by Color c, then 0 is returned. */
long unsigned int occupiesSquare(struct CBoard board, enum Square sq, enum Color c) {
	if (c == WHITE) {
		return WHITE_BOARD(board) & (1UL << sq);
	} else {
		return BLACK_BOARD(board) & (1UL << sq);
	}
}


struct Position generateStartingPosition(struct CBoard board) {
	struct Position pos;

	pos.board = board;
	pos.parent = NULL;

	pos.sideToMove = WHITE;

	pos.wkCastle = FALSE;
	pos.wqCastle = FALSE;
	pos.bkCastle = FALSE;
	pos.bqCastle = FALSE;

	// Sets numOfMoves and moveList
	generateMovesFromPos(&pos);

	return pos;
}

/*
void printMove(struct Move m) {
	printf("From:         To:\n");
	printBitboard(1UL << m.from);
	printf("\n");
	printf("To:\n");
	printBitboard(1UL << m.to);
}
*/

int main() { 

	// Precompute ray tables
	initRays();

	Board knight;
	knight = 1UL << 53;

	int n = 8;
	Board south_ray = rays[NORTH_WEST][58];
	printBitboard(south_ray);

	
}

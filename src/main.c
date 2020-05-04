#include <stdio.h>
#include <stdint.h>

#include "bitboard.h"
#include "printer.h"
#include "types.h"

#include <time.h>

// Knight moves
Board noNoEa(Board b) {return (b << 17) & ~A_FILE; }
Board noEaEa(Board b) {return (b << 10) & ~A_FILE & ~B_FILE; }
Board soEaEa(Board b) {return (b >>  6) & ~A_FILE & ~B_FILE; }
Board soSoEa(Board b) {return (b >> 15) & ~A_FILE; }
Board noNoWe(Board b) {return (b << 15) & ~H_FILE; }
Board noWeWe(Board b) {return (b <<  6) & ~H_FILE & ~G_FILE; }
Board soWeWe(Board b) {return (b >> 10) & ~H_FILE & ~G_FILE; }
Board soSoWe(Board b) {return (b >> 17) & ~H_FILE; }


/** Assumes there is a single 1 bit in the board. */
uint8_t singleBitScan(Board board) {
	for (int i=0; i < 64; i++) {
		if (board >> i == 1) {
			return i;
		}
	}
}

Board knightAttacks(Board knights) {
	return noNoEa(knights) | noEaEa(knights) | soEaEa(knights) | soSoEa(knights) | noNoWe(knights) | noWeWe(knights) | soWeWe(knights) | soSoWe(knights);
}

/** Generate the moves for a board with a single knight. */
void oneKnightMoves(Board board, Move *moves) {
	// A knight has 8 potential moves.

	uint8_t from = singleBitScan(board);
	
	Board to_board = noNoEa(board) | noEaEa(board) | soEaEa(board) | soSoEa(board) | noNoWe(board) | noWeWe(board) | soWeWe(board) | soSoWe(board);

	uint8_t idx = 0;
	uint8_t one = 1;

	for (uint8_t i=0; i < 64; i++) {
		if ((to_board >> i) & one == 1) {
			moves[idx] = (i << 6) | from;
			idx += 1;
		}
	}
}

int main() { 
  Board knightboard = 0x800;
  
  struct CBoard board = generateBoard();

  printCBoard(board);
  return 0;
}

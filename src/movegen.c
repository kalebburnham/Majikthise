#include "movegen.h"
#include <stdio.h>

// Knight moves
Board noNoEa(Board b) {return (b << 17) & ~A_FILE; }
Board noEaEa(Board b) {return (b << 10) & ~A_FILE & ~B_FILE; }
Board soEaEa(Board b) {return (b >>  6) & ~A_FILE & ~B_FILE; }
Board soSoEa(Board b) {return (b >> 15) & ~A_FILE; }
Board noNoWe(Board b) {return (b << 15) & ~H_FILE; }
Board noWeWe(Board b) {return (b <<  6) & ~H_FILE & ~G_FILE; }
Board soWeWe(Board b) {return (b >> 10) & ~H_FILE & ~G_FILE; }
Board soSoWe(Board b) {return (b >> 17) & ~H_FILE; }

Board noWe(Board b) { return (b << 7) & ~H_FILE; }
Board noEa(Board b) { return (b << 9) & ~A_FILE; }
Board soWe(Board b) { return (b >> 9) & ~H_FILE; }
Board soEa(Board b) { return (b >> 7) & ~A_FILE; }

/* Generate the possible bishop attacks using the classical approach. 
This technique and code is copied with a small modification from 
https://rhysre.net/2019/01/15/magic-bitboards.html */
Board bishopAttacks(enum Square sq, Board blockers) {

	Board nw_attacks = rays[NORTH_WEST][sq];
	if (rays[NORTH_WEST][sq] & blockers) {
    	int blockerIndex = BSF(rays[NORTH_WEST][sq] & blockers);
    	nw_attacks &= ~rays[NORTH_WEST][blockerIndex];
  	}

	Board ne_attacks = rays[NORTH_EAST][sq];
  	if (rays[NORTH_EAST][sq] & blockers) {
   		int blockerIndex = BSF(rays[NORTH_EAST][sq] & blockers);
    	ne_attacks &= ~rays[NORTH_EAST][blockerIndex];
  	}

	Board se_attacks = rays[SOUTH_EAST][sq];
	if (rays[SOUTH_EAST][sq] & blockers) {
		int blockerIndex = BSR(rays[SOUTH_EAST][sq] & blockers);
		se_attacks &= ~rays[SOUTH_EAST][blockerIndex];
	}

	Board sw_attacks = rays[SOUTH_WEST][sq];
	if (rays[SOUTH_WEST][sq] & blockers) {
		int blockerIndex = BSR(rays[SOUTH_WEST][sq] & blockers);
		sw_attacks &= ~rays[SOUTH_WEST][blockerIndex];
	}

	return nw_attacks | ne_attacks | se_attacks | sw_attacks;
}

Board rookAttacks(enum Square sq, Board blockers) {

	Board north_attacks = rays[NORTH][sq];
	if (rays[NORTH][sq] & blockers) {
    	int blockerIndex = BSF(rays[NORTH][sq] & blockers);
    	north_attacks &= ~rays[NORTH][blockerIndex];
  	}

	Board east_attacks = rays[EAST][sq];
  	if (rays[EAST][sq] & blockers) {
   		int blockerIndex = BSF(rays[EAST][sq] & blockers);
    	east_attacks &= ~rays[EAST][blockerIndex];
  	}

	Board south_attacks = rays[SOUTH][sq];
	if (rays[SOUTH][sq] & blockers) {
		int blockerIndex = BSR(rays[SOUTH][sq] & blockers);
		south_attacks &= ~rays[SOUTH][blockerIndex];
	}

	Board west_attacks = rays[WEST][sq];
	if (rays[WEST][sq] & blockers) {
		int blockerIndex = BSR(rays[WEST][sq] & blockers);
		west_attacks &= ~rays[WEST][blockerIndex];
	}

	return north_attacks | east_attacks | south_attacks | west_attacks;
}

Board queenAttacks(enum Square sq, Board blockers) {
	return bishopAttacks(sq, blockers) | rookAttacks(sq, blockers);
}

Board kingAttacks(enum Square sq) {
    Board b = 1ULL << sq;
    return ((b << 1) & ~A_FILE) | ((b >> 1) & ~H_FILE) | b << 8 | b >> 8 | noWe(b) | noEa(b) | soWe(b) | soEa(b);
}

/* This needs to be modified if en passant is considered. */
Board pawnAttacks(Board pawns, enum Color c) {
	if (c == WHITE) {
		return noWe(pawns) | noEa(pawns);
	} else {
		return soWe(pawns) | soEa(pawns);
	}
}

int generatePawnMoves(struct Position *pos, struct Move *moves) {
    return 1;
}

void generateMovesFromPos(struct Position *pos) {

}



int generateKnightMoves(Board b, struct Move *moves) {
    Board knights[2] = {0};
    singularize(b, knights);

}

Board knightAttacks(enum Square sq) {
    Board board = 1ULL << sq;
	return noNoEa(board) | noEaEa(board) | soEaEa(board) | soSoEa(board) | noNoWe(board) | noWeWe(board) | soWeWe(board) | soSoWe(board);
}

/** Generate the moves for a board with a single knight. */
int knightMoves(Board board, struct Move *moves) {
	// A knight has 8 potential moves.
    int to;

	uint8_t from = BSF(board);
	Board to_board = knightAttacks(board);

    Board singles[8] = {0};
    int n = singularize(to_board, singles);

    for (int idx=0; idx < n; idx++) {
        to = BSF(singles[idx]);
        struct Move m = { .from=from, .to=to, .flag=0x00 };
        moves[idx] = m;
    }

    return n;
}

int singularize(Board b, Board *singles) {
    int pos;
    int idx = 0;

    while (b) {
        pos = BSF(b);
        singles[idx++] = 1UL << pos;
        b ^= 1UL << pos;
    }

    return idx;
}


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

Board knightAttacks(Board board) {
	Board to_board = noNoEa(board) | noEaEa(board) | soEaEa(board) | soSoEa(board) | noNoWe(board) | noWeWe(board) | soWeWe(board) | soSoWe(board);
	return to_board;
}

/** Generate the moves for a board with a single knight. */
int knightMoves(Board board, struct Move *moves) {
	// A knight has 8 potential moves.
    int to;

	uint8_t from = bitScanForward(board);
	Board to_board = knightAttacks(board);

    Board singles[8] = {0};
    int n = singularize(to_board, singles);

    for (int idx=0; idx < n; idx++) {
        to = bitScanForward(singles[idx]);
        struct Move m = { .from=from, .to=to, .flag=0x00 };
        moves[idx] = m;
    }

    return n;
}

int singularize(Board b, Board *singles) {
    int pos;
    int idx = 0;

    while (b) {
        pos = bitScanForward(b);
        singles[idx++] = 1UL << pos;
        b ^= 1UL << pos;
    }

    return idx;
}


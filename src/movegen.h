#ifndef MOVEGEN_INCLUDE
#define MOVEGEN_INCLUDE

#include "bitboard.h"
#include "types.h"

Board noNoEa(Board b);
Board noEaEa(Board b);
Board soEaEa(Board b);
Board soSoEa(Board b);
Board noNoWe(Board b);
Board noWeWe(Board b);
Board soWeWe(Board b);
Board soSoWe(Board b);

Board noWe(Board b);
Board noEa(Board b);
Board soWe(Board b);
Board soEa(Board b);

/* Returns a board of the diagonal attacks from the specified square with the
given blockers. */
Board bishopAttacks(enum Square sq, Board blockers);

/* Returns a board of the straight-line attacks from the specified square with
the given blockers. */
Board rookAttacks(enum Square sq, Board blockers);

/* Returns a board where 1-bits signal that square is attacked by a knight on
the specified square. */
Board knightAttacks(enum Square sq);

/* Returns a board of the diagonal and straight-line attacks from the
specified square with the given blockers. */
Board queenAttacks(enum Square sq, Board blockers);

/* Returns a board where 1-bits signal that square is attacked by a king on
the specified square. */
Board kingAttacks(enum Square sq);

int generatePawnMoves(struct Position *pos, struct Move *moves);

void generateMovesFromPos(struct Position *pos);

int knightMoves(Board board, struct Move *moves);

/* The returned int should the size of the moves array of non-zero
   values. The maximum number of knight moves per side is 16. */
int generateKnightMoves(Board b, struct Move *moves);

/* Given a bitboard of multiple 1-bits, return a pointer to a list of
   bitboards each with a single 1-bit. */
int singularize(Board b, Board* singles);

#endif // MOVEGEN_INCLUDE
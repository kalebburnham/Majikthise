#ifndef MOVEGEN_INCLUDE
#define MOVEGEN_INCLUDE

#include "bitboard.h"
#include "printer.h"
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

int wGenerateAllPawnMoves(struct Position *pos, struct Move *moves);
int bGenerateAllPawnMoves(struct Position *pos, struct Move *moves);

void generateMovesFromPos(struct Position *pos);

/* Generate all the white pawn single push moves. The moves array should have size
8. Return the number of moves generated.
Since pawns must promote on the eigth rank, do not include moves to the eighth.
That is handled by wGeneratePawnPromotion. */
int wGeneratePawnPushMoves(struct CBoard board, struct Move *moves);

int wGenerateDoublePawnPushMoves(struct CBoard board, struct Move *moves);

/* Generate all the black pawn push moves. The moves array should have size
8. Return the number of moves generated. */
int bGeneratePawnPushMoves(struct CBoard board, struct Move *moves);

int bGenerateDoublePawnPushMoves(struct CBoard board, struct Move *moves);

int knightMoves(Board board, struct Move *moves);

/* The returned int should the size of the moves array of non-zero
   values. The maximum number of knight moves per side is 16. */
int wGenerateKnightMoves(struct CBoard b, struct Move *moves);
int bGenerateKnightMoves(struct CBoard b, struct Move *moves);

int wGenerateBishopMoves(struct CBoard b, struct Move *moves);
int bGenerateBishopMoves(struct CBoard b, struct Move *moves);


int wGeneratePawnPromotionMoves(struct CBoard board, struct Move *moves);
int bGeneratePawnPromotionMoves(struct CBoard board, struct Move *moves);

/* Generate non-En Passant pawn captures. Moves array should hold 16 Moves. */
int wGeneratePawnCaptures(struct CBoard board, struct Move *moves);
int bGeneratePawnCaptures(struct CBoard board, struct Move *moves);

/* Generate pawn attacks during En Passant. The moves array should hold 2 Moves.  */
int wGenerateEnPassantPawnMoves(struct CBoard board, enum Square epTargetSquare, struct Move *moves);
int bGenerateEnPassantPawnMoves(struct CBoard board, enum Square epTargetSquare, struct Move *moves);

int wGeneratePawnPromotionAndCaptureMoves(struct CBoard board, struct Move *moves);
int bGeneratePawnPromotionAndCaptureMoves(struct CBoard board, struct Move *moves);

/* Given a list of moves (and numMoves, the size of the array), loop through them
set the move flag to En Passant if the To square matches epTargetSquare. */
void updateFlagEnPassant(enum Square epTargetSquare, struct Move *moves, int numMoves);

/* Given a bitboard of multiple 1-bits, return a pointer to a list of
   bitboards each with a single 1-bit. */
int singularize(Board b, Board* singles);

#endif // MOVEGEN_INCLUDE
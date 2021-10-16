#ifndef EVAL_INCLUDE
#define EVAL_INCLUDE

#include "bitboard.h"
#include "printer.h"
#include "types.h"

/* An isolated pawn is a pawn with no friendly pawns on the same file or either
adjacent file. */
int numIsolatedPawns(struct CBoard b, enum Color c);

/* A double pawn is a pawn with another pawn on the same file. For example, 
pawns on A2 and A3 count as 2 doubled pawns. A tripled pawn structure counts
as 3 doubled pawns. */
int numDoubledPawns(struct CBoard b, enum Color c);

int numBlockedPawns(struct CBoard b, enum Color c);

#endif // EVAL_INCLUDE
#ifndef CONVERSION_INCLUDE
#define CONVERSION_INCLUDE

#include "types.h"

Move uciMoveToBits(char *move, CBoard b);

char* bitsToUciMove(Move move);

#endif // CONVERSION_INCLUDE
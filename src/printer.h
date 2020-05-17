#ifndef PRINTER_INCLUDE
#define PRINTER_INCLUDE

#include <stdio.h>

#include "bitboard.h"
#include "types.h"

void printBitboard(Board bitboard);

void printMove(struct Move move);

void printCBoard(struct CBoard board);

void numToSquare(int n, char *sq);

#endif // #ifndef PRINTER_INCLUDE
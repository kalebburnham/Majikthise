#include "bitboard.h"

struct CBoard generateBoard() {
	struct CBoard board;

	board.whitePawns = SECOND_RANK;
	board.whiteKnights = 0x42;
	board.whiteBishops = 0x24;
	board.whiteRooks = 0x81;
	board.whiteQueens = 0x08;
	board.whiteKing = 0x10;

	board.blackPawns = SEVENTH_RANK;
	board.blackKnights = board.whiteKnights << 56;
	board.blackBishops = board.whiteBishops << 56;
	board.blackRooks = board.whiteRooks << 56;
	board.blackQueens = board.whiteQueens << 56;
	board.blackKing = board.whiteKing << 56;

	return board;
}

/** Return number of 1-bits from a board.
https://www.chessprogramming.org/Population_Count#BrianKernighansway
*/
int populationCount(Board board) {
	int count = 0;
    while (board) {
        count++;
        board &= board - 1; // reset LS1B
    }
    return count;
}

/* Returns the bit index of the LSB. 
https://www.chessprogramming.org/BitScan#Index_of_LS1B_by_Popcount
*/
int bitScanForward(Board b) {
    assert (b != 0);
    return populationCount( (b & -b) - 1 );
}

/** 
From https://www.chessprogramming.org/Bitboard_Serialization#Converting_Sets_to_Lists
Returns the population count of the board.
*/
int multipleBitScanForward(Board b, int *list) {
    if (b) do {
        int idx = bitScanForward(b);
        *list++ = idx;
    } while (b &= b-1);
    return populationCount(b);
}


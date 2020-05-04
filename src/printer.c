#include "printer.h"

void printBitboard(Board bitboard) {
	for(int row=7; row>=0; row--){
		for (int file=0; file < 8; file++) {
			char c = ((bitboard >> (row*8+file)) & 1LL)? '1' : '0';
			putchar(c);
		}
		putchar('\n');
    }
}

void printCBoard(struct CBoard board) {
	Board whiteBoard = board.whitePawns | board.whiteKnights | board.whiteBishops | board.whiteRooks | board.whiteQueens | board.whiteKing;
	Board blackBoard = board.blackPawns | board.blackKnights | board.blackBishops | board.blackRooks | board.blackQueens | board.blackKing;
	printBitboard(whiteBoard | blackBoard);
}
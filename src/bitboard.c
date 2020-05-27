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

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

void printMove(struct Move move) {
	Board from_bb = 1UL << move.from;
	Board to_bb = 1UL << move.to;

	char from_sq[2];
	char to_sq[2];

	numToSquare(move.from, from_sq);
	numToSquare(move.to, to_sq);

	printf("From %.2s     To %.2s\n", from_sq, to_sq);
    for(int row=7; row>=0; row--){
		for (int file=0; file < 8; file++) {
			char c = ((from_bb >> (row*8+file)) & 1LL)? '1' : '0';
			putchar(c);
		}

		printf("%s", "    ");

		for (int file=0; file < 8; file++) {
			char c = ((to_bb >> (row*8+file)) & 1LL)? '1' : '0';
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

void numToSquare(int n, char *sq) {
	char *files = "ABCDEFGH";
	char *ranks = "12345678";

	sq[0] = files[n%8];
	sq[1] = ranks[n/8];
}
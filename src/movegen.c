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

Board northOne(Board b) { return (b << 8); }
Board southOne(Board b) { return (b >> 8); }

void generateMovesFromPos(struct Position *pos) {

}

void wGenerateAllMoves(struct Position *pos) {

	if (pos->sideToMove == WHITE) {
		struct Move wAllPawnMoves[122] = {0};
		wGenerateAllPawnMoves(pos, wAllPawnMoves);
		/*wGenerateAllBishopMoves();
		wGenerateAllKnightMoves();
		wGenerateAllRookMoves();
		wGenerateAllQueenMoves();
		wGenerateAllKingMoves();*/
	} else {

	}
// Pawn moves
// Pawn double moves
// Pawn attacks
// Pawn promotions

// En Passant captures
// Bishop moves/attacks
// Knight moves/attacks
// Rook moves/attacks
// Queen moves/attacks
// King moves/attacks
}

void bGenerateAllMoves() {

}

/* Moves array should be 13 * 2 Moves wide. 
Returns the number of moves recorded in the moves array. */
int wGenerateBishopMoves(struct CBoard b, struct Move *moves) {
	Board bishopBitboards[2] = {0};
	int n = singularize(b.whiteBishops, bishopBitboards);
	
	int movesIdx = 0;
	enum Square fromSquare;
	enum Square toSquare;
	int flag;
	// When multiple bishops are on the board, this stores the count of moves recorded
	// by bishops already calculated. This helps keep count in the condition of the
	// nested for loop.
	int otherMovesSaved = 0; 

	for (int i=0; i < n; i++) {
		fromSquare = BSR(bishopBitboards[i]);
		
		Board blockers = (WHITE_BOARD(b) | BLACK_BOARD (b));
		Board attackedSquares = bishopAttacks(fromSquare, blockers);
		// Remove squares with white pieces.
		attackedSquares &= ~(WHITE_BOARD(b));

		int numAttackedSquares = POPCOUNT(attackedSquares);
		for (movesIdx; movesIdx < otherMovesSaved + numAttackedSquares; movesIdx++) {
			toSquare = BSF(attackedSquares);
			attackedSquares &= ~(0x01ULL << toSquare);

			if ((0x01ULL << toSquare) & BLACK_BOARD(b)) {
				flag = 0x04;
			} else {
				flag = 0x00;
			}

			struct Move m = { .from=fromSquare, .to=toSquare, .flag=flag };
			moves[movesIdx] = m;
		}

		otherMovesSaved += movesIdx;
	}

	return otherMovesSaved;
}

int bGenerateBishopMoves(struct CBoard b, struct Move *moves) {
	return 1;
}

/* Generate the possible bishop attacks using the classical approach. 
This technique and code is copied with a small modification from 
https://rhysre.net/2019/01/15/magic-bitboards.html */
Board bishopAttacks(enum Square sq, Board blockers) {

	Board nw_attacks = rays[NORTH_WEST][sq];
	if (rays[NORTH_WEST][sq] & blockers) {
    	int blockerIndex = BSF(rays[NORTH_WEST][sq] & blockers);
    	nw_attacks &= ~rays[NORTH_WEST][blockerIndex];
  	}

	Board ne_attacks = rays[NORTH_EAST][sq];
  	if (rays[NORTH_EAST][sq] & blockers) {
   		int blockerIndex = BSF(rays[NORTH_EAST][sq] & blockers);
    	ne_attacks &= ~rays[NORTH_EAST][blockerIndex];
  	}

	Board se_attacks = rays[SOUTH_EAST][sq];
	if (rays[SOUTH_EAST][sq] & blockers) {
		int blockerIndex = BSR(rays[SOUTH_EAST][sq] & blockers);
		se_attacks &= ~rays[SOUTH_EAST][blockerIndex];
	}

	Board sw_attacks = rays[SOUTH_WEST][sq];
	if (rays[SOUTH_WEST][sq] & blockers) {
		int blockerIndex = BSR(rays[SOUTH_WEST][sq] & blockers);
		sw_attacks &= ~rays[SOUTH_WEST][blockerIndex];
	}

	return nw_attacks | ne_attacks | se_attacks | sw_attacks;
}

Board rookAttacks(enum Square sq, Board blockers) {

	Board north_attacks = rays[NORTH][sq];
	if (rays[NORTH][sq] & blockers) {
    	int blockerIndex = BSF(rays[NORTH][sq] & blockers);
    	north_attacks &= ~rays[NORTH][blockerIndex];
  	}

	Board east_attacks = rays[EAST][sq];
  	if (rays[EAST][sq] & blockers) {
   		int blockerIndex = BSF(rays[EAST][sq] & blockers);
    	east_attacks &= ~rays[EAST][blockerIndex];
  	}

	Board south_attacks = rays[SOUTH][sq];
	if (rays[SOUTH][sq] & blockers) {
		int blockerIndex = BSR(rays[SOUTH][sq] & blockers);
		south_attacks &= ~rays[SOUTH][blockerIndex];
	}

	Board west_attacks = rays[WEST][sq];
	if (rays[WEST][sq] & blockers) {
		int blockerIndex = BSR(rays[WEST][sq] & blockers);
		west_attacks &= ~rays[WEST][blockerIndex];
	}

	return north_attacks | east_attacks | south_attacks | west_attacks;
}

Board queenAttacks(enum Square sq, Board blockers) {
	return bishopAttacks(sq, blockers) | rookAttacks(sq, blockers);
}

Board kingAttacks(enum Square sq) {
    Board b = 1ULL << sq;
    return ((b << 1) & ~A_FILE) | ((b >> 1) & ~H_FILE) | b << 8 | b >> 8 | noWe(b) | noEa(b) | soWe(b) | soEa(b);
}

/* This needs to be modified if en passant is considered. */
Board pawnAttacks(Board pawns, enum Color c) {
	if (c == WHITE) {
		return noWe(pawns) | noEa(pawns);
	} else {
		return soWe(pawns) | soEa(pawns);
	}
}

/* Moves array should have 122 open spots. */
int wGenerateAllPawnMoves(struct Position *pos, struct Move *moves) {
    struct Move singlePawnPushMoves[8] = {0};
	struct Move doublePawnPushMoves[8] = {0};
	struct Move pawnPromotions[32] = {0};
	struct Move pawnPromotionAndCaptureMoves[56] = {0};
	struct Move pawnCaptures[16] = {0};
	struct Move enPassantCaptureMoves[2] = {0};

	int numSinglePawnPushMoves = wGeneratePawnPushMoves(pos->board, singlePawnPushMoves);
	int numDoublePawnPushMoves = wGenerateDoublePawnPushMoves(pos->board, doublePawnPushMoves);
	int numPawnPromotionMoves = wGeneratePawnPromotionMoves(pos->board, pawnPromotions);
	int numPawnPromotionAndCaptureMoves= wGeneratePawnPromotionAndCaptureMoves(pos->board, pawnPromotionAndCaptureMoves);
	int numPawnCaptureMoves = wGeneratePawnCaptures(pos->board, pawnCaptures);
	int numEnPassantCaptureMoves = wGenerateEnPassantPawnMoves(pos->board, pos->epTargetSquare, enPassantCaptureMoves);

	int currIdx = 0;
	for (int i=0; i < numSinglePawnPushMoves; i++) { moves[currIdx++] = singlePawnPushMoves[i]; }
	for (int i=0; i < numDoublePawnPushMoves; i++) { moves[currIdx++] = doublePawnPushMoves[i]; }
	for (int i=0; i < numPawnPromotionMoves; i++) { moves[currIdx++] = pawnPromotions[i]; }
	for (int i=0; i < numPawnPromotionAndCaptureMoves; i++) { moves[currIdx++] = pawnPromotionAndCaptureMoves[i]; }
	for (int i=0; i < numPawnCaptureMoves; i++) { moves[currIdx++] = pawnCaptures[i]; }
	for (int i=0; i < numEnPassantCaptureMoves; i++) { moves[currIdx] = enPassantCaptureMoves[i]; }

	// Return total number of moves.
	return currIdx;
}

/* Moves array should have 122 open spots. */
int bGenerateAllPawnMoves(struct Position *pos, struct Move *moves) {
    struct Move singlePawnPushMoves[8] = {0};
	struct Move doublePawnPushMoves[8] = {0};
	struct Move pawnPromotions[32] = {0};
	struct Move pawnPromotionAndCaptureMoves[56] = {0};
	struct Move pawnCaptures[16] = {0};
	struct Move enPassantCaptureMoves[2] = {0};

	int numSinglePawnPushMoves = bGeneratePawnPushMoves(pos->board, singlePawnPushMoves);
	int numDoublePawnPushMoves = bGenerateDoublePawnPushMoves(pos->board, doublePawnPushMoves);
	int numPawnPromotionMoves = bGeneratePawnPromotionMoves(pos->board, pawnPromotions);
	int numPawnPromotionAndCaptureMoves= bGeneratePawnPromotionAndCaptureMoves(pos->board, pawnPromotionAndCaptureMoves);
	int numPawnCaptureMoves = bGeneratePawnCaptures(pos->board, pawnCaptures);
	int numEnPassantCaptureMoves = bGenerateEnPassantPawnMoves(pos->board, pos->epTargetSquare, enPassantCaptureMoves);

	int currIdx = 0;
	for (int i=0; i < numSinglePawnPushMoves; i++) { moves[currIdx++] = singlePawnPushMoves[i]; }
	for (int i=0; i < numDoublePawnPushMoves; i++) { moves[currIdx++] = doublePawnPushMoves[i]; }
	for (int i=0; i < numPawnPromotionMoves; i++) { moves[currIdx++] = pawnPromotions[i]; }
	for (int i=0; i < numPawnPromotionAndCaptureMoves; i++) { moves[currIdx++] = pawnPromotionAndCaptureMoves[i]; }
	for (int i=0; i < numPawnCaptureMoves; i++) { moves[currIdx++] = pawnCaptures[i]; }
	for (int i=0; i < numEnPassantCaptureMoves; i++) { moves[currIdx] = enPassantCaptureMoves[i]; }

	// Return total number of moves.
	return currIdx;
}

int wGeneratePawnPushMoves(struct CBoard board, struct Move *moves) {
	int from;
	int to;
	int numMoves = 0;
	
	Board occupied = WHITE_BOARD(board) | BLACK_BOARD(board);
	Board toBoard = northOne(board.whitePawns) & ~occupied;
	Board eligiblePawns = southOne(toBoard);

	Board fromSingles[8] = {0};
	Board toSingles[8] = {0};

	int n = singularize(eligiblePawns, fromSingles);
	singularize(toBoard, toSingles);

	
	for (int i=0; i < n; i++) {
		from = BSF(fromSingles[i]);
		to = BSF(toSingles[i]);
		struct Move m = { .from=from, .to=to, .flag=0x00 };
		
		// Check for pawn moving to eigth rank
		if (m.to < SQ_A8) {
			moves[i] = m;
			numMoves++;
		}
	}

	return numMoves;
}

int wGenerateDoublePawnPushMoves(struct CBoard board, struct Move *moves) {
	int from;
	int to;
	int numMoves = 0;

	Board occupied = WHITE_BOARD(board) | BLACK_BOARD(board);
	// Eligible pawns are those on the second rank that can move forward two
	// spaces without encountering an occupied square.
	Board toBoard = northOne(northOne(SECOND_RANK & board.whitePawns) & ~occupied) & ~occupied;
	Board eligiblePawns = southOne(southOne(toBoard));

	Board fromSingles[8] = {0};
	Board toSingles[8] = {0};

	int n = singularize(eligiblePawns, fromSingles);
	singularize(toBoard, toSingles);

	for (int i=0; i < n; i++) {
		from = BSF(fromSingles[i]);
		to = BSF(toSingles[i]);
		moves[i].from = from;
		moves[i].to = to;
		moves[i].flag = 0x01;
		numMoves++;
	}

	return numMoves;
}

int bGeneratePawnPushMoves(struct CBoard board, struct Move *moves) {
	int from;
	int to;
	int numMoves = 0;
	
	Board occupied = WHITE_BOARD(board) | BLACK_BOARD(board);
	Board toBoard = southOne(board.blackPawns) & ~occupied;
	Board eligiblePawns = northOne(toBoard);

	Board fromSingles[8] = {0};
	Board toSingles[8] = {0};

	int n = singularize(eligiblePawns, fromSingles);
	singularize(toBoard, toSingles);

	for (int i=0; i < n; i++) {
		from = BSF(fromSingles[i]);
		to = BSF(toSingles[i]);
		struct Move m = { .from=from, .to=to, .flag=0x00 };

		// Check for pawn moving to first rank.
		if (m.to > SQ_H1) {
			moves[i] = m;
			numMoves++;
		}
	}

	return numMoves;
}

int bGenerateDoublePawnPushMoves(struct CBoard board, struct Move *moves) {
	int from;
	int to;
	int numMoves = 0;
	
	Board occupied = WHITE_BOARD(board) | BLACK_BOARD(board);
	Board toBoard = southOne(southOne(SEVENTH_RANK & board.blackPawns) & ~occupied) & ~occupied;
	Board eligiblePawns = northOne(northOne(toBoard));

	Board fromSingles[8] = {0};
	Board toSingles[8] = {0};

	int n = singularize(eligiblePawns, fromSingles);
	singularize(toBoard, toSingles);

	for (int i=0; i < n; i++) {
		from = BSF(fromSingles[i]);
		to = BSF(toSingles[i]);
		moves[i].from = from;
		moves[i].to = to;
		moves[i].flag = 0x01;
		numMoves++;
	}

	return numMoves;
}




// Needs testing
int wGenerateKnightMoves(struct CBoard b, struct Move *moves) {
	enum Square from;
	enum Square to;
	int flag = 0x00;
	int n = 0; // Number of moves

	if (b.whiteKnights == 0) { return 0; }

    Board knights[2] = {0};
    singularize(b.whiteKnights, knights);

	for (int i = 0; i < 2; i++) {
		if (knights[i] == 0) {
			continue;
		}

		enum Square currSquare = BSF(knights[i]);
		from = currSquare;
		Board attackedSquares = knightAttacks(currSquare);

		Board attackedSquaresBoards[8];
		int numAttackedSquares = singularize(attackedSquares, attackedSquaresBoards);

		for (int j=0; j < numAttackedSquares; j++) {

			if (attackedSquaresBoards[j] & WHITE_BOARD(b)) {
				// The attacked square is occupied by a white piece.
				continue;
			}

			to = BSF(attackedSquaresBoards[j]);

			if (attackedSquaresBoards[j] & BLACK_BOARD(b)) {
				flag = 0x04;
			} else {
				flag = 0x00;
			}

			struct Move m = { .from=from, .to=to, .flag=flag };
			moves[n++] = m;
		}
	}

	return n;
}

int bGenerateKnightMoves(struct CBoard b, struct Move *moves) {
	enum Square from;
	enum Square to;
	int flag = 0x00;
	int n = 0; // Number of moves

	if (b.blackKnights == 0) { return 0; }

	Board knights[2] = {0};
	singularize(b.blackKnights, knights);

	for (int i=0; i < 2; i++) {
		if (knights[i] == 0) {
			continue;
		}

		enum Square currSquare = BSF(knights[i]);
		from = currSquare;
		Board attackedSquares = knightAttacks(currSquare);

		Board attackedSquaresBoards[8];
		int numAttackedSquares = singularize(attackedSquares, attackedSquaresBoards);

		for (int j=0; j < numAttackedSquares; j++) {

			if (attackedSquaresBoards[j] & BLACK_BOARD(b)) {
				// The attacked square is occupied by a white piece.
				continue;
			}

			to = BSF(attackedSquaresBoards[j]);

			if (attackedSquaresBoards[j] & WHITE_BOARD(b)) {
				flag = 0x04;
			} else {
				flag = 0x00;
			}

			struct Move m = { .from=from, .to=to, .flag=flag };
			moves[n++] = m;
		}
	}

	return n;
}

Board knightAttacks(enum Square sq) {
    Board board = 1ULL << sq;
	return noNoEa(board) | noEaEa(board) | soEaEa(board) | soSoEa(board) | noNoWe(board) | noWeWe(board) | soWeWe(board) | soSoWe(board);
}

/** Generate the moves for a board with a single knight. */
int knightMoves(Board board, struct Move *moves) {
	// A knight has 8 potential moves.
    int to;

	uint8_t from = BSF(board);
	Board to_board = knightAttacks(board);

    Board singles[8] = {0};
    int n = singularize(to_board, singles);

    for (int idx=0; idx < n; idx++) {
        to = BSF(singles[idx]);
        struct Move m = { .from=from, .to=to, .flag=0x00 };
        moves[idx] = m;
    }

    return n;
}

int wGeneratePawnCaptures(struct CBoard board, struct Move *moves) {
	int from;
	int to;
	int n = 0;

	Board whitePawnBoards[16] = {0};
	// Eight-rank pawn captures are handled in wGeneratePromotionAndCaptureMoves.
	int numBoards = singularize((board.whitePawns & ~SEVENTH_RANK), whitePawnBoards);

	for (int i=0; i < numBoards; i++) {
		if ((noWe(whitePawnBoards[i]) & BLACK_BOARD(board)) > 0) {
			from = BSF(whitePawnBoards[i]);
			to = from + 7;
			struct Move m = { .from=from, .to=to, .flag=0x04 };
			moves[n] = m;
			n++;
		}
		if ((noEa(whitePawnBoards[i]) & BLACK_BOARD(board)) > 0) {
			from = BSF(whitePawnBoards[i]);
			to = from + 9;
			struct Move m = { .from=from, .to=to, .flag=0x04 };
			moves[n] = m;
			n++;
		}
	}

	return n;
}

int bGeneratePawnCaptures(struct CBoard board, struct Move *moves) {
	int from;
	int to;
	int n = 0;

	Board blackPawnBoards[16] = {0};
	// First-rank pawn captures are handled in bGeneratePromotionAndCaptureMoves.
	int numBoards = singularize((board.blackPawns & ~SECOND_RANK), blackPawnBoards);

	for (int i=0; i < numBoards; i++) {
		if ((soWe(blackPawnBoards[i]) & WHITE_BOARD(board)) > 0) {
			from = BSF(blackPawnBoards[i]);
			to = from - 9;
			struct Move m = { .from=from, .to=to, .flag=0x04 };
			moves[n] = m;
			n++;
		}
		if ((soEa(blackPawnBoards[i]) & WHITE_BOARD(board)) > 0) {
			from = BSF(blackPawnBoards[i]);
			to = from - 9;
			struct Move m = { .from=from, .to=to, .flag=0x04 };
			moves[n] = m;
			n++;
		}
	}

	return n;
}

int wGenerateEnPassantPawnMoves(struct CBoard board, enum Square epTargetSquare, struct Move *moves) {
	int from;
	int to;
	int n = 0;

	if (epTargetSquare == SQ_NONE) {
		return 0;
	}

	if (epTargetSquare == SQ_A6) {
		// The only square a white pawn can attack from is B5
		if (board.whitePawns & (1ULL << SQ_B5)) {
			from = SQ_B5;
			to = SQ_A6;
			struct Move m = { .from=from, .to=to, .flag=0x05 };
			moves[0] = m;
			n++;
		}

	} else if (epTargetSquare == SQ_H6) {
		// The only square a white pawn can attack from is G5
		if (board.whitePawns & (1ULL << SQ_G5)) {
			from = SQ_G5;
			to = SQ_H6;
			struct Move m = { .from=from, .to=to, .flag=0x05 };
			moves[0] = m;
			n++;
		}
	} else {
		// There are two potential 'attacking from' squares
		if (board.whitePawns & (1ULL << (epTargetSquare-9))) {
			from = (epTargetSquare-9);
			to = epTargetSquare;
			struct Move m = {.from=from, .to=to, .flag=0x05 };
			moves[n] = m;
			n++;
		}

		if (board.whitePawns & (1ULL << (epTargetSquare-7))) {
			from = (epTargetSquare-7);
			to = epTargetSquare;
			struct Move m = {.from=from, .to=to, .flag=0x05 };
			moves[n] = m;
			n++;
		}
	}

	return n;
}

int bGenerateEnPassantPawnMoves(struct CBoard board, enum Square epTargetSquare, struct Move *moves) {
	int from;
	int to;
	int n = 0;

	if (epTargetSquare == SQ_NONE) {
		return 0;
	}

	if (epTargetSquare == SQ_A3) {
		// The only square a white pawn can attack from is B4
		if (board.whitePawns & (1ULL << SQ_B4)) {
			from = SQ_B4;
			to = SQ_A3;
			struct Move m = { .from=from, .to=to, .flag=0x05 };
			printf("%d", from);
			moves[0] = m;
			n++;
		}

	} else if (epTargetSquare == SQ_H3) {
		// The only square a white pawn can attack from is G5
		if (board.whitePawns & (1ULL << SQ_G4)) {
			from = SQ_G4;
			to = SQ_H3;
			struct Move m = { .from=from, .to=to, .flag=0x05 };
			moves[0] = m;
			n++;
		}
	} else {
		// There are two potential 'attacking from' squares
		if (board.whitePawns & (1ULL << (epTargetSquare+7))) {
			from = (epTargetSquare+7);
			to = epTargetSquare;
			struct Move m = {.from=from, .to=to, .flag=0x05 };
			moves[n] = m;
			n++;
		}

		if (board.whitePawns & (1ULL << (epTargetSquare+9))) {
			from = (epTargetSquare+9);
			to = epTargetSquare;
			struct Move m = {.from=from, .to=to, .flag=0x05 };
			moves[n] = m;
			n++;
		}
	}

	return n;
}

/* Moves array should have 32 positions. There are 8 moves from E7 to E8 with
4 promotions each. */
int wGeneratePawnPromotionMoves(struct CBoard board, struct Move *moves) {
	int n = 0;

	if ((board.whitePawns & SEVENTH_RANK) == 0) {
		return 0;
	}

	Board seventhRankPawns = board.whitePawns & SEVENTH_RANK;
	Board seventhRankBoards[8] = {0};
	int numSeventhRankPawns = singularize(seventhRankPawns, seventhRankBoards);

	for (int i=0; i < numSeventhRankPawns; i++) {
		if (northOne(seventhRankBoards[i]) & ~BLACK_BOARD(board)) {
			int from = BSF(seventhRankBoards[i]);
			int to = BSF(northOne(seventhRankBoards[i]));
			struct Move m0 = { .from=from, .to=to, .flag=0x08 };
			struct Move m1 = { .from=from, .to=to, .flag=0x09 };
			struct Move m2 = { .from=from, .to=to, .flag=0x0A };
			struct Move m3 = { .from=from, .to=to, .flag=0x0B };
			moves[n] = m0;
			moves[n+1] = m1;
			moves[n+2] = m2;
			moves[n+3] = m3;
			n = n + 4;
		}
	}

	return n;
}

/* Moves array should have 32 positions. There are 8 moves from ranks 7 to 8 with
4 promotions each. */
int bGeneratePawnPromotionMoves(struct CBoard board, struct Move *moves) {
	int n = 0;

	if ((board.blackPawns & SECOND_RANK) == 0) {
		return 0;
	}

	Board secondRankPawns = board.blackPawns & SECOND_RANK;
	Board secondRankBoards[8] = {0};
	int numSecondRankPawns = singularize(secondRankPawns, secondRankBoards);

	for (int i=0; i < numSecondRankPawns; i++) {
		if (southOne(secondRankBoards[i]) & ~WHITE_BOARD(board)) {
			int from = BSF(secondRankBoards[i]);
			int to = BSF(southOne(secondRankBoards[i]));
			struct Move m0 = { .from=from, .to=to, .flag=0x08 };
			struct Move m1 = { .from=from, .to=to, .flag=0x09 };
			struct Move m2 = { .from=from, .to=to, .flag=0x0A };
			struct Move m3 = { .from=from, .to=to, .flag=0x0B };
			moves[n] = m0;
			moves[n+1] = m1;
			moves[n+2] = m2;
			moves[n+3] = m3;
			n = n + 4;
		}
	}

	return n;
}

/* Moves array should have 56 positions. There are 14 advances to the eighth rank
and 4 promotion types. */
int wGeneratePawnPromotionAndCaptureMoves(struct CBoard board, struct Move *moves) {
	int n = 0;

	if ((board.whitePawns & SEVENTH_RANK) == 0) {
		return 0;
	}

	Board seventhRankPawns = board.whitePawns & SEVENTH_RANK;
	Board seventhRankBoards[8] = {0};
	int numSeventhRankPawns = singularize(seventhRankPawns, seventhRankBoards);

	for (int i=0; i < numSeventhRankPawns; i++) {
		if (noWe(seventhRankBoards[i]) & BLACK_BOARD(board)) {

			int from = BSF(seventhRankBoards[i]);
			int to = BSF(noWe(seventhRankBoards[i]));
			struct Move m0 = { .from=from, .to=to, .flag=0x0C };
			struct Move m1 = { .from=from, .to=to, .flag=0x0D };
			struct Move m2 = { .from=from, .to=to, .flag=0x0E };
			struct Move m3 = { .from=from, .to=to, .flag=0x0F };
			moves[n] = m0;
			moves[n+1] = m1;
			moves[n+2] = m2;
			moves[n+3] = m3;
			n = n + 4;
		}
		if (noEa(seventhRankBoards[i]) & BLACK_BOARD(board)) {
			int from = BSF(seventhRankBoards[i]);
			int to = BSF(noEa(seventhRankBoards[i]));
			struct Move m0 = { .from=from, .to=to, .flag=0x0C };
			struct Move m1 = { .from=from, .to=to, .flag=0x0D };
			struct Move m2 = { .from=from, .to=to, .flag=0x0E };
			struct Move m3 = { .from=from, .to=to, .flag=0x0F };
			moves[n] = m0;
			moves[n+1] = m1;
			moves[n+2] = m2;
			moves[n+3] = m3;
			n = n + 4;
		}
	}

	return n;
}

/* Moves array should have 56 positions. There are 14 advances to the eighth rank
and 4 promotion types. */
int bGeneratePawnPromotionAndCaptureMoves(struct CBoard board, struct Move *moves) {
	int n = 0;

	if ((board.blackPawns & SECOND_RANK) == 0) {
		return 0;
	}

	Board secondRankPawns = board.blackPawns & SECOND_RANK;
	Board secondRankBoards[8] = {0};
	int numSecondRankPawns = singularize(secondRankPawns, secondRankBoards);

	for (int i=0; i < numSecondRankPawns; i++) {
		if (soWe(secondRankBoards[i]) & WHITE_BOARD(board)) {

			int from = BSF(secondRankBoards[i]);
			int to = BSF(soWe(secondRankBoards[i]));
			struct Move m0 = { .from=from, .to=to, .flag=0x0C };
			struct Move m1 = { .from=from, .to=to, .flag=0x0D };
			struct Move m2 = { .from=from, .to=to, .flag=0x0E };
			struct Move m3 = { .from=from, .to=to, .flag=0x0F };
			moves[n] = m0;
			moves[n+1] = m1;
			moves[n+2] = m2;
			moves[n+3] = m3;
			n = n + 4;
		}
		if (soEa(secondRankBoards[i]) & WHITE_BOARD(board)) {
			int from = BSF(secondRankBoards[i]);
			int to = BSF(soEa(secondRankBoards[i]));
			struct Move m0 = { .from=from, .to=to, .flag=0x0C };
			struct Move m1 = { .from=from, .to=to, .flag=0x0D };
			struct Move m2 = { .from=from, .to=to, .flag=0x0E };
			struct Move m3 = { .from=from, .to=to, .flag=0x0F };
			moves[n] = m0;
			moves[n+1] = m1;
			moves[n+2] = m2;
			moves[n+3] = m3;
			n = n + 4;
		}
	}

	return n;
}

void updateFlagEnPassant(enum Square epTargetSquare, struct Move *moves, int numMoves) {
	if (epTargetSquare == SQ_NONE) {
		return;
	}

	for (int i = 0; i < numMoves; i++) {
		if (moves[i].to == epTargetSquare) {
			moves[i].flag = 0x05;
		}
	}
}

/* Given any bitboard, return a list of bitboards with only one piece per board. */
int singularize(Board b, Board *singles) {
    int pos;
    int idx = 0;

    while (b) {
        pos = BSF(b);
        singles[idx++] = 1UL << pos;
        b ^= 1UL << pos;
    }

    return idx;
}


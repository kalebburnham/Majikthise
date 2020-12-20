#include <stdlib.h>
#include "ctest.h"
#include "../src/movegen.h"
#include "../src/printer.h"
#include "../src/rays.h"

#include <time.h>

CTEST(generateBoard, generateBoard) {
    struct CBoard b = generateBoard();
    ASSERT_EQUAL(0x81 , b.whiteRooks);
    ASSERT_EQUAL(0x42, b.whiteKnights);
    ASSERT_EQUAL(0X24, b.whiteBishops);
    ASSERT_EQUAL(0x08, b.whiteQueens);
    ASSERT_EQUAL(0x10, b.whiteKing);
    ASSERT_EQUAL(SECOND_RANK, b.whitePawns);

    ASSERT_EQUAL(0x8100000000000000, b.blackRooks);
    ASSERT_EQUAL(0x4200000000000000, b.blackKnights);
    ASSERT_EQUAL(0X2400000000000000, b.blackBishops);
    ASSERT_EQUAL(0x0800000000000000, b.blackQueens);
    ASSERT_EQUAL(0x1000000000000000, b.blackKing);
    ASSERT_EQUAL(SEVENTH_RANK, b.blackPawns);
}

CTEST(bishop_attacks, sq_d3) {
    /*
    BLOCKERS

    00000000
    00000000
    10000000
    00000000
    00000000
    000B0000
    00000000
    01000100

    EXPECTED

    00000000
    00000001
    10000010
    01000100
    00101000
    000B0000
    00101000
    01000100
    */
    initRays();
    enum Square sq = SQ_D3;
    Board blockers = 0x10000000022;
    Board exp = 0x80412214001422;
    ASSERT_EQUAL(exp, bishopAttacks(sq, blockers));
    
}

CTEST(bishop_attacks, sq_a1_blocked) {
    /*
    BLOCKERS

    00000000
    00000000
    00000000
    00000000
    00000000
    00000000
    01000000
    B0000000

    EXPECTED: The same board.
    */
    initRays();
    enum Square sq = SQ_A1;
    Board blockers = 0x200;
    Board exp = 0x200;
    ASSERT_EQUAL(exp, bishopAttacks(sq, blockers));
}

CTEST(rook_attacks, sq_d3) {
    /*
    BLOCKERS

    00010000
    00010000
    00000000
    00000000
    00000000
    001R0010
    00000000
    00000000

    EXPECTED
    00000000
    00010000
    00010000
    00010000
    00010000
    00101110
    00010000
    00010000
    */

    initRays();
    enum Square sq = SQ_D3;
    Board blockers = 0x0808000000440000;
    Board exp = 0x0008080808740808;
    ASSERT_EQUAL(exp, rookAttacks(sq, blockers));
}

CTEST(rook_attacks, sq_a8_blocked) {
    /*
    BLOCKERS

    00000000
    00000000
    00000000
    00000000
    00000000
    00000000
    00000001
    0000001R

    EXPECTED: The same board
    */
    initRays();
    enum Square sq = SQ_H1;
    Board blockers = 0x8040;
    Board exp = 0x8040;
    ASSERT_EQUAL(exp, rookAttacks(sq, blockers));
}

CTEST(queen_attacks, sq_f4) {
    /*
    BLOCKERS

    00000000
    00100000
    00100100
    00100010
    00100Q11
    00000000
    00110000
    01100000

    EXPECTED

    00000000
    00100000
    00010100
    00001110
    00111Q10
    00001110
    00010101
    00000100
    */
    initRays();
    enum Square sq = SQ_F4;
    Board blockers = 0x00042444C4000C06;
    Board exp = 0x000428705C70A820;
    ASSERT_EQUAL(exp, queenAttacks(sq, blockers));
}

CTEST(knight_attacks, center_of_board) {
    /*
    Square: E5

    EXPECTED

    00000000
    00010100
    00100010
    00000000
    00100010
    00010100
    00000000
    00000000
    */

    enum Square sq = SQ_E5;
    Board exp = 0x0028440044280000;
    ASSERT_EQUAL(exp, knightAttacks(sq));
}

CTEST(knight_attacks, corner_of_board) {
    /*
    Square: G2

    EXPECTED

    00000000
    00000000
    00000000
    00000000
    00000101
    00001000
    000000K0
    00001000
    */

    enum Square sq = SQ_G2;
    Board exp = 0x00000000A0100010;
    ASSERT_EQUAL(exp, knightAttacks(sq));
}

CTEST(king_attacks, center_of_board) {
    /*
    Square: C3

    EXPECTED

    00000000
    00000000
    00000000
    00000000
    01110000
    01010000
    01110000
    00000000
    */

    enum Square sq = SQ_C3;
    Board exp = 0x000000000E0A0E00;
    ASSERT_EQUAL(exp, kingAttacks(sq));
}

CTEST(king_attacks, corner_of_board) {
    /*
    Square: H1

    EXPECTED

    00000000
    00000000
    00000000
    00000000
    00000000
    00000000
    00000011
    00000010
    */

    enum Square sq = SQ_H1;
    Board exp = 0xC040;
    ASSERT_EQUAL(exp, kingAttacks(sq));
}

CTEST(pawnPushes, wPawnPush_noBlockers) {
    /*
    Place unobstructed white pawns on A2 and D3 and generate their single
    space pushes.
    Since there can be up to 8 pawns on the board for white, the move arrays
    are of length 8.

    00000000
    00000000
    00000000
    00000000
    00000000
    00010000
    10000000
    00000000
    */
    struct Move emptyMove = { .from=0, .to=0, .flag=0 };
    struct CBoard board = generateBoard();
    board.whitePawns = 0x080100;
    struct Move moves[8] = {emptyMove, emptyMove, emptyMove, emptyMove,
                            emptyMove, emptyMove, emptyMove, emptyMove};
    int numMoves = wGeneratePawnPushMoves(board, moves);
    struct Move move1 = { .from=SQ_A2, .to=SQ_A3, .flag=0 };
    struct Move move2 = { .from=SQ_D3, .to=SQ_D4, .flag=0 };
    struct Move exp[8] = {move1, move2, emptyMove, emptyMove, emptyMove,
                          emptyMove, emptyMove, emptyMove};
    ASSERT_EQUAL(numMoves, 2);
    for (int i=0; i < 8; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(pawnPushes, wPawnPush_Blockers) {
    /**
    Place an obstructed white pawn on C4 and an unobstructed pawn on A5.
    Only one move should be generated.
    
    00000000
    00000000
    00000000
    P0p00000
    00P00000
    00000000
    00000000
    00000000
     */
    struct Move emptyMove = { .from=0, .to=0, .flag=0 };
    struct CBoard board = generateEmptyBoard();
    board.whitePawns = 0x0104000000;
    board.blackPawns = 0x0400000000;

    struct Move moves[8] = {emptyMove, emptyMove, emptyMove, emptyMove,
                            emptyMove, emptyMove, emptyMove, emptyMove};
    int numMoves = wGeneratePawnPushMoves(board, moves);
    struct Move move1 = { .from=SQ_A5, .to=SQ_A6, .flag=0 };
    struct Move exp[8] = {move1, emptyMove, emptyMove, emptyMove, emptyMove,
                          emptyMove, emptyMove, emptyMove};
    ASSERT_EQUAL(1, numMoves);
    for (int i=0; i < 8; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(pawnPushes, wPawnPush_OnSeventh) {
    /*
    A white pawn on the seventh rank cannot push to the eighth and remain a
    pawn. That case will be handled by wGeneratePawnPromotions.

    Place one pawn on A7. No moves should be returned.
    */
    struct Move emptyMove = { .from=0, .to=0, .flag=0 };
    struct CBoard board = generateEmptyBoard();

    board.whitePawns = 0x0001000000000000;
    struct Move moves[1] = {emptyMove};
    int numMoves = wGeneratePawnPushMoves(board, moves);
    struct Move exp[1] = {emptyMove};
    ASSERT_EQUAL(numMoves, 0);
    ASSERT_EQUAL(moves[0].from, exp[0].from);
    ASSERT_EQUAL(moves[0].to, exp[0].to);
    ASSERT_EQUAL(moves[0].flag, exp[0].flag);
}

CTEST(pawnPushes, bPawnPush_NoBlockers) {
    /** Place unobstructed black pawns on C5 and H3 and generate their single
    space pushes.
    Since there can be up to 8 pawns on the board for black, the move arrays
    are of length 8.

    00000000
    00000000
    00000000
    00100000
    00000000
    00000001
    00000000
    00000000
    */
    struct Move emptyMove = { .from=0, .to=0, .flag=0 };
    struct CBoard board = generateEmptyBoard();

    board.blackPawns = 0x0400800000;
    struct Move moves[8] = {emptyMove, emptyMove, emptyMove, emptyMove,
                            emptyMove, emptyMove, emptyMove, emptyMove};
    int numMoves = bGeneratePawnPushMoves(board, moves);
    struct Move move1 = { .from=SQ_H3, .to=SQ_H2, .flag=0 };
    struct Move move2 = { .from=SQ_C5, .to=SQ_C4, .flag=0 };
    struct Move exp[8] = {move1, move2, emptyMove, emptyMove, emptyMove,
                          emptyMove, emptyMove, emptyMove};
    ASSERT_EQUAL(2, numMoves);
    for (int i=0; i < 8; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(pawnPushes, bPawnPush_Blockers) {
    /** Place an unobstructed black pawn on C5 and an obstructed pawn on H3 and
    generate their single space pushes.

    00000000
    00000000
    00000000
    00p00000
    00000000
    0000000p
    0000000P
    00000000
    */
    struct Move emptyMove = { .from=0, .to=0, .flag=0 };
    struct CBoard board = generateEmptyBoard();

    board.blackPawns = 0x0400800000;
    board.whitePawns = SECOND_RANK;
    struct Move moves[8] = {emptyMove, emptyMove, emptyMove, emptyMove,
                            emptyMove, emptyMove, emptyMove, emptyMove};
    int numMoves = bGeneratePawnPushMoves(board, moves);
    struct Move move1 = { .from=SQ_C5, .to=SQ_C4, .flag=0 };
    struct Move exp[8] = {move1, emptyMove, emptyMove, emptyMove, emptyMove,
                          emptyMove, emptyMove, emptyMove};

    for (int i=0; i < numMoves; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(pawnPushes, bPawnPush_OnSecond) {
    /*
    A black pawn on the seventh rank cannot push to the second and remain a
    pawn. That case will be handled by bGeneratePawnPromotions.

    Place one pawn on A2. No moves should be returned.
    */
    struct Move emptyMove = { .from=0, .to=0, .flag=0 };
    struct CBoard board = generateEmptyBoard();

    board.blackPawns = 0x100;
    struct Move moves[1] = {emptyMove};
    
    int numMoves = bGeneratePawnPushMoves(board, moves);
    struct Move exp[1] = {emptyMove};
    ASSERT_EQUAL(numMoves, 0);
    ASSERT_EQUAL(moves[0].from, exp[0].from);
    ASSERT_EQUAL(moves[0].to, exp[0].to);
    ASSERT_EQUAL(moves[0].flag, exp[0].flag);
}

CTEST(pawnPushes, wDoublePawnPush_NoBlockers) {
    /*
    Place all white pawns on the second rank with no blockers. Verify they all
    move to the fourth rank.
    */
    struct CBoard board = generateEmptyBoard();
    board.whitePawns = SECOND_RANK;

    struct Move moves[8] = {0};

    struct Move exp[8] = { {.from=SQ_A2, .to=SQ_A4, .flag=0x01 },
                           {.from=SQ_B2, .to=SQ_B4, .flag=0x01 },
                           {.from=SQ_C2, .to=SQ_C4, .flag=0x01 },
                           {.from=SQ_D2, .to=SQ_D4, .flag=0x01 },
                           {.from=SQ_E2, .to=SQ_E4, .flag=0x01 },
                           {.from=SQ_F2, .to=SQ_F4, .flag=0x01 },
                           {.from=SQ_G2, .to=SQ_G4, .flag=0x01 },
                           {.from=SQ_H2, .to=SQ_H4, .flag=0x01 }};

    
    int numMoves = wGenerateDoublePawnPushMoves(board, moves);

    ASSERT_EQUAL(8, numMoves);
    for (int i=0; i < 8; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST (pawnPushes, wDoublePawnPush_Blockers) {
    /*
    Place all white pawns on second rank. Put blockers on A3, B3, C4, and D4.
    */
    struct CBoard board = generateEmptyBoard();
    board.whitePawns = SECOND_RANK;

    // Blockers
    board.blackPawns = 0x0C030000;

    struct Move moves[8] = {0};

    struct Move exp[8] = { {.from=SQ_E2, .to=SQ_E4, .flag=0x01 },
                           {.from=SQ_F2, .to=SQ_F4, .flag=0x01 },
                           {.from=SQ_G2, .to=SQ_G4, .flag=0x01 },
                           {.from=SQ_H2, .to=SQ_H4, .flag=0x01 }};

    int numMoves = wGenerateDoublePawnPushMoves(board, moves);

    ASSERT_EQUAL(4, numMoves);
    for (int i=0; i < numMoves; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(pawnPushes, bDoublePawnPush_NoBlockers) {
    struct CBoard board = generateEmptyBoard();
    board.blackPawns = SEVENTH_RANK;

    struct Move moves[8] = {0};

    struct Move exp[8] = { {.from=SQ_A7, .to=SQ_A5, .flag=0x01 },
                           {.from=SQ_B7, .to=SQ_B5, .flag=0x01 },
                           {.from=SQ_C7, .to=SQ_C5, .flag=0x01 },
                           {.from=SQ_D7, .to=SQ_D5, .flag=0x01 },
                           {.from=SQ_E7, .to=SQ_E5, .flag=0x01 },
                           {.from=SQ_F7, .to=SQ_F5, .flag=0x01 },
                           {.from=SQ_G7, .to=SQ_G5, .flag=0x01 },
                           {.from=SQ_H7, .to=SQ_H5, .flag=0x01 }};

    int numMoves = bGenerateDoublePawnPushMoves(board, moves);

    ASSERT_EQUAL(8, numMoves);
    for (int i=0; i < 8; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(pawnPushes, bDoublePawnPush_Blockers) {
    /*
    Place all black pawns on the seventh rank. Blockers are on C6 and E5.
    */
    struct CBoard board = generateEmptyBoard();
    board.blackPawns = SEVENTH_RANK;

    struct Move moves[8] = {0};

    board.blackKnights = 0x4000040000000000;
    board.whiteKnights = 0x1000000000;

    struct Move exp[8] = { {.from=SQ_A7, .to=SQ_A5, .flag=0x01 },
                           {.from=SQ_B7, .to=SQ_B5, .flag=0x01 },
                           {.from=SQ_D7, .to=SQ_D5, .flag=0x01 },
                           {.from=SQ_F7, .to=SQ_F5, .flag=0x01 },
                           {.from=SQ_G7, .to=SQ_G5, .flag=0x01 },
                           {.from=SQ_H7, .to=SQ_H5, .flag=0x01 }};

    int numMoves = bGenerateDoublePawnPushMoves(board, moves);

    ASSERT_EQUAL(6, numMoves);
    for (int i=0; i < 8; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(Captures, wGeneratePawnCaptures) {
    /* B2 captures C3, E4 and G4 capture F5, D7 is not considered. */
    struct CBoard board = generateEmptyBoard();

    board.whitePawns = 1ULL << SQ_B2 | 1ULL << SQ_E4 | 1ULL << SQ_G4 | 1ULL << SQ_D7;
    board.blackPawns = 1ULL << SQ_C3 | 1ULL << SQ_F5;
    board.blackKing = 1ULL << SQ_E8;

    struct Move moves[16] = {0};
    int numMoves = wGeneratePawnCaptures(board, moves);

    struct Move exp[3] = {{ .from=SQ_B2, .to=SQ_C3, .flag=0x04 },
                          { .from=SQ_E4, .to=SQ_F5, .flag=0x04 },
                          { .from=SQ_G4, .to=SQ_F5, .flag=0x04 }};

    ASSERT_EQUAL(3, numMoves);
    for (int i=0; i < 3; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(EnPassant, wGenerateEnPassantPawnMoves_Empty) {
    struct Move moves[2] = {0};

    struct CBoard board = generateEmptyBoard();
    enum Square epTargetSquare = SQ_E6;
    
    board.whitePawns = SECOND_RANK;
    struct Move exp[2] = {0};

    int numMoves = wGenerateEnPassantPawnMoves(board, epTargetSquare, moves);

    ASSERT_EQUAL(0, numMoves);
    for (int i=0; i < 2; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(EnPassant, wGenerateEnPassantPawnMoves_A6) {
    struct Move moves[2] = {0};

    struct CBoard board = generateEmptyBoard();
    enum Square epTargetSquare = SQ_A6;
    board.whitePawns = 1ULL << SQ_B5;

    struct Move exp[2] = { { .from=SQ_B5, .to=SQ_A6, .flag=0x05 },
                           { .from=0, .to=0, .flag=0 }};

    int numMoves = wGenerateEnPassantPawnMoves(board, epTargetSquare, moves);

    ASSERT_EQUAL(1, numMoves);
    for (int i=0; i < 2; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(EnPassant, wGenerateEnPassantPawnMoves_H6) {
    struct Move moves[2] = {0};

    struct CBoard board = generateEmptyBoard();
    enum Square epTargetSquare = SQ_H6;
    board.whitePawns = 1ULL << SQ_G5;

    struct Move exp[2] = { { .from=SQ_G5, .to=SQ_H6, .flag=0x05 },
                           { .from=0, .to=0, .flag=0 }};

    int numMoves = wGenerateEnPassantPawnMoves(board, epTargetSquare, moves);

    ASSERT_EQUAL(1, numMoves);
    for (int i=0; i < 2; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(EnPassant, wGenerateEnPassantPawnMoves_C6) {
    struct Move moves[2] = {0};

    struct CBoard board = generateEmptyBoard();
    enum Square epTargetSquare = SQ_C6;
    board.whitePawns = 1ULL << SQ_B5 | 1ULL << SQ_D5;

    struct Move exp[2] = { { .from=SQ_B5, .to=SQ_C6, .flag=0x05 },
                           { .from=SQ_D5, .to=SQ_C6, .flag=0x05 }};

    int numMoves = wGenerateEnPassantPawnMoves(board, epTargetSquare, moves);

    ASSERT_EQUAL(2, numMoves);
    for (int i=0; i < 2; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(EnPassant, bGenerateEnPassantPawnMoves_Empty) {
    struct Move moves[2] = {0};

    struct CBoard board = generateEmptyBoard();
    enum Square epTargetSquare = SQ_E3;
    
    board.blackPawns = SEVENTH_RANK;
    struct Move exp[2] = {0};

    int numMoves = wGenerateEnPassantPawnMoves(board, epTargetSquare, moves);

    ASSERT_EQUAL(0, numMoves);
    for (int i=0; i < 2; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(EnPassant, bGenerateEnPassantPawnMoves_A3) {
    struct Move moves[2] = {0};

    struct CBoard board = generateEmptyBoard();
    enum Square epTargetSquare = SQ_A3;
    board.whitePawns = 1ULL << SQ_B4;

    struct Move exp[2] = { { .from=SQ_B4, .to=SQ_A3, .flag=0x05 },
                           { .from=0, .to=0, .flag=0 }};

    int numMoves = bGenerateEnPassantPawnMoves(board, epTargetSquare, moves);

    ASSERT_EQUAL(1, numMoves);
    for (int i=0; i < 2; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(EnPassant, bGenerateEnPassantPawnMoves_H3) {
    struct Move moves[2] = {0};

    struct CBoard board = generateEmptyBoard();
    enum Square epTargetSquare = SQ_H3;
    board.whitePawns = 1ULL << SQ_G4;

    struct Move exp[2] = { { .from=SQ_G4, .to=SQ_H3, .flag=0x05 },
                           { .from=0, .to=0, .flag=0 }};

    int numMoves = bGenerateEnPassantPawnMoves(board, epTargetSquare, moves);

    ASSERT_EQUAL(1, numMoves);
    for (int i=0; i < 2; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(EnPassant, bGenerateEnPassantPawnMoves_C3) {
    struct Move moves[2] = {0};

    struct CBoard board = generateEmptyBoard();
    enum Square epTargetSquare = SQ_C3;
    board.whitePawns = 1ULL << SQ_B4 | 1ULL << SQ_D4;

    struct Move exp[2] = { { .from=SQ_B4, .to=SQ_C3, .flag=0x05 },
                           { .from=SQ_D4, .to=SQ_C3, .flag=0x05 }};

    int numMoves = bGenerateEnPassantPawnMoves(board, epTargetSquare, moves);

    ASSERT_EQUAL(2, numMoves);
    for (int i=0; i < 2; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(EnPassant, updateFlagEnPassant) {
    enum Square epTargetSquare = SQ_C6;
    struct Move moves[4] = {{ .from=SQ_F6, .to=SQ_C6, .flag=0x00 },
                            { .from=SQ_F3, .to=SQ_C6, .flag=0x00 },
                            { .from=SQ_B4, .to=SQ_C6, .flag=0x00 },
                            { .from=SQ_E2, .to=SQ_E4, .flag=0x00 }};

    updateFlagEnPassant(epTargetSquare, moves, 4);

    struct Move exp[4] = {{ .from=SQ_F6, .to=SQ_C6, .flag=0x05 },
                            { .from=SQ_F3, .to=SQ_C6, .flag=0x05 },
                            { .from=SQ_B4, .to=SQ_C6, .flag=0x05 },
                            { .from=SQ_E2, .to=SQ_E4, .flag=0x00 }};

    for (int i=0; i < 4; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(Promotion, wGeneratePawnPromotionMoves) {
    /* Move white's pawn from E7 to E8 and generate all 4 promotions. */
    struct CBoard board = generateEmptyBoard();
    board.whitePawns = 1ULL << SQ_E7;
    struct Move moves[4] = {0};
    
    int numMoves = wGeneratePawnPromotionMoves(board, moves);

    struct Move exp[4] = {{ .from=SQ_E7, .to=SQ_E8, .flag=0x08 },
                          { .from=SQ_E7, .to=SQ_E8, .flag=0x09 },
                          { .from=SQ_E7, .to=SQ_E8, .flag=0x0A },
                          { .from=SQ_E7, .to=SQ_E8, .flag=0x0B }};

    ASSERT_EQUAL(4, numMoves);
    for (int i=0; i < 4; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(Promotion, wGeneratePawnPromotionMoves_Blocked) {
    /* White's E7 pawn is blocked from advancing to E8 by the black king. */
    struct CBoard board = generateEmptyBoard();
    board.whitePawns = 1ULL << SQ_E7;
    board.blackKing = 1ULL << SQ_E8;
    struct Move moves[4] = {0};

    int numMoves = wGeneratePawnPromotionMoves(board, moves);

    struct Move exp[4] = {0};

    ASSERT_EQUAL(0, numMoves);
    for (int i=0; i < 4; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(Promotion, bGeneratePawnPromotionMoves){
    /* Move black's E2 pawn to E1 and generate all 4 promotions. */
    struct CBoard board = generateEmptyBoard();
    board.blackPawns = 1ULL << SQ_E2;
    struct Move moves[4] = {0};
    
    int numMoves = bGeneratePawnPromotionMoves(board, moves);

    struct Move exp[4] = {{ .from=SQ_E2, .to=SQ_E1, .flag=0x08 },
                          { .from=SQ_E2, .to=SQ_E1, .flag=0x09 },
                          { .from=SQ_E2, .to=SQ_E1, .flag=0x0A },
                          { .from=SQ_E2, .to=SQ_E1, .flag=0x0B }};

    ASSERT_EQUAL(4, numMoves);
    for (int i=0; i < 4; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(Promotion, bGeneratePawnPromotionMoves_Blocked) {
    /* Black's E2 pawn is blocked from advancing to E1 by the white king. */
    struct CBoard board = generateEmptyBoard();
    board.whitePawns = 1ULL << SQ_E2;
    board.blackKing = 1ULL << SQ_E1;
    struct Move moves[4] = {0};

    int numMoves = bGeneratePawnPromotionMoves(board, moves);

    struct Move exp[4] = {0};

    ASSERT_EQUAL(0, numMoves);
    for (int i=0; i < 4; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}


CTEST(Promotion, wGeneratePawnPromotionAndCaptureMoves) {
    /* Use white's G7 pawn to capture black's rook on H8 and generate all promotions. */
    struct CBoard board = generateEmptyBoard();
    board.blackRooks = 1ULL << SQ_H8;
    board.whitePawns = 1ULL << SQ_G7;

    struct Move moves[56] = {0};

    int numMoves = wGeneratePawnPromotionAndCaptureMoves(board, moves);

    struct Move exp[4] = { { .from=SQ_G7, .to=SQ_H8, .flag=0x0C },
                        { .from=SQ_G7, .to=SQ_H8, .flag=0x0D },
                        { .from=SQ_G7, .to=SQ_H8, .flag=0x0E },
                        { .from=SQ_G7, .to=SQ_H8, .flag=0x0F }};

    ASSERT_EQUAL(4, numMoves);
    for (int i=0; i < 4; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(Promotion, bGeneratePawnPromotionAndCaptureMoves) {
    /* Use blacks's G2 and E2 pawn to capture white's bishop on F1 and generate all promotions. */
    struct CBoard board = generateEmptyBoard();
    board.blackPawns = 1ULL << SQ_G2 | 1ULL << SQ_E2;
    board.whiteBishops = 1ULL << SQ_F1;

    struct Move moves[56] = {0};

    int numMoves = bGeneratePawnPromotionAndCaptureMoves(board, moves);

    struct Move exp[8] = {{ .from=SQ_E2, .to=SQ_F1, .flag=0x0C },
                          { .from=SQ_E2, .to=SQ_F1, .flag=0x0D },
                          { .from=SQ_E2, .to=SQ_F1, .flag=0x0E },
                          { .from=SQ_E2, .to=SQ_F1, .flag=0x0F },
                          { .from=SQ_G2, .to=SQ_F1, .flag=0x0C },
                          { .from=SQ_G2, .to=SQ_F1, .flag=0x0D },
                          { .from=SQ_G2, .to=SQ_F1, .flag=0x0E },
                          { .from=SQ_G2, .to=SQ_F1, .flag=0x0F }};

    ASSERT_EQUAL(8, numMoves);
    for (int i=0; i < 8; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(PawnMoves, wGenerateAllPawnMoves_StartingBoard) {
    /* Generate all 16 pawn moves for white at the start of a game. 
    The function wGenerateAllPawnMoves takes 600 +/- 50 seconds of CPU time to run 1000000 iterations. */
    struct Move moves[122] = {0};
    struct CBoard board = generateBoard();
    struct Position pos = { .board=board };

    int numMoves = wGenerateAllPawnMoves(&pos, moves);
    ASSERT_EQUAL(16, numMoves);
}

CTEST(PawnMoves, bGenerateAllPawnMoves_StartingBoard) {
    /* Generate all 16 pawn moves for white at the start of a game. 
    The function wGenerateAllPawnMoves takes 600 +/- 50 seconds of CPU time to run 1000000 iterations. */
    struct Move moves[122] = {0};
    struct CBoard board = generateBoard();
    struct Position pos = { .board=board };

    int numMoves = bGenerateAllPawnMoves(&pos, moves);
    ASSERT_EQUAL(16, numMoves);
}

CTEST(KnightMoves, wGenerateKnightMoves_StartingBoard) {
    /* wGenerateKnightMoves takes 150 +/- 20 ms of CPU time to run 1000000 iterations*/
    struct Move moves[4] = {0};
    struct CBoard board = generateBoard();

    int numMoves = wGenerateKnightMoves(board, moves);

    struct Move exp[4] = {{ .from=SQ_B1, .to=SQ_A3, .flag=0x00 },
                          { .from=SQ_B1, .to=SQ_C3, .flag=0x00 },
                          { .from=SQ_G1, .to=SQ_F3, .flag=0x00 },
                          { .from=SQ_G1, .to=SQ_H3, .flag=0x00 }};

    ASSERT_EQUAL(4, numMoves);
    for (int i = 0; i < 4; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(KnightMoves, wGenerateKnightMoves_MultipleCaptures) {
    /* Knights on F3 and B3 capture D4. F3 knight captures G5.
    F3 knight is blocked from moving to E5. */
    struct Move moves[8] = {0};

    struct CBoard board = generateBoard();
    board.whiteKnights = 1ULL << SQ_B3 | 1ULL << SQ_F3;
    // All pawns in starting position except E pawn.
    board.whitePawns = (SECOND_RANK ^ (1ULL << SQ_E2)) | (1ULL << SQ_E5);
    board.blackPawns = 1ULL << SQ_D4;
    board.blackBishops = 1ULL << SQ_G5;

    int numMoves = wGenerateKnightMoves(board, moves);

    struct Move exp[8] = {{ .from=SQ_B3, .to=SQ_D4, .flag=0x04 },
                          { .from=SQ_B3, .to=SQ_A5, .flag=0x00 },
                          { .from=SQ_B3, .to=SQ_C5, .flag=0x00 },
                          { .from=SQ_F3, .to=SQ_G1, .flag=0x00 },
                          { .from=SQ_F3, .to=SQ_D4, .flag=0x04 },
                          { .from=SQ_F3, .to=SQ_H4, .flag=0x00 },
                          { .from=SQ_F3, .to=SQ_G5, .flag=0x04 }};

    ASSERT_EQUAL(7, numMoves);
    for (int i = 0; i < 7; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(KnightMoves, bGenerateKnightMoves_StartingBoard) {
    struct Move moves[4] = {0};
    struct CBoard board = generateBoard();

    int numMoves = bGenerateKnightMoves(board, moves);

    struct Move exp[4] = {{ .from=SQ_B8, .to=SQ_A6, .flag=0x00 },
                          { .from=SQ_B8, .to=SQ_C6, .flag=0x00 },
                          { .from=SQ_G8, .to=SQ_F6, .flag=0x00 },
                          { .from=SQ_G8, .to=SQ_H6, .flag=0x00 }};

    ASSERT_EQUAL(4, numMoves);
    for (int i = 0; i < 4; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

CTEST(KnightMoves, bGenerateKnightMoves_MultipleCaptures) {
    /* Knights on F6 and B6 capture D5. F6 knight captures G4.
    F6 knight is blocked from moving to G8. */
    struct Move moves[8] = {0};

    struct CBoard board = generateBoard();
    board.blackKnights = 1ULL << SQ_F6 | 1ULL << SQ_B6;
    board.blackRooks = (1ULL << SQ_A8) | (1ULL << SQ_G8);
    board.whitePawns = 1ULL << SQ_D5;
    board.whiteBishops = 1ULL << SQ_G4;

    int numMoves = bGenerateKnightMoves(board, moves);

    struct Move exp[8] = {{ .from=SQ_B6, .to=SQ_A4, .flag=0x00 },
                          { .from=SQ_B6, .to=SQ_C4, .flag=0x00 },
                          { .from=SQ_B6, .to=SQ_D5, .flag=0x04 },
                          { .from=SQ_F6, .to=SQ_E4, .flag=0x00 },
                          { .from=SQ_F6, .to=SQ_G4, .flag=0x04 },
                          { .from=SQ_F6, .to=SQ_D5, .flag=0x04 },
                          { .from=SQ_F6, .to=SQ_H5, .flag=0x00 }};

    ASSERT_EQUAL(7, numMoves);
    for (int i = 0; i < 7; i++) {
        ASSERT_EQUAL(exp[i].from, moves[i].from);
        ASSERT_EQUAL(exp[i].to, moves[i].to);
        ASSERT_EQUAL(exp[i].flag, moves[i].flag);
    }
}

// Need to test if moving pawn puts own king in check?

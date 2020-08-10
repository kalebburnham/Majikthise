#include <stdlib.h>
#include "ctest.h"
#include "../src/movegen.h"
#include "../src/printer.h"
#include "../src/rays.h"

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

// Need to test if moving pawn puts king in check?
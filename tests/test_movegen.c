#include <stdlib.h>
#include "ctest.h"
#include "../src/movegen.h"
#include "../src/printer.h"
#include "../src/rays.h"

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

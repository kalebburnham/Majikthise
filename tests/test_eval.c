#include <stdlib.h>
#include "ctest.h"
#include "../src/eval.h"
#include "../src/printer.h"
#include "../src/rays.h"

#include <time.h>

CTEST(isolatedPawns, startingBoard) {
    /* Using a fresh board, no pawns should be isolated. */
    struct CBoard b = generateBoard();
    int white = numIsolatedPawns(b, WHITE);
    //int black = numIsolatedPawns(b, BLACK);
    ASSERT_EQUAL(0,white);
    //ASSERT_EQUAL(0,black);
}

CTEST(isolatedPawns, onePawn) {
    /* Using a fresh board, no pawns should be isolated. */
    struct CBoard b = generateEmptyBoard();
    b.whitePawns = 0x100;
    int white = numIsolatedPawns(b, WHITE);
    //int black = numIsolatedPawns(b, BLACK);
    ASSERT_EQUAL(1,white);
    //ASSERT_EQUAL(0,black);
}

CTEST(isolatedPawns, threeIsolatedPawns) {
    /* Using a fresh board, no pawns should be isolated. */
    struct CBoard b = generateEmptyBoard();
    b.whitePawns = 0x100 | 0x400 | 0x4000;
    int white = numIsolatedPawns(b, WHITE);
    int black = numIsolatedPawns(b, BLACK);
    ASSERT_EQUAL(3,white);
    ASSERT_EQUAL(0,black);
}
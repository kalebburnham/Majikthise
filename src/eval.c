#include "eval.h"
#include <stdio.h>
#include <math.h>

int numIsolatedPawns(struct CBoard b, enum Color c) {
    Board pawns[8] = {0};
    int numIsolated = 0;
    int activePawns;
    int file;

    if (c == WHITE) {
        activePawns = singularize(b.whitePawns, pawns);
    } else {
        activePawns = singularize(b.blackPawns, pawns);
    }

    for (int i = 0; i < activePawns; i++) {
        file = BSF(pawns[i]) % 8;
        printf("%i", file);
        switch (file) {
            case 0:
                if (POPCOUNT((A_FILE | B_FILE) & b.whitePawns) == 1) { numIsolated++; }
                break;
            case 1:
                if (POPCOUNT((A_FILE | B_FILE | C_FILE) & b.whitePawns) == 1) { numIsolated++; }
                break;
            case 2:
                if (POPCOUNT((B_FILE | C_FILE | D_FILE) & b.whitePawns) == 1) { numIsolated++;  }
                break;
            case 3:
                if (POPCOUNT((C_FILE | D_FILE | E_FILE) & b.whitePawns) == 1) { numIsolated++; }
                break;
            case 4:
                if (POPCOUNT((D_FILE | E_FILE | F_FILE) & b.whitePawns) == 1) { numIsolated++;  }
                break;
            case 5:
                if (POPCOUNT((E_FILE | F_FILE | G_FILE) & b.whitePawns) == 1) { numIsolated++;  }
                break;
            case 6:
                if (POPCOUNT((F_FILE | G_FILE | H_FILE) & b.whitePawns) == 1) { numIsolated++;  }
                break;
            case 7:
                if (POPCOUNT((G_FILE | H_FILE) & b.whitePawns) == 1) { numIsolated++; }
        }
    }

    return numIsolated;
}

int numDoubledPawns(struct CBoard b, enum Color c) {
    int numDoubled= 0;
    int activePawns;
    int file;
    int count;

    activePawns = (c == WHITE) ? b.whitePawns : b.blackPawns;

    numDoubled += ((count = POPCOUNT(A_FILE & activePawns)) > 1) ? count : 0;
    numDoubled += ((count = POPCOUNT(B_FILE & activePawns)) > 1) ? count : 0;
    numDoubled += ((count = POPCOUNT(C_FILE & activePawns)) > 1) ? count : 0;
    numDoubled += ((count = POPCOUNT(D_FILE & activePawns)) > 1) ? count : 0;
    numDoubled += ((count = POPCOUNT(E_FILE & activePawns)) > 1) ? count : 0;
    numDoubled += ((count = POPCOUNT(F_FILE & activePawns)) > 1) ? count : 0;
    numDoubled += ((count = POPCOUNT(G_FILE & activePawns)) > 1) ? count : 0;
    numDoubled += ((count = POPCOUNT(H_FILE & activePawns)) > 1) ? count : 0;

    return numDoubled;
}
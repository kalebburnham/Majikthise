#include "rays.h"

Board rays[8][64];

// Source: https://www.chessprogramming.org/On_an_empty_Board
void initRays() {
    for (int sq=0; sq < 64; sq++) {
        rays[NORTH][sq] = 0x0101010101010100ULL << sq;
        rays[SOUTH][sq] = 0x0080808080808080ULL >> (63-sq);
        rays[EAST][sq] = 2 * ((1ULL << (sq | 7)) - (1ULL << sq));
        rays[WEST][sq] = ((1UL << (sq)) - 1) ^ ((1UL << (sq/8)*8) - 1);
    }

    Board diag = A1_H8_DIAGONAL;
    Board diag2;
    for (int rank=0; rank < 8; rank++) {
        diag = (diag >> 1) & ~H_FILE;
        diag2 = diag;
        for (int file = 0; file < 8; file++) {
            diag2 = (diag2 << 1) & ~A_FILE;
            rays[NORTH_EAST][rank*8+file] = diag2;
        }
    }

    diag = A1_H8_DIAGONAL;
    for (int rank=7; rank >= 0; rank--) {
        diag = (diag << 1) & ~A_FILE;
        diag2 = diag;
        for (int file=7; file >= 0; file--) {
            diag2 = (diag2 >> 1) & ~H_FILE;
            rays[SOUTH_WEST][rank*8+file] = diag2;
        }
    }

    diag = H1_A8_ANTIDIAGONAL;
    for (int rank=0; rank < 8; rank++) {
        diag = (diag << 1) & ~A_FILE;
        diag2 = diag;
        for (int file=7; file >= 0; file--) {
            diag2 = (diag2 >> 1) & ~H_FILE;
            rays[NORTH_WEST][rank*8+file] = diag2;
        }
    }

    diag = H1_A8_ANTIDIAGONAL;
    for (int rank=7; rank >= 0; rank--) {
        diag = (diag >> 1) & ~H_FILE;
        diag2 = diag;
        for (int file=0; file < 8; file++) {
            diag2 = (diag2 << 1) & ~A_FILE;
            rays[SOUTH_EAST][rank*8+file] = diag2;
        }
    }
}
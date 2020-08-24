#ifndef BITBOARD_INCLUDED
#define BITBOARD_INCLUDED

#include <stdint.h>
#include <assert.h>

#include "rays.h"
#include "types.h"

#define WHITE_BOARD(b) (b.whitePawns | b.whiteKnights | b.whiteBishops | b.whiteRooks | b.whiteQueens | b.whiteKing)
#define BLACK_BOARD(b) (b.blackPawns | b.blackKnights | b.blackBishops | b.blackRooks | b.blackQueens | b.blackKing)

/* BSF and BSR have undefined return values if their arguments
are zero. */
#define BSF(b) (__builtin_ctzll(b))
#define BSR(b) (63 - __builtin_clzll(b))
#define POPCOUNT(b) (__builtin_popcountll(b))

#define A_FILE 0x0101010101010101
#define B_FILE 0x0202020202020202
#define C_FILE 0x0404040404040404
#define D_FILE 0x0808080808080808
#define E_FILE 0x1010101010101010
#define F_FILE 0x2020202020202020
#define G_FILE 0x4040404040404040
#define H_FILE 0x8080808080808080

#define FIRST_RANK 0x00000000000000FF
#define SECOND_RANK 0x000000000000FF00
#define THIRD_RANK 0x0000000000FF0000
#define FOURTH_RANK 0x00000000FF000000
#define FIFTH_RANK 0x000000FF00000000
#define SIXTH_RANK 0x0000FF0000000000
#define SEVENTH_RANK 0x00FF000000000000
#define EIGHTH_RANK 0xFF00000000000000

#define A1_H8_DIAGONAL 0x8040201008040201
#define H1_A8_ANTIDIAGONAL 0x0102040810204080
#define LIGHT_SQUARES 0x55AA55AA55AA55AA
#define DARK_SQUARES 0xAA55AA55AA55AA55

struct CBoard generateBoard();

struct CBoard generateEmptyBoard();

struct CBoard wIsInCheck();

#endif // ifndef BITBOARD_INCLUDED
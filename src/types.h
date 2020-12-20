#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED

#include <stdint.h>

typedef uint64_t Board;

enum bool { FALSE, TRUE };

enum Color { WHITE, BLACK, COLOR_NB = 2 };

enum Piece { P, N, B, R, Q, K };

enum Square {
  SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
  SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
  SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
  SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
  SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
  SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
  SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
  SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
  SQ_NONE,

  SQUARE_NB = 64
};

enum Dir {
  NORTH, SOUTH, EAST, WEST, NORTH_EAST, NORTH_WEST, SOUTH_EAST, SOUTH_WEST
};

struct CBoard
{
  Board whitePawns;
  Board whiteKnights;
  Board whiteBishops;
  Board whiteRooks;
  Board whiteQueens;
  Board whiteKing;

  Board blackPawns;
  Board blackKnights;
  Board blackBishops;
  Board blackRooks;
  Board blackQueens;
  Board blackKing;
};

struct Move {
  unsigned int from:6;
  unsigned int to:6;
  unsigned int flag:4;
};

struct Position {
  struct Position *parent;

  struct CBoard board;
  struct CBoard wAttacks;
  struct CBoard bAttacks;

  enum Color sideToMove;

  uint8_t halfmove_clock;

  enum bool wkCastle;
  enum bool wqCastle;
  enum bool bkCastle;
  enum bool bqCastle;

  enum Square epTargetSquare;
};

struct PieceInfo {
  enum Piece piece;
  enum Color color;
  enum Square sq;
};

#endif // TYPES_INCLUDED
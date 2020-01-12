#include "../include/board.h"
#include <iostream>
#include "../include/piece.h"
#include "../include/square.h"

namespace Chess {
Board::Board() {}

void Board::placePawns() {
  int xWhitePawnStart = pawnWhiteStart.first;
  int xBlackPawnStart = pawnBlackStart.second;
  for (int i = 0; i < columns; i++) {
    board[xWhitePawnStart][i] = Square(Piece::PAWN, Color::WHITE);
    board[xBlackPawnStart][i] = Square(Piece::PAWN, Color::BLACK);
  }
}

void Board::placeBlackPowerPieces() {
  // Queens
  board[queenBlack.first][queenBlack.second] =
      Square(Piece::QUEEN, Color::BLACK);
  board[kingBlack.first][kingBlack.second] = Square(Piece::KING, Color::BLACK);
  board[bishop1Black.first][bishop1Black.second] =
      Square(Piece::BISHOP, Color::BLACK);
  board[bishop2Black.first][bishop2Black.second] =
      Square(Piece::BISHOP, Color::BLACK);
  board[knight1Black.first][knight1Black.second] =
      Square(Piece::KNIGHT, Color::BLACK);
  board[knight2Black.first][knight2Black.second] =
      Square(Piece::KNIGHT, Color::BLACK);
  board[rook1Black.first][rook1Black.second] =
      Square(Piece::ROOK, Color::BLACK);
  board[rook2Black.first][rook2Black.second] =
      Square(Piece::ROOK, Color::BLACK);
}

void Board::placeWhitePowerPieces() {
  // Queens
  board[queenWhite.first][queenWhite.second] =
      Square(Piece::QUEEN, Color::WHITE);
  board[kingWhite.first][kingWhite.second] = Square(Piece::KING, Color::WHITE);
  board[bishop1White.first][bishop1White.second] =
      Square(Piece::BISHOP, Color::WHITE);
  board[bishop2White.first][bishop2White.second] =
      Square(Piece::BISHOP, Color::WHITE);
  board[knight1White.first][knight1White.second] =
      Square(Piece::KNIGHT, Color::WHITE);
  board[knight2White.first][knight2White.second] =
      Square(Piece::KNIGHT, Color::WHITE);
  board[rook1White.first][rook1White.second] =
      Square(Piece::ROOK, Color::WHITE);
  board[rook2White.first][rook2White.second] =
      Square(Piece::ROOK, Color::WHITE);
}

Square Board::getSquare(int x, int y) { return board[x][y]; }

void Board::constructInitialBoard() {
  placePawns();
  placeBlackPowerPieces();
  placeWhitePowerPieces();
}
}  // namespace Chess
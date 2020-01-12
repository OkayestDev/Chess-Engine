#include "../include/square.h"
#include "../include/color.h"
#include "../include/piece.h"

namespace Chess {
Square::Square(Piece _piece, Color _pieceColor) {
  pieceColor = _pieceColor;
  piece = _piece;
}

Square::Square() {}
}  // namespace Chess
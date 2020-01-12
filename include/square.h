#pragma once

using namespace std;

#include "color.h"
#include "piece.h"

namespace Chess
{
struct Square
{
    Color pieceColor;
    Piece piece;
    Square(Piece, Color);
    Square();
};
} // namespace Chess
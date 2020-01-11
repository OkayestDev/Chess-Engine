#pragma once

#include <array>

namespace Chess
{
const size_t boardSize = 10 * 12;

const size_t Col8Row1 = 28;
const size_t Col1Row2 = 31;
const size_t Col1Row7 = 81;
const size_t Col1Row8 = 91;
const size_t Col8Row8 = 98;

const size_t pawnWhiteStart = 81;
const size_t pawnBlackStart = 32;

const size_t kingWhitePosition = 95;
const size_t kingBlackPosition = 25;

enum class Color
{
    white,
    black,
    none
};

enum class Piece
{
    king,       // A king without castle potential
    kingCastle, // A king with castle potential
    queen,
    pawn,          // A pawn without en passant potential
    pawnEnPassant, // A pawn with en passant potential
    rook,
    rookCastle,
    knight,
    bishop,
    none,
    outOfBounds // Illegal position
};

struct Square
{
    Color pieceColor;
    Piece piece;
    Square(Piece, Color);
    Square();
};

class Board
{
private:
    std::array<Square, boardSize> squares;

public:
    void setSquare(const size_t where, Square);
    Square getSquare(const size_t where) const;
};

void initClassicBoard(Board &);
} // namespace Chess
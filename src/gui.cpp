#include "gui.h"
#include "board.h"
#include "piece.h"
#include <iostream>
#include <map>

using namespace std;

namespace Chess
{
static const map<Piece, char> sprites = {
    {Piece::PAWN, 'A'},   {Piece::PAWN_EN_PASSANT, 'P'},
    {Piece::ROOK, 'H'},   {Piece::ROOK_CASTLE, 'H'},
    {Piece::KNIGHT, 'F'}, {Piece::BISHOP, 'I'},
    {Piece::KING, 'K'},   {Piece::KING_CASTLE, 'K'},
    {Piece::NONE, '+'},   {Piece::OUT_OF_BOUNDS, '#'},
    {Piece::QUEEN, 'Q'}};

void printBoard(Board board)
{
    for (int i = 0; i < board.columns; i++)
    {
        for (int j = 0; j < board.rows; j++)
        {
            Square square = board.getSquare(i, j);
            char sprite = sprites.at(square.piece);
            if (square.pieceColor == Color::BLACK)
            {
                sprite = tolower(sprite);
            }
            cout << sprite << ' ';
        }
        cout << endl;
    }
}

Move readMove() {}
} // namespace Chess
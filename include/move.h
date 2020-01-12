#pragma once

#include <list>
#include <vector>

#include "board.h"

using namespace std;

namespace Chess
{
// const int moveDone = 100; // @todo what's this?

struct Move
{
    int fromX;
    int fromY;
    int toX;
    int toY;
    Move(int, int, int, int);
    Move();
};

struct BoardChange
{
    int row;
    int column;
    Square oldSquare;
};

using BoardHistory = list<BoardChange>;
using MoveSet = vector<Move>;

void undoMove(Board &, BoardHistory &);

/*
 * Castling is identified by king move to its castling destination if permitted.
 * Pawn promotion move deduced.
 * All other moves are unconditional moves.
 */
void doMove(Move, Board &, BoardHistory &, Piece pawnPromotion = Piece::QUEEN);

MoveSet validMoves(Board, Color turn);
} // namespace Chess
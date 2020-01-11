#pragma once

#include <list>
#include <vector>

#include "board.h"

namespace Chess
{
const size_t moveDone = boardSize;

struct Move
{
    size_t from;
    size_t to;
    Move(size_t, size_t);
    Move();
};

struct BoardChange
{
    size_t position;
    Square oldSquare;
};

using Boardhistory = std::list<BoardChange>;
using MoveSet = std::vector<Move>;

void undoMove(Board &, Boardhistory &);

/* 
* Castling is identified by king move to its castling destination if permitted.
* Pawn promotion move deduced.
* All other moves are unconditional moves.
*/
void doMove(Move, Board &, Boardhistory &, Piece pawnPromotion = Piece::queen);

MoveSet validMoves(Board &, Color turn); // This is the move generator
} // namespace Chess
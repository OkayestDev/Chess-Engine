#include <iostream>

#include "../include/move.h"

namespace Chess
{
Move::Move(int _fromX, int _toX, int _fromY, int _toY)
{
    fromX = _fromX;
    fromY = _fromY;
    toX = _toX;
    toY = _toY;
}

Move::Move() {}

void undoMove(Board &board, BoardHistory &boardHistory)
{
    if (boardHistory.size())
    {
        BoardChange lastChange = boardHistory.back();
        board.setSquare(lastChange.column, lastChange.row,
                        lastChange.oldSquare);
    }
}

void doMove(Move m, Board &board, BoardHistory &boardHistory,
            Piece pawnPromotion)
{
    
}
} // namespace Chess
#include <iostream>

#include "../include/move.h"

namespace Chess
{
Move::Move(int _fromColumn, int _toColumn, int _fromRow, int _toRow)
{
    fromColumn = _fromColumn;
    fromRow = _fromRow;
    toColumn = _toColumn;
    toRow = _toRow;
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
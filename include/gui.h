#pragma once

#include <vector>
#include "board.h"
#include "move.h"

namespace Chess
{
void printBoard(const Board &, Move last_move);

/* Returns when one of the provided valid moves is read */
Move readMove(const MoveSet &valid_moves, Color turn);
} // namespace Chess
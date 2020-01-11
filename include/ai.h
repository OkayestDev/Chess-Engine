/*
    File: ai.h

    Takes a board, returns an heuristically optimized move.
*/
#pragma once

#include "move.h"

namespace Chess
{
int aiMove(
    Board &board,
    Boardhistory &boardHistory,
    Color turn,
    int depth,
    Move &_bm,
    int alpha = -400,
    int beta = 400);
}
// See board.h on "magic numbers"
// File: ai.cpp

#include "ai.h"
#include <random>
#include <algorithm>
#include <iostream>

using namespace std;

namespace Chess
{
mt19937 mt(time(0));

void moveorder(MoveSet &ms)
{
    random_shuffle(ms.begin(), ms.end());
}

static int evaluateLeaf(Board board)
{
    int sum = 0;
    for (int i = 0; i < board.rows; i++)
    {
        for (int j = 0; j < board.columns; j++)
        {
            Square currentSquare = board.getSquare(j, i);

            if (currentSquare.pieceColor == Color::NONE)
            {
                continue;
            }

            int c = currentSquare.pieceColor == Color::WHITE ? 1 : -1;
            int v = 0;
            switch (currentSquare.piece)
            {
            case Piece::PAWN:
            case Piece::PAWN_EN_PASSANT:
                v = 1;
                break;
            case Piece::ROOK:
            case Piece::ROOK_CASTLE:
                v = 5;
                break;
            case Piece::KNIGHT:
            case Piece::BISHOP:
                v = 3;
                break;
            case Piece::QUEEN:
                v = 9;
                break;
            default:
                break;
            }
            sum += c * v;
        }
    }
    return sum;
}

static Color flippedTurn(Color turn)
{
    return turn == Color::WHITE
               ? Color::BLACK
               : Color::WHITE;
}

int aiMove(Board board, BoardHistory boardHistory, Color turn, int depth, Move bm, int alpha, int beta)
{
    /*
    MoveSet valid = validMoves(board, turn);
    bm = valid[mt()%valid.size()];
    return 0;
    */

    Move bestMove;
    int bestScore = turn == Color::WHITE ? -300 : 300;
    if (!depth)
    {
        return evaluateLeaf(board);
    }

    MoveSet vmoves = validMoves(board, turn);
    moveorder(vmoves);
    for (Move m : vmoves)
    {
        Square currentSquare = board.getSquare(m.toColumn, m.toRow);
        if (currentSquare.piece == Piece::KING || currentSquare.piece == Piece::KING_CASTLE)
        {
            bestScore = turn == Color::WHITE ? 200 + depth : -200 - depth;
            bestMove = m;
            break;
        }

        doMove(m, board, boardHistory);
        int newScore = aiMove(board, boardHistory, flippedTurn(turn), depth - 1, bm, alpha, beta);
        undoMove(board, boardHistory);

        if ((turn == Color::WHITE && newScore > bestScore) || (turn == Color::BLACK && newScore < bestScore))
        {
            bestMove = m;
            bestScore = newScore;

            if (turn == Color::BLACK)
            {
                beta = newScore;
                if (beta <= alpha)
                {
                    break;
                }
            }

            if (turn == Color::WHITE)
            {
                alpha = newScore;
                if (alpha >= beta)
                {
                    break;
                }
            }
        }
    }
    bm = bestMove;
    return bestScore;
}
} // namespace Chess
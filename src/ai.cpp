#include <random>
#include <algorithm>
#include <iostream>

#include "../include/ai.h"

namespace Chess
{
std::mt19937 mt(time(0));

void moveorder(MoveSet &moveSet)
{
    std::random_shuffle(moveSet.begin(), moveSet.end());
}

static int evaluateLeaf(const Board &board)
{
    int sum = 0;
    for (size_t i = 21; i < 99; ++i)
    {
        if (board.getSquare(i).pieceColor == Color::none)
            continue;
        int c = board.getSquare(i).pieceColor == Color::white ? 1 : -1;
        int v = 0;
        switch (board.getSquare(i).piece)
        {
        case Piece::pawn:
        case Piece::pawnEnPassant:
            v = 1;
            break;
        case Piece::rook:
        case Piece::rookCastle:
            v = 5;
            break;
        case Piece::knight:
        case Piece::bishop:
            v = 3;
            break;
        case Piece::queen:
            v = 9;
            break;
        default:
            break;
        }
        sum += c * v;
    }
    return sum;
}

static Color flippedTurn(Color turn)
{
    return turn == Color::white
               ? Color::black
               : Color::white;
}

int aiMove(Board &board, Boardhistory &boardHistory, Color turn, int depth, Move &_bm, int alpha, int beta)
{
    /*
            MoveSet valid = validMoves(b, turn);
            _bm = valid[mt()%valid.size()];
            return 0;
        */
    const bool isWhiteTurn = turn == Color::white;
    Move bestMove;
    int bestScore = isWhiteTurn ? -300 : 300;
    if (!depth)
    {
        return evaluateLeaf(board);
    }

    MoveSet vmoves = validMoves(board, turn);
    moveorder(vmoves);
    //int progress = 0; // Temporary hack to show progress
    for (Move m : vmoves)
    {
        //if (depth == 8) // Temporary hack to show progress
        //  std::cout<<"\r"<<++progress<<"/"<<vmoves.size()<<std::flush;

        if (board.getSquare(m.to).piece == Piece::king || board.getSquare(m.to).piece == Piece::kingCastle)
        {
            bestScore = turn == Color::white ? 200 + depth : -200 - depth;
            bestMove = m;
            break;
        }

        doMove(m, board, boardHistory);
        int newScore = aiMove(board, boardHistory, flippedTurn(turn), depth - 1, _bm, alpha, beta);
        undoMove(board, boardHistory);

        if ((isWhiteTurn && newScore > bestScore) || (!isWhiteTurn && newScore < bestScore))
        {
            bestMove = m;
            bestScore = newScore;

            if (!isWhiteTurn)
            {
                beta = newScore;
                if (beta <= alpha)
                {
                    break;
                }
            }

            if (isWhiteTurn)
            {
                alpha = newScore;
                if (alpha >= beta)
                {
                    break;
                }
            }
        }
    }

    _bm = bestMove;
    return bestScore;
}
} // namespace Chess
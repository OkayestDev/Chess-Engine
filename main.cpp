/*
    TODO: don't allow moves that leaves king in check, and count check-mate as victory. Hence, perft will be off by a few.
    TODO: prompt pawn promotion, instead of the default queen.
    TODO: handle cases of no valid moves
*/
#include <iostream>
#include <ctime>
#include "./include/board.h"
#include "./include/move.h"
#include "./include/gui.h"
#include "./include/ai.h"

using namespace Chess;

unsigned long perft(Board &board, Boardhistory &boardHistory, int depth, Color turn)
{
    turn = (turn == Color::white) ? Color::black : Color::white;
    if (!depth)
        return 1;
    int leafs = 0;
    for (Move m : validMoves(board, turn))
    {
        if (board.getSquare(m.to).piece == Piece::king || board.getSquare(m.to).piece == Piece::kingCastle)
        {
            ++leafs;
            continue;
        }
        doMove(m, board, boardHistory);
        leafs += perft(board, boardHistory, depth - 1, turn);
        undoMove(board, boardHistory);
    }
    return leafs;
}

int main()
{
    std::cout << "\nChess Engine 1.0\n\n";
    std::cout << "Commands:\nyxyx: fromto move.\n0: regret move (last AI move will be reverted as well).\n1: change color (AI will make this move)\n2: exit.\n\n";
    Board board;
    Boardhistory boardHistory;
    initClassicBoard(board);

    Color turn = Color::white;
    Color aiColor = Color::black;

    bool aiHasKing = true;
    bool humanHasKing = true;

    if (false)
    {
        unsigned long t = time(0);
        std::cout << "DEBUG: Perft(5) result (expecting 4897256): " << perft(board, boardHistory, 5, Color::black);
        t = time(0) - t;
        std::cout << "\nTime " << t << "\n";
        return 0;
    }

    if (false)
    {
        Move mv;
        unsigned long t = time(0);
        aiMove(board, boardHistory, turn, 7, mv);
        t = time(0) - t;
        std::cout << "\nAI Time: " << t << "\n";
        return 0;
    }

    Move mv{0, 0};
    while (aiHasKing && humanHasKing)
    {
        printBoard(board, mv);
        if (turn == aiColor)
        {
            aiMove(board, boardHistory, turn, 7, mv);
        }
        else
        {
            mv = readMove(validMoves(board, turn), turn);
        }

        if (mv.from == 0)
        {
            undoMove(board, boardHistory);
            undoMove(board, boardHistory);
            continue;
        }
        else if (mv.from == 1)
        {
            aiColor = aiColor == Color::white ? Color::black : Color::white;
            continue;
        }
        else if (mv.from == 2)
        {
            humanHasKing = false;
            break;
        }

        doMove(mv, board, boardHistory);
        turn = turn == Color::white ? Color::black : Color::white;

        aiHasKing = humanHasKing = false;
        for (size_t i = 21; i < 99; ++i)
        { // board.boardHistory about these magic numbers
            if (board.getSquare(i).piece == Piece::king || board.getSquare(i).piece == Piece::kingCastle)
            {
                if (board.getSquare(i).pieceColor == aiColor)
                {
                    aiHasKing = true;
                }
                else
                {
                    humanHasKing = true;
                }
            }
        }
    }
    printBoard(board, mv);

    std::cout << "\n\n";
    if (!humanHasKing)
        std::cout << "You lose.";
    if (!aiHasKing)
        std::cout << "You win.";
    std::cout << "\n\nBye!\n\n";
}
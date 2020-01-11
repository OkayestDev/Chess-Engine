#include <iostream>

#include "../include/move.h"

namespace Chess
{
Move::Move(size_t _from, size_t _to)
{
    from = _from;
    to = _to;
}

Move::Move() {}

void undoMove(Board &board, Boardhistory &ml)
{
    if (!ml.size())
    {
        return;
    }
    if (ml.back().position == moveDone)
    {
        ml.pop_back();
    }

    while (ml.size() && ml.back().position != moveDone)
    {
        board.setSquare(ml.back().position, ml.back().oldSquare);
        ml.pop_back();
    }
}

static void doChange(Board &board, Boardhistory &boardHistory, size_t position, Square newSquare)
{
    BoardChange change;
    change.oldSquare = board.getSquare(position);
    change.position = position;
    boardHistory.push_back(change);
    board.setSquare(position, newSquare);
}

void doMove(Move m, Board &board, Boardhistory &boardHistory, Piece pawn_promotion)
{
    // Pawn promotion
    if (board.getSquare(m.from).piece == Piece::pawn && m.to / 10 == 2)
    {
        doChange(board, boardHistory, m.from, Square(pawn_promotion, Color::white));
    }

    if (board.getSquare(m.from).piece == Piece::pawn && m.to / 10 == 9)
    {
        doChange(board, boardHistory, m.from, Square(pawn_promotion, Color::black));
    }

    // Move rook if castling
    if (board.getSquare(m.from).piece == Piece::kingCastle && (m.from - m.to == 2 || m.from - m.to == -2))
    {
        if (m.to == 23)
        {
            doChange(board, boardHistory, 21, Square(Piece::none, Color::none));
            doChange(board, boardHistory, 24, Square(Piece::rook, Color::black));
        }

        if (m.to == 27)
        {
            doChange(board, boardHistory, 28, Square(Piece::none, Color::none));
            doChange(board, boardHistory, 26, Square(Piece::rook, Color::black));
        }

        if (m.to == 93)
        {
            doChange(board, boardHistory, 91, Square(Piece::none, Color::none));
            doChange(board, boardHistory, 94, Square(Piece::rook, Color::white));
        }

        if (m.to == 97)
        {
            doChange(board, boardHistory, 98, Square(Piece::none, Color::none));
            doChange(board, boardHistory, 96, Square(Piece::rook, Color::white));
        }
    }

    Piece pawnReplaced = board.getSquare(m.to).piece;
    // Regular piece move
    doChange(board, boardHistory, m.to, board.getSquare(m.from));
    doChange(board, boardHistory, m.from, Square(Piece::none, Color::none));

    // Pawn replaced empty square
    if (board.getSquare(m.to).piece == Piece::pawn && pawnReplaced == Piece::none)
    {
        // En passant move
        if (board.getSquare(m.from - 1).piece == Piece::pawnEnPassant && (m.from - m.to == 11 || m.from - m.to == -9))
        {
            doChange(board, boardHistory, m.from - 1, Square(Piece::none, Color::none));
        }
        else if (board.getSquare(m.from + 1).piece == Piece::pawnEnPassant && (m.from - m.to == 9 || m.from - m.to == -11))
        {
            doChange(board, boardHistory, m.from + 1, Square(Piece::none, Color::none));
        }
    }

    // Clear flag of pawns with en passant potential
    for (size_t i = 1; i < 9; ++i)
    {
        if (board.getSquare(50 + i).piece == Piece::pawnEnPassant)
        {
            doChange(board, boardHistory, 50 + i, Square(Piece::pawn, Color::black));
        }

        if (board.getSquare(60 + i).piece == Piece::pawnEnPassant)
        {
            doChange(board, boardHistory, 60 + i, Square(Piece::pawn, Color::white));
        }
    }

    // Give two-square moved pawns en passant flag
    if (board.getSquare(m.to).piece == Piece::pawn)
    {
        if (m.from / 10 == 3 && m.to / 10 == 5)
        {
            doChange(board, boardHistory, m.to, Square(Piece::pawnEnPassant, Color::black));
        }

        if (m.from / 10 == 8 && m.to / 10 == 6)
        {
            doChange(board, boardHistory, m.to, Square(Piece::pawnEnPassant, Color::white));
        }
    }

    // Lose castling potential
    if (board.getSquare(m.to).piece == Piece::kingCastle)
    {
        doChange(board, boardHistory, m.to, Square(Piece::king, board.getSquare(m.to).pieceColor));
    }

    if (board.getSquare(m.to).piece == Piece::rookCastle)
    {
        doChange(board, boardHistory, m.to, Square(Piece::rook, board.getSquare(m.to).pieceColor));
    }

    BoardChange done;
    done.position = moveDone;
    boardHistory.push_back(done);
}

MoveSet validMoves(Board &board, Color turn)
{
    MoveSet moveSet;
    Color enemyColor = (turn == Color::white) ? Color::black : Color::white;
    int pawnDir = (turn == Color::white) ? -1 : 1;

    for (size_t from = 21 /*skip padding*/; from < 99 /*padding after this*/; ++from)
    {
        if (board.getSquare(from).pieceColor == turn)
        {
            switch (board.getSquare(from).piece)
            {
            case Piece::kingCastle:
                if (from == 95 && board.getSquare(96).piece == Piece::none && board.getSquare(97).piece == Piece::none && board.getSquare(98).piece == Piece::rookCastle)
                {
                    moveSet.push_back(Move(from, 97));
                }
                if (from == 25 && board.getSquare(26).piece == Piece::none && board.getSquare(27).piece == Piece::none && board.getSquare(28).piece == Piece::rookCastle)
                {
                    moveSet.push_back(Move(from, 27));
                }
                if (from == 95 && board.getSquare(94).piece == Piece::none && board.getSquare(93).piece == Piece::none && board.getSquare(92).piece == Piece::none && board.getSquare(91).piece == Piece::rookCastle)
                {
                    moveSet.push_back(Move(from, 93));
                }
                if (from == 25 && board.getSquare(24).piece == Piece::none && board.getSquare(23).piece == Piece::none && board.getSquare(22).piece == Piece::none && board.getSquare(21).piece == Piece::rookCastle)
                {
                    moveSet.push_back(Move(from, 23));
                }
            // fallthrough
            case Piece::king:
                for (auto to : {from - 11, from - 10, from - 9, from - 1, from + 1, from + 9, from + 10, from + 11})
                {
                    if (board.getSquare(to).pieceColor == turn || board.getSquare(to).piece == Piece::outOfBounds)
                        continue;
                    moveSet.push_back(Move(from, to));
                }
                break;
            case Piece::pawn:
                if (board.getSquare(from + pawnDir * 11).pieceColor == enemyColor)
                {
                    moveSet.push_back(Move(from, from + pawnDir * 11));
                }

                if (board.getSquare(from + pawnDir * 9).pieceColor == enemyColor)
                {
                    moveSet.push_back(Move(from, from + pawnDir * 9));
                }

                if (board.getSquare(from + pawnDir * 10).piece == Piece::none)
                {
                    moveSet.push_back(Move(from, from + pawnDir * 10));
                }

                if (board.getSquare(from + pawnDir * 10).piece == Piece::none && board.getSquare(from + pawnDir * 20).piece == Piece::none)
                {
                    size_t row = from / 10;
                    if ((row == 3 && pawnDir == 1) || (row == 8 && pawnDir == -1))
                    {
                        moveSet.push_back(Move(from, from + pawnDir * 20));
                    }
                }

                if (board.getSquare(from - 1).piece == Piece::pawnEnPassant && pawnDir == -1)
                {
                    moveSet.push_back(Move(from, from - 11));
                }
                if (board.getSquare(from + 1).piece == Piece::pawnEnPassant && pawnDir == -1)
                {
                    moveSet.push_back(Move(from, from - 9));
                }
                if (board.getSquare(from - 1).piece == Piece::pawnEnPassant && pawnDir == 1)
                {
                    moveSet.push_back(Move(from, from + 9));
                }
                if (board.getSquare(from + 1).piece == Piece::pawnEnPassant && pawnDir == 1)
                {
                    moveSet.push_back(Move(from, from + 11));
                }
                break;
            case Piece::knight:
                for (auto to : {from + 8, from + 12, from + 19, from + 21, from - 8, from - 12, from - 21, from - 19})
                {
                    if (board.getSquare(to).pieceColor == turn || board.getSquare(to).piece == Piece::outOfBounds)
                        continue;
                    moveSet.push_back(Move(from, to));
                }
                break;
            case Piece::queen:
            case Piece::rook:
            case Piece::rookCastle:
                for (int dd : {1, -1, 10, -10})
                    for (int d = dd; board.getSquare(from + d).pieceColor != board.getSquare(from).pieceColor && board.getSquare(from + d).piece != Piece::outOfBounds; d += dd)
                    {
                        moveSet.push_back(Move(from, from + d));
                        if (board.getSquare(from + d).piece != Piece::none)
                            break;
                    }
                if (board.getSquare(from).piece != Piece::queen)
                    break;
            case Piece::bishop:
                for (int dd : {9, 11, -9, -11})
                    for (int d = dd; board.getSquare(from + d).pieceColor != board.getSquare(from).pieceColor && board.getSquare(from + d).piece != Piece::outOfBounds; d += dd)
                    {
                        moveSet.push_back(Move(from, from + d));
                        if (board.getSquare(from + d).piece != Piece::none)
                        {
                            break;
                        }
                    }
                break;
            default: // warnings unwanted
                break;
            }
        }
    }

    return moveSet;
}
} // namespace Chess
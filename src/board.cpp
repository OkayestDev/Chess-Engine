#include "../include/board.h"

namespace Chess
{
Square::Square(Piece p, Color c)
{
    piece = p;
    pieceColor = c;
}

Square::Square()
{
    piece = Piece::outOfBounds;
    pieceColor = Color::none;
}

void Board::setSquare(const size_t position, Square s)
{
    if (position >= boardSize)
    {
        return;
    }
    squares[position] = s;
}

Square Board::getSquare(const size_t position) const
{
    if (position >= boardSize)
    {
        return Square(Piece::outOfBounds, Color::none);
    }
    return squares[position];
}

void placePawns(Board &board)
{
    for (size_t i = 0; i < 8; ++i)
    {
        board.setSquare(pawnBlackStart + i, Square(Piece::pawn, Color::black));
        board.setSquare(pawnWhiteStart + i, Square(Piece::pawn, Color::white));
    }
}

/**
     * Place the rest but with s/kings/queens
     * @todo refactor magic number
     */
void placePowerPieces(Board &board)
{
    int w = 0;
    for (auto p : {Piece::rookCastle, Piece::knight, Piece::bishop, Piece::queen})
    {
        board.setSquare(21 + w, Square(p, Color::black));
        board.setSquare(Col8Row1 - w, Square(p, Color::black));
        board.setSquare(Col1Row8 + w, Square(p, Color::white));
        board.setSquare(Col8Row8 - w, Square(p, Color::white));
        ++w;
    }
}

void placeKings(Board &board)
{
    board.setSquare(kingBlackPosition, Square(Piece::kingCastle, Color::black));
    board.setSquare(kingWhitePosition, Square(Piece::kingCastle, Color::white));
}

/**
     * Populates the empty spaces between pieces
     */
void emptySquares(Board &board)
{
    for (int x = 0; x < 8; ++x)
    {
        for (int y = 0; y < 4; ++y)
        {
            board.setSquare(
                41 + x + y * 10,
                Square(Piece::none, Color::none));
        }
    }
}

void initClassicBoard(Board &board)
{
    placePawns(board);
    placePowerPieces(board);
    placeKings(board);
    emptySquares(board);
}
} // namespace Chess
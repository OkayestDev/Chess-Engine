#pragma once

#include "square.h"
#include <array>

using namespace std;

namespace Chess
{
class Board
{
  private:
    Square board[8][8];
    // Black pieces
    pair<int, int> pawnBlackStart = make_pair(1, 0);
    pair<int, int> kingBlack = make_pair(0, 4);
    pair<int, int> queenBlack = make_pair(0, 3);
    pair<int, int> bishop1Black = make_pair(0, 2);
    pair<int, int> bishop2Black = make_pair(0, 5);
    pair<int, int> rook1Black = make_pair(0, 0);
    pair<int, int> rook2Black = make_pair(0, 7);
    pair<int, int> knight1Black = make_pair(0, 1);
    pair<int, int> knight2Black = make_pair(0, 6);
    // White pieces
    pair<int, int> pawnWhiteStart = make_pair(6, 7);
    pair<int, int> kingWhite = make_pair(7, 4);
    pair<int, int> queenWhite = make_pair(7, 3);
    pair<int, int> bishop1White = make_pair(7, 2);
    pair<int, int> bishop2White = make_pair(7, 5);
    pair<int, int> rook1White = make_pair(7, 0);
    pair<int, int> rook2White = make_pair(7, 7);
    pair<int, int> knight1White = make_pair(7, 1);
    pair<int, int> knight2White = make_pair(7, 6);

    void placePawns();
    void placeBlackPowerPieces();
    void placeWhitePowerPieces();

  public:
    const int columns = 8;
    const int rows = 8;

    Board();

    Square getSquare(int, int);
    /**
     * Constructs a board with game start state
     */
    void constructInitialBoard();
    void setSquare(int, int, Square);
    bool isColumnRowInBounds(int, int);
};
} // namespace Chess

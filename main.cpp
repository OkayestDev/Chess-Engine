#include "./include/board.h"
#include "./include/gui.h"
#include <iostream>

using namespace Chess;

int main()
{
    Board board = Board();
    board.constructInitialBoard();

    printBoard(board);
}
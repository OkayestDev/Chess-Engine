#include <iostream>
#include "./include/board.h"

using namespace Chess;

int main() {
  Board board = Board();
  board.constructInitialBoard();

  Square square = board.getSquare(0, 0);
}
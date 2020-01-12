/**
 * Prints a text based gui
 */
#include "board.h"
#include "move.h"
#include <cctype>
#include <iostream>
#include <map>

using namespace std;

namespace Chess
{
void printBoard(Board);
Move readMove();
} // namespace Chess
#include "board.h"

Board::Board() {
    cells.fill(EMPTY, 100);

}

void Board::addShip(Ship *ship)
{
    flot.push_back(ship);
}

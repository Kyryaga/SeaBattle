#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include "ship.h"

class Board
{
public:
    Board();

    enum Cell {
        EMPTY,
        DOT,
        SHIP,
        DEAD
    };

    void addShip(Ship* ship);

private:
    QVector<Cell> cells;
    QVector<Ship*> flot;
};

#endif // BOARD_H

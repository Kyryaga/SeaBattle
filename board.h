#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include "ship.h"


enum Cell {
    EMPTY,
    DOT,
    SHIP,
    DEAD,
    DAMAGED
};


class Board
{
public:
    Board();

    void addShip(Ship* ship);
    void setCellState(QPoint point, Cell state);
    Cell getCellState(QPoint point);
    void printBoardStates();

    QVector<Cell> getCells();

    QVector<Ship *> getFlot();
    void prettyPrintFlot();
    void clear();

    Ship *getShipByCell(QPoint point);

private:
    QVector<Cell> cells;
    QVector<Ship*> flot;
};

#endif // BOARD_H

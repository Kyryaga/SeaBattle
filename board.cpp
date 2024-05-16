#include "board.h"

Board::Board() {
    cells.fill(EMPTY, 100);
}

void Board::addShip(Ship *ship)
{
    flot.push_back(ship);
}

void Board::setCellState(QPoint point, Cell state)
{
    cells[point.x() + 10 * point.y()] = state;
}

Cell Board::getCellState(QPoint point)
{
    return cells[point.x() + 10 * point.y()];
}

void Board::printBoardStates()
{
    // вывод игрового поля в виде матрицы
    for (int i = 0; i < 10; i++) {
        QString str = "";

        for (int j {0}; j < 10; j++) {
            str += QString::number(cells[i * 10 + j]) + " ";
        }

        qDebug() << str;
    }

    qDebug() << "\n";
}

QVector<Cell> Board::getCells()
{
    return cells;
}

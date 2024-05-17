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
    if (point.x() > 9 || point.y() > 9 || point.x() < 0 || point.y() < 0) {
        return Cell::EMPTY;
    }

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

QVector<Ship *> Board::getFlot()
{
    return flot;
}

void Board::prettyPrintFlot()
{
    for (Ship* ship : flot) {
        qDebug() << "w: " << ship->getWeight() << ", " << ship->getCoords();
    }
}

void Board::clear()
{
    for (Cell &cell : cells) {
        cell = Cell::EMPTY;
    }
}

Ship *Board::getShipByCell(QPoint point)
{
    // получаем корабль по клетке
    if (getCellState(point) != Cell::SHIP) {
        qDebug() << "В ФУНКЦИЮ getShipByCell передана клетка без корабля!";
        return nullptr;
    }


    // проверка на то, что мы как раз тыкнули на нос корабля
    for (Ship* ship : flot) {
        if (ship->getCoords() == point)
            return ship;
    }

    if (getCellState(QPoint(point.x() - 1, point.y())) == Cell::SHIP || getCellState(QPoint(point.x() - 1, point.y())) == Cell::DAMAGED) {
        // значит нос корабля слева

        while (true) {
            point = QPoint(point.x() - 1, point.y());

            for (Ship* ship : flot) {
                if (ship->getCoords() == point)
                    return ship;
            }
        }
    } else {
        while (true) {
            // значит нос корабля сверху
            point = QPoint(point.x(), point.y() - 1);

            for (Ship* ship : flot) {
                if (ship->getCoords() == point)
                    return ship;
            }
        }
    }

    qDebug() << "Не нашел корабль..";
    return nullptr;
}












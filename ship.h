#ifndef SHIP_H
#define SHIP_H

#include <QDebug>
#include <QPoint>

class Ship
{
protected:
    int weight;
    QPoint coords;
    QVector<bool> shipPartsState;
    bool orientation; // 1 - horizontal, 0 - vetrical

public:
    Ship() {};

    int getWeight();
    QVector<bool> getShipPartsState();
    void setCoords(QPoint point);
    QPoint getCoords();
};


class OnePartShip : public Ship {
public:
    OnePartShip() {
        weight = 1;

        for (int i {0}; i < weight; i++) {
            shipPartsState.push_back(1);
        }
    }
};


class TwoPartShip : public Ship {
public:
    TwoPartShip() {
        weight = 2;

        for (int i {0}; i < weight; i++) {
            shipPartsState.push_back(1);
        }
    }
};


class ThreePartShip : public Ship {
public:
    ThreePartShip() {
        weight = 3;

        for (int i {0}; i < weight; i++) {
            shipPartsState.push_back(1);
        }
    }
};


class FourPartShip : public Ship {
public:
    FourPartShip() {
        weight = 4;

        for (int i {0}; i < weight; i++) {
            shipPartsState.push_back(1);
        }
    }
};

#endif // SHIP_H

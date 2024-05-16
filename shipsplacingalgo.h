#ifndef SHIPSPLACINGALGO_H
#define SHIPSPLACINGALGO_H

#include <QDebug>

class ShipsPlacingAlgo
{
public:
    virtual ~ShipsPlacingAlgo() {};
    virtual void fillBoard() = 0;

};


class RandomPlacingAlgo : public ShipsPlacingAlgo {
public:
    void fillBoard() override {
        qDebug() << "Рандомная расстановка кораблей";
    }
};

class ManualPlacingAlgo : public ShipsPlacingAlgo {
public:
    void fillBoard() override {
        qDebug() << "Ручная расстановка кораблей";
    }
};

#endif // SHIPSPLACINGALGO_H

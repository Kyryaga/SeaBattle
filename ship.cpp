#include "ship.h"


int Ship::getWeight()
{
    return weight;
}

QVector<bool> Ship::getShipPartsState()
{
    return shipPartsState;
}

void Ship::setCoords(QPoint point)
{
    coords = point;
}

QPoint Ship::getCoords()
{
    return coords;
}

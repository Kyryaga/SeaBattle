#include "shotsstrategy.h"



int ManualShotStrategy::shot(Player *player, QPoint point)
{
    qDebug() << "Ручной выстрел по координатам: " << point.x() << " " << point.y();

    return 0;
}

int FullRandomShotStrategy::shot(Player *player, QPoint point)
{
    qDebug() << "FULL рандомный выстрел";

    return 0;
}

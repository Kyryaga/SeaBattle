#include "shotsstrategy.h"



QPoint ManualShotStrategy::shot(QPoint point)
{
    return point;
}

QPoint FullRandomShotStrategy::shot(QPoint point)
{
    qDebug() << "FULL рандомный выстрел(обычно для бота)";
    srand(time(NULL));

    return QPoint(rand() % 10, rand() % 10);
}

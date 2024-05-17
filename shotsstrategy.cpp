#include "shotsstrategy.h"



QPoint ManualShotStrategy::shot(QPoint point)
{
    return point;
}

QPoint FullRandomShotStrategy::shot(QPoint point)
{
    srand(time(NULL));

    return QPoint(rand() % 10, rand() % 10);
}

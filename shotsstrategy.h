#ifndef SHOTSSTRATEGY_H
#define SHOTSSTRATEGY_H
#include <QPoint>
#include <QDebug>


class ShotsStrategy
{
public:
    // функция будет просто возвращать QPoint, а в gameController уже будет все обрабатываться
    virtual QPoint shot(QPoint point = QPoint(0, 0)) = 0;
};


class ManualShotStrategy : public ShotsStrategy {
public:
    QPoint shot(QPoint point = QPoint(0, 0)) override;
};

class FullRandomShotStrategy : public ShotsStrategy {
public:
    QPoint shot(QPoint point = QPoint(0, 0)) override;
};

#endif // SHOTSSTRATEGY_H

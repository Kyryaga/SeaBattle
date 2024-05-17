#ifndef SHOTSSTRATEGY_H
#define SHOTSSTRATEGY_H
#include <QPoint>
#include <QDebug>

class Player;

class ShotsStrategy
{
public:
    virtual int shot(Player* player, QPoint point = QPoint(0, 0)) = 0;
};


class ManualShotStrategy : public ShotsStrategy {
public:
    int shot(Player *player, QPoint point = QPoint(0, 0)) override;
};

class FullRandomShotStrategy : public ShotsStrategy {
public:
    int shot(Player *player, QPoint point = QPoint(0, 0)) override;
};

#endif // SHOTSSTRATEGY_H

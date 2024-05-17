#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "Defines.h"
#include "shotsstrategy.h"


class Player
{
public:
    Player();
    virtual ~Player();

    virtual Ship* createShip(int w) = 0;

    void createFlot();

    Board *getBoard();

    QPoint performShot(QPoint point = QPoint(-1, -1));

protected:
    Board* board;

    ShotsStrategy* shotS;
};


class HumanPlayer : public Player {
public:
    HumanPlayer() {
        shotS = new ManualShotStrategy();
    };

    Ship* createShip(int w) override;
};


class AIPlayer : public Player {
public:
    AIPlayer() {
        shotS = new FullRandomShotStrategy();
    };

    Ship* createShip(int w) override;
};

#endif // PLAYER_H

#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "Defines.h"


class Player
{
public:
    Player();
    virtual ~Player();

    virtual Ship* createShip(int w) = 0;

    void createFlot();

    Board *getBoard();

private:
    Board* board;
};


class HumanPlayer : public Player {
public:
    HumanPlayer() {};

    Ship* createShip(int w) override;
};


class AIPlayer : public Player {
public:
    AIPlayer() {};

    Ship* createShip(int w) override;
};

#endif // PLAYER_H

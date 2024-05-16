#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "player.h"

class GameController
{
public:
    GameController();
    ~GameController();

    enum GameState {
        SHIPS_PLACING,
        PLAYER_TURN,
        ENEMY_TURN
    };

    GameState getGameState();

    void createFlots(); // создает все корабли для обоих игроков

private:
    GameState gameState;

    Player* player;
    Player* bot;
};

#endif // GAMECONTROLLER_H

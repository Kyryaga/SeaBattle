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

    int getPlayerShipCellsCount();

    bool isEmptyCell(QPoint point);

    void setCellState(QPoint point, int stateNum);

    void printAllCellStates();

    QVector<Cell> getAllCells();

private:
    GameState gameState;

    Player* player;
    Player* bot;
};

#endif // GAMECONTROLLER_H

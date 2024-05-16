#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "player.h"
#include <time.h>

enum GameState {
    SHIPS_PLACING,
    PLAYER_TURN,
    ENEMY_TURN
};

class GameController
{
public:
    GameController();
    ~GameController();

    GameState getGameState();

    void createFlots(); // создает все корабли для обоих игроков

    int getPlayerShipCellsCount();

    int getBotShipCellsCount();

    bool isPlayerEmptyCell(QPoint point);

    bool isBotEmptyCell(QPoint point);

    void setPlayerCellState(QPoint point, int stateNum);

    void setBotCellState(QPoint point, int stateNum);

    void printPlayerAllCellStates();

    void printBotAllCellStates();

    QVector<Cell> getPlayerAllCells();

    QVector<Cell> getBotAllCells();

    bool checkPlayerShipPlacement();

    bool checkBotShipPlacement();

    void syncPlayerShipsCells();

    void setGameState(GameState newState);

    void botRandomShipsPlacing();

private:
    GameState gameState;

    Player* player;
    Player* bot;
};

#endif // GAMECONTROLLER_H

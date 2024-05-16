#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "player.h"

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

    // начало проверки размещения кораблей
    bool checkPlayerShipPlacement();

    bool checkBotShipPlacement();
    // окончание проверки размещения кораблей

    void setGameState(GameState newState);

private:
    GameState gameState;

    Player* player;
    Player* bot;
};

#endif // GAMECONTROLLER_H

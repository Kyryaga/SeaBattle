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

    bool isEmptyCell(QPoint point);

    void setCellState(QPoint point, int stateNum);

    void printAllCellStates();

    QVector<Cell> getAllCells();

    // начало проверки размещения кораблей
    bool checkShipPlacement();

    int shipNum(int size);

    bool isShip(int size, int x, int y);
    // окончание проверки размещения кораблей

    void setGameState(GameState newState);

private:
    GameState gameState;

    Player* player;
    Player* bot;
};

#endif // GAMECONTROLLER_H

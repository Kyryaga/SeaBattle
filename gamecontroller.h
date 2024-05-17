#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "player.h"
#include <time.h>
#include <QLabel>

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

    Cell getBotCellState(QPoint point);

    Cell getPlayerCellState(QPoint point);

    void printPlayerAllCellStates();

    void printBotAllCellStates();

    QVector<Cell> getPlayerAllCells();

    QVector<Cell> getBotAllCells();

    bool checkPlayerShipPlacement();

    bool checkBotShipPlacement();

    void syncPlayerShipsCells();

    void syncBotShipsCells();

    void setGameState(GameState newState);

    void botRandomShipsPlacing();

    void playerShot(QPoint point);

    void botShot();

    QLabel *infoLabel;
private:
    GameState gameState;

    Player* player;
    Player* bot;
};

#endif // GAMECONTROLLER_H

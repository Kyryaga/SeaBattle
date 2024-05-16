#include "gamecontroller.h"

GameController::GameController() {
    gameState = GameState::SHIPS_PLACING;

    player = new HumanPlayer();
    bot = new AIPlayer();

    createFlots();
}

GameController::~GameController()
{
    delete player;
    delete bot;
}


GameState GameController::getGameState()
{
    return gameState;
}

void GameController::createFlots()
{
    player->createFlot();
    bot->createFlot();
}


int getShipCellsCount(Player* somePlayer)
{
    int count = 0;

    Board* board = somePlayer->getBoard();

    for (int i {0}; i < 10; i++) {
        for (int j {0}; j < 10; j++) {
            if (board->getCellState(QPoint(j, i)) == Cell::SHIP)
                count++;
        }
    }

    return count;
}

int GameController::getPlayerShipCellsCount()
{
    return getShipCellsCount(player);
}

int GameController::getBotShipCellsCount()
{
    return getShipCellsCount(bot);
}


bool isEmptyCell(Player* somePlayer, QPoint point)
{
    Board* board = somePlayer->getBoard();

    return board->getCellState(point) == Cell::EMPTY;
}

bool GameController::isPlayerEmptyCell(QPoint point)
{
    return isEmptyCell(player, point);
}

bool GameController::isBotEmptyCell(QPoint point)
{
    return isEmptyCell(bot, point);
}


void setCellState(Player* somePlayer, QPoint point, int stateNum)
{
    Board* board = somePlayer->getBoard();

    board->setCellState(point, static_cast<Cell>(stateNum));
}

void GameController::setBotCellState(QPoint point, int stateNum)
{
    return setCellState(bot, point, stateNum);
}

void GameController::setPlayerCellState(QPoint point, int stateNum)
{
    return setCellState(player, point, stateNum);
}

void printAllCellStates(Player* somePlayer)
{
    somePlayer->getBoard()->printBoardStates();
}

void GameController::printPlayerAllCellStates()
{
    printAllCellStates(player);
}

void GameController::printBotAllCellStates()
{
    printAllCellStates(bot);
}

QVector<Cell> getAllCells(Player* somePlayer)
{
    return somePlayer->getBoard()->getCells();
}

QVector<Cell> GameController::getPlayerAllCells()
{
    return getAllCells(player);
}

QVector<Cell> GameController::getBotAllCells()
{
    return getAllCells(bot);
}


bool isShip(Player* somePlayer, int size, int x, int y) {
    Board* board = somePlayer->getBoard();

    // left field !clear
    if (x > 0 && board->getCellState(QPoint(x - 1, y)) != Cell::EMPTY)
        return false;

    // up field !clear
    if (y > 0 && board->getCellState(QPoint(x, y - 1)) != Cell::EMPTY)
        return false;

    // no ship here
    if (board->getCellState(QPoint(x, y)) == Cell::EMPTY)
        return false;

    int tmp = x;
    int num = 0;

    // checking in right direction
    while (board->getCellState(QPoint(tmp, y)) != Cell::EMPTY && tmp < 10) {
        tmp++;
        num++;
    }

    if (num == size) {
        if (board->getCellState(QPoint(x, y + 1)) != Cell::EMPTY)
            return false;

        if (board->getCellState(QPoint(x - 1, y - 1)) != Cell::EMPTY || board->getCellState(QPoint(x - 1, y + 1)) != Cell::EMPTY
            || board->getCellState(QPoint(x + size, y - 1)) != Cell::EMPTY || board->getCellState(QPoint(x + size, y + 1)) != Cell::EMPTY)
            return false;

        return true;
    }

    tmp = y;
    num = 0;

    // checking in down direction
    while (board->getCellState(QPoint(x, tmp)) != Cell::EMPTY && tmp < 10) {
        tmp++;
        num++;
    }

    if (num == size) {
        if (board->getCellState(QPoint(x + 1, y)) != Cell::EMPTY)
            return false;

        if (board->getCellState(QPoint(x - 1, y - 1)) != Cell::EMPTY || board->getCellState(QPoint(x + 1, y - 1)) != Cell::EMPTY
            || board->getCellState(QPoint(x - 1, y + size)) != Cell::EMPTY || board->getCellState(QPoint(x + 1, y + size)) != Cell::EMPTY)
            return false;

        return true;
    }

    return false;
}

int shipNum(Player* somePlayer, int size) {
    int shipNumber = 0;

    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            if(isShip(somePlayer, size, j, i))
                shipNumber++;

    return shipNumber;
}

bool checkShipPlacement(Player* somePlayer)
{
    // проверка на кол-во кораблей, должно быть 20
    if (getShipCellsCount(somePlayer) == 20) {
        if (shipNum(somePlayer, 1) == 4 &&
            shipNum(somePlayer, 2) == 3 &&
            shipNum(somePlayer, 3) == 2 &&
            shipNum(somePlayer, 4) == 1) {
            qDebug() << "КОРРЕКТНАЯ РАССТАНОВКА КОРАБЛЕЙ\n";

            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}


bool GameController::checkPlayerShipPlacement()
{
    return checkShipPlacement(player);
}

bool GameController::checkBotShipPlacement()
{
    return checkShipPlacement(bot);
}

void GameController::setGameState(GameState newState)
{
    gameState = newState;
}














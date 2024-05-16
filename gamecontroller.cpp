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

int GameController::getPlayerShipCellsCount()
{
    int count = 0;

    Board* board = player->getBoard();

    for (int i {0}; i < 10; i++) {
        for (int j {0}; j < 10; j++) {
            if (board->getCellState(QPoint(j, i)) == Cell::SHIP)
                count++;
        }
    }

    return count;
}

bool GameController::isEmptyCell(QPoint point)
{
    Board* board = player->getBoard();

    return board->getCellState(point) == Cell::EMPTY;
}


void GameController::setCellState(QPoint point, int stateNum)
{
    Board* board = player->getBoard();

    board->setCellState(point, static_cast<Cell>(stateNum));
}

void GameController::printAllCellStates()
{
    player->getBoard()->printBoardStates();
}

QVector<Cell> GameController::getAllCells()
{
    return player->getBoard()->getCells();
}

bool GameController::checkShipPlacement()
{
    // проверка на кол-во кораблей, должно быть 20
    if (getPlayerShipCellsCount() == 20) {
        if (shipNum(1) == 4 &&
            shipNum(2) == 3 &&
            shipNum(3) == 2 &&
            shipNum(4) == 1) {
            qDebug() << "КОРРЕКТНАЯ РАССТАНОВКА КОРАБЛЕЙ\n";

            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}


int GameController::shipNum(int size) {
    int shipNumber = 0;

    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            if(isShip(size, j, i))
                shipNumber++;

    return shipNumber;
}


bool GameController::isShip(int size, int x, int y) {
    Board* board = player->getBoard();

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

void GameController::setGameState(GameState newState)
{
    gameState = newState;
}














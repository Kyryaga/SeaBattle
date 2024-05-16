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


GameController::GameState GameController::getGameState()
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

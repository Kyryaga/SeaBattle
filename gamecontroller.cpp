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

Cell getCellState(QPoint point, Player* somePlayer) {
    Board *board = somePlayer->getBoard();

    return board->getCellState(point);
}

Cell GameController::getBotCellState(QPoint point)
{
    return getCellState(point, bot);
}

Cell GameController::getPlayerCellState(QPoint point)
{
    return getCellState(point, player);
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


void syncShipsCells(Player* somePlayer) {
    Board* board = somePlayer->getBoard();

    QPoint fourPartShip;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (isShip(somePlayer, 4, j, i)) {
                fourPartShip.setX(j);
                fourPartShip.setY(i);
            }

    QPoint threePartShip1(-1, -1);
    QPoint threePartShip2(-1, -1);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (isShip(somePlayer, 3, j, i)) {
                if (threePartShip1.x() == -1) {
                    threePartShip1.setX(j);
                    threePartShip1.setY(i);
                } else {
                    threePartShip2.setX(j);
                    threePartShip2.setY(i);
                }
            }

    QPoint twoPartShip1(-1, -1);
    QPoint twoPartShip2(-1, -1);
    QPoint twoPartShip3(-1, -1);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (isShip(somePlayer, 2, j, i)) {
                if (twoPartShip1.x() == -1) {
                    twoPartShip1.setX(j);
                    twoPartShip1.setY(i);
                } else if (twoPartShip2.x() == -1) {
                    twoPartShip2.setX(j);
                    twoPartShip2.setY(i);
                } else {
                    twoPartShip3.setX(j);
                    twoPartShip3.setY(i);
                }
            }

    QPoint onePartShip1(-1, -1);
    QPoint onePartShip2(-1, -1);
    QPoint onePartShip3(-1, -1);
    QPoint onePartShip4(-1, -1);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (isShip(somePlayer, 1, j, i)) {
                if (onePartShip1.x() == -1) {
                    onePartShip1.setX(j);
                    onePartShip1.setY(i);
                } else if (onePartShip2.x() == -1) {
                    onePartShip2.setX(j);
                    onePartShip2.setY(i);
                } else if (onePartShip3.x() == -1){
                    onePartShip3.setX(j);
                    onePartShip3.setY(i);
                } else {
                    onePartShip4.setX(j);
                    onePartShip4.setY(i);
                }
            }

    for (Ship* ship : board->getFlot()) {
        if (ship->getWeight() == 4) {
            ship->setCoords(fourPartShip);
        } else if (ship->getWeight() == 3) {
            if (threePartShip1.x() != -1) {
                ship->setCoords(threePartShip1);
                threePartShip1.setX(-1);
            } else {
                ship->setCoords(threePartShip2);
            }
        } else if (ship->getWeight() == 2) {
            if (twoPartShip1.x() != -1) {
                ship->setCoords(twoPartShip1);
                twoPartShip1.setX(-1);
            } else if (twoPartShip2.x() != -1) {
                ship->setCoords(twoPartShip2);
                twoPartShip2.setX(-1);
            } else {
                ship->setCoords(twoPartShip3);
            }
        } else {
            if (onePartShip1.x() != -1) {
                ship->setCoords(onePartShip1);
                onePartShip1.setX(-1);
            } else if (onePartShip2.x() != -1) {
                ship->setCoords(onePartShip2);
                onePartShip2.setX(-1);
            } else if (onePartShip3.x() != -1) {
                ship->setCoords(onePartShip3);
                onePartShip3.setX(-1);
            } else {
                ship->setCoords(onePartShip4);
            }
        }
    }

    // корабли синхронизированы
    board->prettyPrintFlot();
}



void GameController::syncPlayerShipsCells()
{
    return syncShipsCells(player);
}

void GameController::syncBotShipsCells()
{
    return syncShipsCells(bot);
}

void GameController::setGameState(GameState newState)
{
    gameState = newState;
}

// только горизонтальная ориетация
void GameController::botRandomShipsPlacing()
{
    Board* board = bot->getBoard();
    srand(time(NULL));


    // берем 4-х палубник, генерим для него позицию, проверяем, можно ли поставить его
    QPoint fourPartShip;

    while (true) {
        fourPartShip.setX(rand() % 10);
        fourPartShip.setY(rand() % 10);

        if (fourPartShip.x() < 7) {
            board->setCellState(QPoint(fourPartShip.x(), fourPartShip.y()), Cell::SHIP);
            board->setCellState(QPoint(fourPartShip.x() + 1, fourPartShip.y()), Cell::SHIP);
            board->setCellState(QPoint(fourPartShip.x() + 2, fourPartShip.y()), Cell::SHIP);
            board->setCellState(QPoint(fourPartShip.x() + 3, fourPartShip.y()), Cell::SHIP);

            if (isShip(bot, 4, fourPartShip.x(), fourPartShip.y()))
                break;
            else {
                board->setCellState(QPoint(fourPartShip.x(), fourPartShip.y()), Cell::EMPTY);
                board->setCellState(QPoint(fourPartShip.x() + 1, fourPartShip.y()), Cell::EMPTY);
                board->setCellState(QPoint(fourPartShip.x() + 2, fourPartShip.y()), Cell::EMPTY);
                board->setCellState(QPoint(fourPartShip.x() + 3, fourPartShip.y()), Cell::EMPTY);
            }
        }
    }


    QPoint threePartShip1(-1, -1);
    QPoint threePartShip2(-1, -1);

    for (int i {0}; i < 2; i++) {
        while (true) {
            if (threePartShip1.x() == -1) {
                threePartShip1.setX(rand() % 10);
                threePartShip1.setY(rand() % 10);

                if (threePartShip1.x() < 8 && board->getCellState(threePartShip1) == Cell::EMPTY
                    && board->getCellState(QPoint(threePartShip1.x() + 1, threePartShip1.y())) == Cell::EMPTY
                    && board->getCellState(QPoint(threePartShip1.x() + 2, threePartShip1.y())) == Cell::EMPTY) {

                    board->setCellState(QPoint(threePartShip1.x(), threePartShip1.y()), Cell::SHIP);
                    board->setCellState(QPoint(threePartShip1.x() + 1, threePartShip1.y()), Cell::SHIP);
                    board->setCellState(QPoint(threePartShip1.x() + 2, threePartShip1.y()), Cell::SHIP);

                    if (isShip(bot, 3, threePartShip1.x(), threePartShip1.y())) {

                        break;
                    }
                    else {
                        board->setCellState(QPoint(threePartShip1.x(), threePartShip1.y()), Cell::EMPTY);
                        board->setCellState(QPoint(threePartShip1.x() + 1, threePartShip1.y()), Cell::EMPTY);
                        board->setCellState(QPoint(threePartShip1.x() + 2, threePartShip1.y()), Cell::EMPTY);
                    }
                }

                threePartShip1.setX(-1);
            } else {
                threePartShip2.setX(rand() % 10);
                threePartShip2.setY(rand() % 10);

                if (threePartShip2.x() < 8 && board->getCellState(threePartShip2) == Cell::EMPTY
                    && board->getCellState(QPoint(threePartShip2.x() + 1, threePartShip2.y())) == Cell::EMPTY
                    && board->getCellState(QPoint(threePartShip2.x() + 2, threePartShip2.y())) == Cell::EMPTY) {

                    board->setCellState(QPoint(threePartShip2.x(), threePartShip2.y()), Cell::SHIP);
                    board->setCellState(QPoint(threePartShip2.x() + 1, threePartShip2.y()), Cell::SHIP);
                    board->setCellState(QPoint(threePartShip2.x() + 2, threePartShip2.y()), Cell::SHIP);

                    if (isShip(bot, 3, threePartShip2.x(), threePartShip2.y())) {

                        break;
                    }
                    else {
                        board->setCellState(QPoint(threePartShip2.x(), threePartShip2.y()), Cell::EMPTY);
                        board->setCellState(QPoint(threePartShip2.x() + 1, threePartShip2.y()), Cell::EMPTY);
                        board->setCellState(QPoint(threePartShip2.x() + 2, threePartShip2.y()), Cell::EMPTY);
                    }
                }

                threePartShip2.setX(-1);
            }
        }
    }

    QPoint twoPartShip1(-1, -1);
    QPoint twoPartShip2(-1, -1);
    QPoint twoPartShip3(-1, -1);

    for (int i {0}; i < 3; i++) {
        while (true) {
            if (twoPartShip1.x() == -1) {
                twoPartShip1.setX(rand() % 10);
                twoPartShip1.setY(rand() % 10);

                if (twoPartShip1.x() < 9 && board->getCellState(twoPartShip1) == Cell::EMPTY
                    && board->getCellState(QPoint(twoPartShip1.x() + 1, twoPartShip1.y())) == Cell::EMPTY) {

                    board->setCellState(QPoint(twoPartShip1.x(), twoPartShip1.y()), Cell::SHIP);
                    board->setCellState(QPoint(twoPartShip1.x() + 1, twoPartShip1.y()), Cell::SHIP);

                    if (isShip(bot, 2, twoPartShip1.x(), twoPartShip1.y())) {

                        break;
                    }
                    else {
                        board->setCellState(QPoint(twoPartShip1.x(), twoPartShip1.y()), Cell::EMPTY);
                        board->setCellState(QPoint(twoPartShip1.x() + 1, twoPartShip1.y()), Cell::EMPTY);
                    }
                }

                twoPartShip1.setX(-1);
            } else if (twoPartShip2.x() == - 1){
                twoPartShip2.setX(rand() % 10);
                twoPartShip2.setY(rand() % 10);

                if (twoPartShip2.x() < 9 && board->getCellState(twoPartShip2) == Cell::EMPTY
                    && board->getCellState(QPoint(twoPartShip2.x() + 1, twoPartShip2.y())) == Cell::EMPTY) {

                    board->setCellState(QPoint(twoPartShip2.x(), twoPartShip2.y()), Cell::SHIP);
                    board->setCellState(QPoint(twoPartShip2.x() + 1, twoPartShip2.y()), Cell::SHIP);

                    if (isShip(bot, 2, twoPartShip2.x(), twoPartShip2.y())) {

                        break;
                    }
                    else {
                        board->setCellState(QPoint(twoPartShip2.x(), twoPartShip2.y()), Cell::EMPTY);
                        board->setCellState(QPoint(twoPartShip2.x() + 1, twoPartShip2.y()), Cell::EMPTY);
                    }
                }

                twoPartShip2.setX(-1);
            } else {
                twoPartShip3.setX(rand() % 10);
                twoPartShip3.setY(rand() % 10);

                if (twoPartShip3.x() < 9 && board->getCellState(twoPartShip3) == Cell::EMPTY
                    && board->getCellState(QPoint(twoPartShip3.x() + 1, twoPartShip3.y())) == Cell::EMPTY) {

                    board->setCellState(QPoint(twoPartShip3.x(), twoPartShip3.y()), Cell::SHIP);
                    board->setCellState(QPoint(twoPartShip3.x() + 1, twoPartShip3.y()), Cell::SHIP);

                    if (isShip(bot, 2, twoPartShip3.x(), twoPartShip3.y())) {

                        break;
                    }
                    else {
                        board->setCellState(QPoint(twoPartShip3.x(), twoPartShip3.y()), Cell::EMPTY);
                        board->setCellState(QPoint(twoPartShip3.x() + 1, twoPartShip3.y()), Cell::EMPTY);
                    }
                }

                twoPartShip3.setX(-1);
            }
        }
    }

    // генерация однопалубников - используем другой метод: простой перебор
    while (!checkBotShipPlacement()) {
        QPoint onePartShip(rand() % 10, rand() % 10);

        if (board->getCellState(onePartShip) != Cell::EMPTY)
            continue;

        board->setCellState(onePartShip, Cell::SHIP);

        if (!isShip(bot, 1, onePartShip.x(), onePartShip.y()))
            board->setCellState(onePartShip, Cell::EMPTY);
    }

    // синхронизация
    syncBotShipsCells();

}

void GameController::swapGameState() {
    if (getGameState() == GameState::ENEMY_TURN)
        setGameState(GameState::PLAYER_TURN);
    else if (getGameState() == GameState::PLAYER_TURN){
        setGameState(GameState::ENEMY_TURN);
    }
}


void GameController::takeShot(Player* whoShots, Player* whoseField, QPoint point) {
    Board* board = whoseField->getBoard();
    QPoint shotedPoint = whoShots->performShot(point);

    qDebug() << "Статус выстрела: " << shotedPoint;

    if (board->getCellState(shotedPoint) == Cell::EMPTY) {
        board->setCellState(shotedPoint, Cell::DOT);
        // TODO: переход к ходу бота
        swapGameState();
        if (getGameState() == GameState::ENEMY_TURN)
            infoLabel->setText("Ход Бота!");
        else {
            infoLabel->setText("Ваш ход!");
        }

    } else if (board->getCellState(shotedPoint) == Cell::SHIP) {
        // обработка попадания по кораблю
        // если корабль подбили - поставить Cell::DAMAGED, если убили - DEAD

        Ship* shotedShip = board->getShipByCell(shotedPoint);
        shotedShip->shipDamage();

        int shipHealth = shotedShip->getHealth();

        board->setCellState(shotedPoint, Cell::DAMAGED);

        if (shipHealth != 0) {
            // не добили
            qDebug() << "Подбили" << shotedShip->getWeight() << "палубник";
        } else {
            // убили
            // установка всех клеток, пренадлежащих кораблю в статус DEAD
            if (board->getCellState(QPoint(shotedShip->getCoords().x() + 1, shotedShip->getCoords().y())) == Cell::DAMAGED) {
                // ориентация горизонтальная
                for (int i {0}; i < shotedShip->getWeight(); i++) {
                    board->setCellState(QPoint(shotedShip->getCoords().x() + i, shotedShip->getCoords().y()), Cell::DEAD);
                }
            } else {
                for (int i {0}; i < shotedShip->getWeight(); i++) {
                    board->setCellState(QPoint(shotedShip->getCoords().x(), shotedShip->getCoords().y() + i), Cell::DEAD);
                }
            }

            qDebug() << "Убили" << shotedShip->getWeight() << "палубник";

        }
    }
}

void GameController::playerShot(QPoint point)
{
    takeShot(player, bot, point);

}

void GameController::botShot()
{
    takeShot(bot, player, QPoint(-1, -1));

    sleep(2);
}














#include "player.h"

Player::Player() {
    board = new Board();
}

Player::~Player() {}

void Player::createFlot()
{
    // четырехпалубники
    for (int i {0}; i < SHIPS4COUNT; i++) {
        board->addShip(createShip(4));
    }

    // трехпалубники
    for (int i {0}; i < SHIPS3COUNT; i++) {
        board->addShip(createShip(3));
    }

    // двухпалубники
    for (int i {0}; i < SHIPS2COUNT; i++) {
        board->addShip(createShip(2));
    }

    // однопалубники
    for (int i {0}; i < SHIPS1COUNT; i++) {
        board->addShip(createShip(1));
    }
}

Board *Player::getBoard()
{
    return board;
}

QPoint Player::performShot(QPoint point)
{
    return shotS->shot(point);
}



Ship* HumanPlayer::createShip(int w)
{
    if (w == 1) {
        return new OnePartShip();
    } else if (w == 2) {
        return new TwoPartShip();
    } else if (w == 3) {
        return new ThreePartShip();
    } else if (w == 4) {
        return new FourPartShip();
    } else {
        qDebug() << "Введен некорректный вес корабля";
        return nullptr;
    }
}

Ship* AIPlayer::createShip(int w)
{
    if (w == 1) {
        return new OnePartShip();
    } else if (w == 2) {
        return new TwoPartShip();
    } else if (w == 3) {
        return new ThreePartShip();
    } else if (w == 4) {
        return new FourPartShip();
    } else {
        qDebug() << "Введен некорректный вес корабля";
        return nullptr;
    }
}


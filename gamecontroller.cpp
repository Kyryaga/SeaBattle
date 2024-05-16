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

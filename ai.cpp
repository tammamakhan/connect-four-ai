#include "ai.h"

#include <QDebug>

AI::AI() {
    playerNum_ = AI_PLAYER;
}

int AI::getNextMove() {
    return rand() % BOARD_COLS;
}

#include "gamescene.h"

GameScene::GameScene() {
    // Create empty board when game is initialized
    initializeBoard();

    // Initialize member variables
    mouseX_ = 0;
}

void GameScene::updateBoard() {
    // Make/wait for the next move

    // Check for victory

    // Draw the board
    drawBoard();
}


// -------------------------------------- PRIVATE FUNCTIONS --------------------------------------//

// Update the stored x position of the mouse
void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    mouseX_ = event->pos().x();

}

// Make the player's move if it is their turn
void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {

}




// Initialize the board 2d array with all EMPTY cells
void GameScene::initializeBoard() {
    for (int row = 0; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLS; col++) {
            board_[row][col] = EMPTY;
        }
    }
}

// Draw the game board and corresponding game pieces
// for the current state of the board
void GameScene::drawBoard() {
    // Draw the background board
    QPen backgroundPen(Qt::blue);
    QBrush backgroundBrush(Qt::blue);
    this->addRect(0,0,700,700, backgroundPen, backgroundBrush);

    // Draw in the game pieces
    for (int row = 0; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLS; col++) {
            // Set the brush color and fill each cell/piece accordingly
            QPen pen(Qt::black);
            if (board_[row][col] == EMPTY) {
                QBrush brush(Qt::black);
                this->addEllipse(2 + RADIUS * col,
                                 RADIUS + RADIUS * row,
                                 RADIUS - 4,
                                 RADIUS - 4,
                                 pen,
                                 brush);
            }
            if (board_[row][col] == PLAYER) {
                QBrush brush(Qt::yellow);
                this->addEllipse(2 + RADIUS * col,
                                 RADIUS + RADIUS * row,
                                 RADIUS - 4,
                                 RADIUS - 4,
                                 pen,
                                 brush);
            }
            if (board_[row][col] == ENEMY) {
                QBrush brush(Qt::red);
                this->addEllipse(2 + RADIUS * col,
                                 RADIUS + RADIUS * row,
                                 RADIUS - 4,
                                 RADIUS - 4,
                                 pen,
                                 brush);
            }

        }
    }
}

void GameScene::drawNextPiece() {
    int col = getColFromPos(mouseX_);

}

int GameScene::getColFromPos(int xPos) {

    // Mouse is not in a valid column
    return -1;
}

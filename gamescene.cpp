#include "gamescene.h"

#include <QDebug>

GameScene::GameScene() {
    // Create empty board when game is initialized
    initializeBoard();

    // Initialize member variables
    mouseX_ = 5 + RADIUS / 2;
    currentTurn_ = PLAYER;
}

void GameScene::updateBoard() {
    // Clear the current scene
    this->clear();

    // Check for victory

    // Draw the entire board
    drawBoard();
    drawNextPiece();
}

// Update the stored x position of the mouse
void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (currentTurn_ == PLAYER) {
        mouseX_ = event->scenePos().x();

        if (mouseX_ - RADIUS / 2 < 2) {
            mouseX_ = 2 + RADIUS / 2;
        }
        if (mouseX_ + RADIUS > 750) {
            mouseX_ = 750 - RADIUS;
        }
    }
}

// Make the player's move if it is their turn
void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (currentTurn_ == PLAYER && isInScreen(event->scenePos().x(), event->scenePos().y())) {
        // Get the column where the mouse is
        int col = getColFromPos(mouseX_);
        if (isValidCol(col)) {
            // Add player piece to column


            // Change current turn to enemy
            //currentTurn_ = ENEMY;
            qDebug() << "CLICK IN SCREEN" << event->scenePos().x() << event->scenePos().y();
        }
    }
    //qDebug() << "CLICK" << event->scenePos().x() << event->scenePos().y();
}

// -------------------------------------- HELPER FUNCTIONS --------------------------------------//

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
    this->addRect(0, 0, 700, 700, backgroundPen, backgroundBrush);

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

// Draw the next piece that follows the mouse if it is
// the player's turn
void GameScene::drawNextPiece() {
    if (currentTurn_ == PLAYER) {
        QBrush brush(Qt::yellow);
        QPen pen(Qt::yellow);
        this->addEllipse(mouseX_ - RADIUS / 2,
                         2,
                         RADIUS - 4,
                         RADIUS - 4,
                         pen,
                         brush);
    }
}

// Given the mouse's x position, return the
// corresponding column
int GameScene::getColFromPos(int xPos) {
    return ((this->width() - xPos + 1) * 7);
    // Mouse is not in a valid column
    return -1;
}

// Given a column, check if it is full or not already
bool GameScene::isValidCol(int col) {
    if (board_[0][col] == EMPTY) {
        return true;
    }
    return false;
}

// Given an x and y position, check if it is within the
// game screen
bool GameScene::isInScreen(int x, int y) {
    if (x > 0 && x < this->width()) {
        if (y > 0 && y < this->height()) {
            return true;
            qDebug() << "IN SCREEN";
        }
    }
    return false;
}

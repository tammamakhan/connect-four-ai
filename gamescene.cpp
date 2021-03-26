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

    // If it is the AI's turn, it will make its
    // next move
    if (currentTurn_ == AI) {
        // Get the next optimal move for the AI
        int nextAIMoveCol = makeAIMove();

        // Make sure that the column the AI has chosen is valid
        if (isValidCol(nextAIMoveCol)) {
            // Get the next row
            int nextAIMoveRow = getValidRow(nextAIMoveCol);

            // Update the board for the AI's move and
            // change turn to player's
            board_[nextAIMoveRow][nextAIMoveCol] = AI;
            currentTurn_ = PLAYER;
        }
    }

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
            // Get the row to place piece
            int row = getValidRow(col);

            // Update board with player's next move
            board_[row][col] = PLAYER;

            // Change current turn to enemy
            currentTurn_ = AI;
            qDebug() << "CLICK IN SCREEN" << event->scenePos().x() << event->scenePos().y();
        }
    }
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
            if (board_[row][col] == AI) {
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
    return xPos / RADIUS;
}

// Given a column, check if it is full or not already
bool GameScene::isValidCol(int col) {
    if (board_[0][col] == EMPTY) {
        return true;
    }
    return false;
}

int GameScene::getValidRow(int col) {
    int row = BOARD_ROWS - 1;
    for (; row >= 0; row--) {
        if (board_[row][col] == EMPTY) {
            break;
        }
    }
    return row;
}

// Given an x and y position, check if it is within the
// game screen
bool GameScene::isInScreen(int x, int y) {
    if (x > 0 && x < this->width()) {
        if (y > 0 && y < this->height()) {
            return true;
        }
    }
    return false;
}

// Uses the minimax algorithm with alpha beta pruning to decide
// which column to place the next piece
int GameScene::makeAIMove() {
    return rand() % BOARD_COLS;
}

#include "gamescene.h"

#include <QDebug>
#include <QGraphicsTextItem>

/*
 * Constructor for the GameScene class
*/
GameScene::GameScene() {
    // Initialize the game board
    game.initializeBoard();

    // Initialize member variables
    mouseX_ = 5 + RADIUS / 2;
}

/*
 *
*/
void GameScene::updateBoard() {
    // Check if the board is filled up
    if (game.isBoardFull()) {
        qDebug() << "Game Draw!";
    }
    // Update the game if it is still in progress
    if (game.inProgress_) {
        // Clear the game scene for the current game state
        this->clear();

        // Check if it is the AI's turn, and if so
        // let it make its move
        if (game.currentTurn_ == AI_PLAYER) {
            int aiMoveCol = game.ai.getNextMove(game.board_);
            if (game.isValidCol(aiMoveCol)){
                game.placePiece(AI_PLAYER, aiMoveCol);
            }

            // Check for winning move
            if (game.checkForWin(AI_PLAYER)) {
                game.inProgress_ = false;
                drawBoard();
                qDebug() << "You Lose!";
            } else {
                if (game.isValidCol(aiMoveCol)) {
                    game.currentTurn_ = PLAYER;
                }
            }
        }

        // Draw the game scene for the new board state
        drawBoard();

        // Check if it is the player's turn, and if so, display the
        // next game piece for them to place
        // This game piece will follow the mouse and upon clicking in
        // the game scene, will place the player's piece in that column
        // Mouse event handling can be seen below
        if (game.currentTurn_ == PLAYER) {
            drawNextPiece();
        }
    }
}

/*
 *
*/
void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (game.currentTurn_ == PLAYER && game.inProgress_) {
        mouseX_ = event->scenePos().x();

        if (mouseX_ - RADIUS / 2 < 2) {
            mouseX_ = 2 + RADIUS / 2;
        }
        if (mouseX_ + RADIUS > 750) {
            mouseX_ = 750 - RADIUS;
        }
    }
}

/*
 *
*/
void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    // First check that the game is in progress and it is the player's
    // turn
    if (game.currentTurn_ == PLAYER && game.inProgress_) {
        // Make sure the click occured in the game scene
        if (isInScreen(event->scenePos().x(), event->scenePos().y())) {
            int col = getColFromPos(mouseX_);
            game.placePiece(PLAYER, col);
            // Check if this is a winning move
            // If it is, we can end the game
            // Otherwise, it will now become the AI's turn
            if (game.checkForWin(PLAYER)) {
                game.inProgress_ = false;
                drawBoard();
                qDebug() << "You win!";
            } else {
                if (game.isValidCol(col)) {
                    game.currentTurn_ = AI_PLAYER;
                }
            }
        }
    }
}


/*
 * Draw the connect four game for the current state of
 * the board
*/
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
            if (game.board_[row][col] == EMPTY) {
                QBrush brush(Qt::black);
                this->addEllipse(2 + RADIUS * col,
                                 RADIUS + RADIUS * row,
                                 RADIUS - 4,
                                 RADIUS - 4,
                                 pen,
                                 brush);
            }
            if (game.board_[row][col] == PLAYER) {
                QBrush brush(Qt::yellow);
                this->addEllipse(2 + RADIUS * col,
                                 RADIUS + RADIUS * row,
                                 RADIUS - 4,
                                 RADIUS - 4,
                                 pen,
                                 brush);
            }
            if (game.board_[row][col] == AI_PLAYER) {
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

/*
 * Draw the next piece that follows the mouse if it is
 * the player's turn
*/
void GameScene::drawNextPiece() {
    QBrush brush(Qt::yellow);
    QPen pen(Qt::yellow);
    this->addEllipse(mouseX_ - RADIUS / 2,
                     2,
                     RADIUS - 4,
                     RADIUS - 4,
                     pen,
                     brush);
}

/*
 * Input:   x position
 * Output:  the column in which the inputted x position
 *          corresponds to on the board
*/
int GameScene::getColFromPos(int xPos) {
    return xPos / RADIUS;
}


/*
 * Input:   x and y position
 * Output:  true if the coordinates (x, y) are inside the screen,
 *          false otherwise
*/
bool GameScene::isInScreen(int x, int y) {
    if (x > 0 && x < this->width()) {
        if (y > 0 && y < this->height()) {
            return true;
        }
    }
    return false;
}


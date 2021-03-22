#include "game.h"

Game::Game() {

    // Initialize board with all empty spaces
    initializeBoard();

}

QRectF Game::boundingRect() const {
    return QRect(0, 0, 700, 700);
}

void Game::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // Initialize the background board
    QRectF background = boundingRect();
    QBrush backgroundBrush(Qt::cyan);

    // Draw in game board
    painter->fillRect(background, backgroundBrush);
    painter->drawRect(background);

    // Draw in each of the pieces for the current board state
    drawPieces(painter);
}

void Game::advance(int phase) {

}

// -------------------------------------- HELPER FUNCTIONS --------------------------------------//

// Set all cells of the board to EMPTY (0)
void Game::initializeBoard() {
    for (int row = 0; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLS; col++) {
            board_[row][col] = EMPTY;
        }
    }
}

// Draws each of the pieces on the board
void Game::drawPieces(QPainter *painter) {
    for (int row = 0; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLS; col++) {
            // Set the brush color to fill a cell/piece accordingly
            if (board_[row][col] == EMPTY) {
                painter->setBrush(Qt::white);
            }
            if (board_[row][col] == PLAYER) {
                painter->setBrush(Qt::yellow);
            }
            if (board_[row][col] == ENEMY) {
                painter->setBrush(Qt::red);
            }

            // Draw in the piece
            painter->drawEllipse(RADIUS * col, RADIUS + RADIUS * row, RADIUS, RADIUS);
        }
    }
}

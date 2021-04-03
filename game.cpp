#include "game.h"


/*
 * Constructor for the Game class
*/
Game::Game() {
    // Initialize board
    initializeBoard();

    // Initialize member variables
    currentTurn_ = PLAYER;
    inProgress_ = true;
}

/*
 *  Initialize the board 2d array with all EMPTY cells
*/
void Game::initializeBoard() {
    for (int row = 0; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLS; col++) {
            board_[row][col] = EMPTY;
        }
    }
}

/*
 * Input:   Player number and column number
 *
 * If the inputted column is valid, places the specified player's piece
 * in the next valid row for that column
*/
void Game::placePiece(int player, int col) {
    if (isValidCol(col)) {
        int row = getValidRow(col);
        board_[row][col] = player;
    }
}

/*
 *  Input:  column to check
 *  Output: true if a piece can be placed in the inputted column,
 *          false otherwise
*/
bool Game::isValidCol(int col) {
    if (board_[0][col] == EMPTY) {
        return true;
    }
    return false;
}

/*
 * Input:   column to check
 * Output:  the row index corresponding to the next empty space on the board
 *          for the inputted column
*/
int Game::getValidRow(int col) {
    int row = BOARD_ROWS - 1;
    for (; row >= 0; row--) {
        if (board_[row][col] == EMPTY) {
            break;
        }
    }
    return row;
}

/*
 *  Output: true if there are no more empty spaces left on the board,
 *          false otherwise
*/
bool Game::isBoardFull(void) {
    for (int col = 0; col < BOARD_COLS; col++) {
        if (board_[0][col] == EMPTY) {
            return false;
        }
    }
    return true;
}

bool Game::checkForWin(int player) {
    // Check horizontally for wins
    for (int row = 0; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLS - 3; col++) {
            if (board_[row][col] == player && board_[row][col+1] == player &&
                board_[row][col+2] == player && board_[row][col+3] == player) {
                return true;
            }
        }
    }

    // Check vertically for wins
    for (int row = 0; row < BOARD_ROWS - 3; row++) {
        for (int col = 0; col < BOARD_COLS; col++) {
            if (board_[row][col] == player && board_[row+1][col] == player &&
                board_[row+2][col] == player && board_[row+3][col] == player) {
                return true;
            }
        }
    }
    // Check right diaganols
    for (int row = 0; row < BOARD_ROWS - 3; row++) {
        for (int col = 0; col < BOARD_COLS - 3; col++) {
            if (board_[row][col] == player && board_[row+1][col+1] == player &&
                board_[row+2][col+2] == player && board_[row+3][col+3] == player) {
                return true;
            }
        }
    }
    // Check left diagonals
    for (int row = 3; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLS - 3; col++) {
            if (board_[row][col] == player && board_[row-1][col+1] == player &&
                board_[row-2][col+2] == player && board_[row-3][col+3] == player) {
                return true;
            }
        }
    }

    return false;
}





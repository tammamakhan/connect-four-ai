#include "ai.h"

#include <QDebug>

/*
 * Constructor for the AI class
*/
AI::AI() {
    playerNum_ = AI_PLAYER;
}

/*
 * Input:   connect four game board 2d array
 * Output:  integer corresponding to the most optimal column for the AI
 *          to place its next piece at the state of the inputted board.
 *          Uses the minimax with alpha-beta pruning to decide most optimal
 *          move.
*/
int AI::getNextMove(int board[BOARD_ROWS][BOARD_COLS]) {
    int** boardCopy = initializeCopy(board);
    int nextCol = minimax(boardCopy, 6, INT_MIN, INT_MAX, playerNum_).first;
    return nextCol;
}

/*
 * Implementation of the minimax with alpha-beta pruning algorithm for
 * connect four
 * Pseudocode can be found online
 *
 * Output format: pair<int, int>(column, score)
*/
std::pair<int, int> AI::minimax(int** board, int depth, int alpha, int beta, int player) {
    std::list<int> validColumns = getValidColumns(board);
    bool terminalState = isTerminalState(board);

    // If at a terminal state or max depth, we are at base case
    if (terminalState || depth == 0) {
        if (terminalState){
            if (isWin(board, AI_PLAYER)) {
                // If the AI player wins, maximum score
                return std::pair<int, int>(-1, INT_MAX);
            } else if (isWin(board, getOtherPlayer(PLAYER))){
                // If the AI player lost, minimum score
                return std::pair<int, int>(-1, INT_MIN);
            } else {
                // If game is over, board is full
                return std::pair<int, int>(-1, 0);
            }
        } else {
            // If at terminal state, evaluate the score for the current
            // board
            return std::pair<int, int>(-1, evaluate(board));
        }
    }
    // If it is the AI player's turn, we want to maximize score
    // Otherwise, we want to minimize the score
    if (player == playerNum_) {
        // Maximize score
        int value = INT_MIN;
        int nextCol = rand() % validColumns.size();

        // Consider all next possible moves
        for (int col: validColumns) {
            int row = getValidRow(board, col);
            int** boardCopy = copyBoard(board, row, col, player);
            int score = minimax(boardCopy, depth - 1, alpha, beta, getOtherPlayer(player)).second;
            if (score > value) {
                value = score;
                nextCol = col;
            }

            // Update alpha
            alpha = std::max(alpha, value);

            // Check for beta cutoff
            if (alpha >= beta) {
                break;
            }
        }
        return std::pair<int, int>(nextCol, value);
    } else {
        // Minimize score
        int value = INT_MAX;
        int nextCol = rand() % validColumns.size();

        // Consider all next possible moves
        for (int col: validColumns) {
            int row = getValidRow(board, col);
            int** boardCopy = copyBoard(board, row, col, player);
            int score = minimax(boardCopy, depth - 1, alpha, beta, getOtherPlayer(player)).second;
            if (score < value) {
                value = score;
                nextCol = col;
            }

            // Update beta
            beta = std::min(beta, value);

            // Check for alpha cutoff
            if (alpha >= beta) {
                break;
            }
        }
        return std::pair<int, int>(nextCol, value);
    }

}

/*
 * Input:   game board
 * Output:  an integer score for the AI player for the
 *          current state of the inputted board
*/
int AI::evaluate(int **board) {
    int score = 0;

    // Prioritize the middle of the board, since it gives the
    // most opportunities to win
    int middle = BOARD_COLS / 2;
    int centerWindow[BOARD_ROWS];
    int iter = sizeof(centerWindow) / sizeof(centerWindow[0]);
    for (int row = 0; row < BOARD_ROWS; row++) {
        centerWindow[row] = board[row][middle];
    }
    score += std::count(centerWindow, centerWindow + iter, playerNum_) * 5;

    // Score all windows horizontally
    for (int row = 0; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLS - 3; col++) {
            int window[] = {board[row][col], board[row][col+1], board[row][col+2], board[row][col+3]};
            score += evaluateWindow(window);
        }
    }

    // Score all windows vertically
    for (int row = 0; row < BOARD_ROWS - 3; row++) {
        for (int col = 0; col < BOARD_COLS; col++) {
            int window[] = {board[row][col], board[row+1][col], board[row+2][col], board[row+3][col]};
            score += evaluateWindow(window);
        }
    }
    // Score all right diagonal windows
    for (int row = 0; row < BOARD_ROWS - 3; row++) {
        for (int col = 0; col < BOARD_COLS - 3; col++) {
            int window[] = {board[row][col], board[row+1][col+1], board[row+2][col+2], board[row+3][col+3]};
            score += evaluateWindow(window);
        }
    }
    // Score all left diagonal windows
    for (int row = 3; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLS - 3; col++) {
            int window[] = {board[row][col], board[row-1][col+1], board[row-2][col+2], board[row-3][col+3]};
            score += evaluateWindow(window);
        }
    }
    return score;
}

/*
 * Input:   window of size WINDOW_SIZE which we want to evaluate
 * Output:  integer score of the inputted window
*/
int AI::evaluateWindow(int window[WINDOW_SIZE]) {
    int score = 0;
    int iter = sizeof(window) / sizeof(window[0]);

    if (std::count(window, window + iter, playerNum_) == 4) {
        // Window is entirely AI player's pieces, which is the best
        // possible scenario
        score += 50;
    } else if (std::count(window, window + iter, playerNum_) == 3
               && std::count(window, window + iter, EMPTY) == 1) {
        // Window has three of the AI player's pieces and one empty spot
        score += 10;
    } else if (std::count(window, window + iter, playerNum_) == 2
               && std::count(window, window + iter, EMPTY) == 2) {
        // Window has two of the AI player's pieces and two empty spots
        score += 5;
    }

    if (std::count(window, window + iter, PLAYER) == 3
            && std::count(window, window + iter, EMPTY) == 1) {
        // Window has three of the opponent's pieces and one empty spot
        // This is a bad scenario and we want to block it, so decrease score
        score -= 15;
    }
    return score;
}

/*
 * Input:   connect four game board
 * Output:  list containing all columns where a piece can
 *          still be placed
*/
std::list<int> AI::getValidColumns(int **board) {
    std::list<int> columns;
    for (int col = 0; col < BOARD_COLS; col++) {
        if (board[0][col] == EMPTY) {
            columns.push_back(col);
        }
    }
    return columns;
}

/*
 * Input:   column number
 * Output:  the row where a piece would land in if
 *          dropped in the inputted column
*/
int AI::getValidRow(int** board, int col) {
    int row = BOARD_ROWS - 1;
    for (; row >= 0; row--) {
        if (board[row][col] == EMPTY) {
            break;
        }
    }
    return row;
}

/*
 * Input:   a specified player (AI or Player)
 * Output:  player whose turn it is next
*/
int AI::getOtherPlayer(int player) {
    if (player == PLAYER) {
        return AI_PLAYER;
    }
    return PLAYER;
}

/*
 * Input:   game board
 * Output:  Returns true if the inputted board is a terminal
 *          state, otherwise false
*/
bool AI::isTerminalState(int** board) {
    return isWin(board, AI_PLAYER) || isWin(board, PLAYER) || isBoardFull(board);
}

/*
 * Input:   game board
 * Output:  true if the AI player is winning in the inputted
 *          board, false otherwise
*/
bool AI::isWin(int **board, int player) {
    // Check horizontally for wins
    for (int row = 0; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLS - 3; col++) {
            if (board[row][col] == player && board[row][col+1] == player &&
                board[row][col+2] == player && board[row][col+3] == player) {
                return true;
            }
        }
    }

    // Check vertically for wins
    for (int row = 0; row < BOARD_ROWS - 3; row++) {
        for (int col = 0; col < BOARD_COLS; col++) {
            if (board[row][col] == player && board[row+1][col] == player &&
                board[row+2][col] == player && board[row+3][col] == player) {
                return true;
            }
        }
    }
    // Check right diaganols
    for (int row = 0; row < BOARD_ROWS - 3; row++) {
        for (int col = 0; col < BOARD_COLS - 3; col++) {
            if (board[row][col] == player && board[row+1][col+1] == player &&
                board[row+2][col+2] == player && board[row+3][col+3] == player) {
                return true;
            }
        }
    }
    // Check left diagonals
    for (int row = 3; row < BOARD_ROWS; row++) {
        for (int col = 0; col < BOARD_COLS - 3; col++) {
            if (board[row][col] == player && board[row-1][col+1] == player &&
                board[row-2][col+2] == player && board[row-3][col+3] == player) {
                return true;
            }
        }
    }

    return false;
}

/*
 * Input:   game board
 * Output:  true if there are no empty space left on
 *          the board, false otherwise
*/
bool AI::isBoardFull(int **board) {
    for (int col = 0; col < BOARD_COLS; col++) {
        if (board[0][col] == EMPTY) {
            return false;
        }
    }
    return true;
}

/*
 * Input: 2d array of the board
 * Output: copy of the board
*/
int** AI::initializeCopy(int board[BOARD_ROWS][BOARD_COLS]) {
    int** boardCopy = new int*[BOARD_ROWS];

    for (int row = 0; row < BOARD_ROWS; row++) {
        boardCopy[row] = new int[BOARD_COLS];
        for (int col = 0; col < BOARD_COLS; col++) {
            boardCopy[row][col] = board[row][col];
        }
    }
    return boardCopy;
}

/*
 * Input: game board
 * Output: copy of the board
*/
int **AI::copyBoard(int **board, int row, int col, int player) {
    int** boardCopy = new int*[BOARD_ROWS];

    for (int r = 0; r < BOARD_ROWS; r++) {
        boardCopy[r] = new int[BOARD_COLS];
        for (int c = 0; c < BOARD_COLS; c++) {
            if (r == row && c == col) {
                boardCopy[r][c] = player;
            } else {
                boardCopy[r][c] = board[r][c];
            }
        }
    }
    return boardCopy;
}



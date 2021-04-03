#ifndef AI_H
#define AI_H

#define BOARD_ROWS  6
#define BOARD_COLS  7

#define EMPTY   0
#define PLAYER  1
#define AI_PLAYER   2

#define WINDOW_SIZE 4

#include <QDebug>

class AI {
public:
    AI();

    int playerNum_;

    int getNextMove(int board[BOARD_ROWS][BOARD_COLS]);

private:
    std::pair<int,int> minimax(int** board, int depth, int alpha, int beta, int player);
    int evaluate(int** board);
    int evaluateWindow(int window[WINDOW_SIZE]);
    std::list<int> getValidColumns(int** board);
    int getValidRow(int** board, int col);
    int getOtherPlayer(int player);
    bool isTerminalState(int** board);
    bool isWin(int** board, int player);
    bool isBoardFull(int** board);
    int** initializeCopy(int board[BOARD_ROWS][BOARD_COLS]);
    int** copyBoard(int** board, int row, int col, int player);
};

#endif // AI_H

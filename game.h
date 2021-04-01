#ifndef GAME_H
#define GAME_H

#include <ai.h>

class Game {
public:
    Game();

    AI ai;

    int board_[BOARD_ROWS][BOARD_COLS];
    int currentTurn_;
    bool inProgress_;

    void initializeBoard(void);
    void placePiece(int player, int col);
    void makeAIMove(void);
    bool isValidCol(int col);
    int getValidRow(int col);
    bool isBoardFull(void);
    bool checkForWin(int player);
};

#endif // GAME_H

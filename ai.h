#ifndef AI_H
#define AI_H

#define BOARD_ROWS  6
#define BOARD_COLS  7

#define EMPTY   0
#define PLAYER  1
#define AI_PLAYER   2

class AI {
public:
    AI();

    int playerNum_;

    int getNextMove(void);
};

#endif // AI_H

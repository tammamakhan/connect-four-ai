#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

#define BOARD_ROWS  6
#define BOARD_COLS  7

#define EMPTY   0
#define PLAYER  1
#define AI   2

#define RADIUS  100


class GameScene : public QGraphicsScene{
public:
    GameScene();
    void updateBoard(void);

private:
    int board_[BOARD_ROWS][BOARD_COLS];
    int mouseX_;
    int currentTurn_;
    bool gameInProgress_;

    void initializeBoard(void);
    void drawBoard(void);
    void drawNextPiece(void);
    int getColFromPos(int xPos);
    bool isValidCol(int col);
    int getValidRow(int col);
    bool isInScreen(int x, int y);
    int makeAIMove(void);
    bool checkForWin(int player);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GAMESCENE_H

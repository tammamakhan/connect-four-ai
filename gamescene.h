#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

#include <game.h>

#define RADIUS  100


class GameScene : public QGraphicsScene{
public:
    GameScene();

    Game game;

    void updateBoard(void);

private:
    int mouseX_;

    void drawBoard(void);
    void drawNextPiece(void);
    bool isInScreen(int x, int y);
    int getColFromPos(int xPos);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GAMESCENE_H

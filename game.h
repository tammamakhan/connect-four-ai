#ifndef GAME_H
#define GAME_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

#define BOARD_ROWS  6
#define BOARD_COLS  7

#define EMPTY   0
#define PLAYER  1
#define ENEMY   2

#define RADIUS  100

class Game : public QGraphicsItem {
public:
    Game();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void advance(int phase);

private:
    int board_[BOARD_ROWS][BOARD_COLS];

    void initializeBoard(void);
    void drawPieces(QPainter *painter);
};

#endif // GAME_H

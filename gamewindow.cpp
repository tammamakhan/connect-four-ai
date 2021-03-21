#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    gameScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(gameScene);

    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(3);

    ellipse = gameScene->addEllipse(10, 10, 100, 100, blackPen, redBrush);
}

GameWindow::~GameWindow()
{
    delete ui;
}


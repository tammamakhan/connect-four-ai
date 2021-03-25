#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::GameWindow) {
    ui->setupUi(this);

    scene = new GameScene();
    ui->graphicsView->setScene(scene);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));
    timer->start(100);

}

GameWindow::~GameWindow() {
    delete ui;
}

void GameWindow::slotTimer() {
    scene->updateBoard();
    qDebug() << "Updated...";
}


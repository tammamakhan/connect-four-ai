#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "game.h"

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::GameWindow) {
    ui->setupUi(this);

    // Create scene where game will take place
    gameScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(gameScene);

    // Define the Game object which will run the game and add
    // it to the scene
    Game *game = new Game();
    gameScene->addItem(game);


    // Create a timer that will update the game window every 100ms
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), gameScene, SLOT(advance()));
    timer->start(100);
}

GameWindow::~GameWindow()
{
    delete ui;
}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QPushButton>
#include <QCursor>
#include <QLabel>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <wood.h>
#include <pig.h>
#include <slingshot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void setAndCreate();

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void restart();
    void endgame();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QPushButton *endButton;
    QPushButton *restartButton;
   /* Pig *fatfat_1;
    Pig *fatfat_2;
    Wood *stick_1;
    Wood *stick_2;
    Wood *stick_3;
    Bird *birdie_1;
    Bird *birdie_2;
    Bird *birdie_3;
    Bird *birdie_4;*/
    bool fly;
    bool skill;
    int countdown;
    float xpos;
    float ypos;

};


#endif // MAINWINDOW_H

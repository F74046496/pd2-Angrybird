#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setBackgroundBrush(QPixmap(":/image/background.png").scaled(960, 540));
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Enable the event Filter
    qApp->installEventFilter(this);
    fly = false;
    skill = false;
    countdown = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,960,540);
    ui->graphicsView->setScene(scene);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)
    itemList.push_back(new Land(16.0f,1.5f,32.0f,3.0f,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));
    // Create Slingshot
    itemList.push_back(new Slingshot(7.0,6.25,0,0,QPixmap(":/image/slingshot.png").scaled(50,100),world,scene));

    /*QLabel *slingshot= new QLabel();
    slingshot->setGeometry(200,200,100,300);
    slingshot->setPixmap(QPixmap(":/image/slingshot.png"));
    slingshot->setAttribute(Qt::WA_TranslucentBackground);
    scene->addWidget(slingshot);*/

    setAndCreate();

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

void MainWindow::setAndCreate()
{
    // Create pig
    Pig *fatfat_1 = new Pig(18.0f, 14.0f, 1.0f,  &timer, QPixmap(":/image/PIGLETTE_BIG_01.png").scaled(60, 60), world, scene);
    Pig *fatfat_2 = new Pig(18.0f, 6.0f, 1.0f,  &timer, QPixmap(":/image/PIGLETTE_BIG_01.png").scaled(60, 60), world, scene);
    itemList.push_back(fatfat_1);
    itemList.push_back(fatfat_2);
    // Create wood
    Wood *stick_1 = new Wood(16.0f, 6.0f, 1.0f, 4.0f,  &timer, QPixmap(":/image/wood.png").scaled(30, 120), world, scene);
    Wood *stick_2 = new Wood(20.0f, 6.0f, 1.0f, 4.0f, &timer, QPixmap(":/image/wood.png").scaled(30, 120), world, scene);
    Wood *stick_3 = new Wood(18.0f, 10.0f, 5.0f, 1.0f, &timer, QPixmap(":/image/wood.png").scaled(150, 30), world, scene);
    itemList.push_back(stick_1);
    itemList.push_back(stick_2);
    itemList.push_back(stick_3);
    // Create bird (You can edit here)
    Bird *birdie_1 = new Bird(1.0f,10.0f,1.0f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0), world, scene);
    Bird *birdie_2 = new Bird(1.5f,1.75f,1.0f,&timer,QPixmap(":/image/BIRD_GREY.png").scaled(height()/9.0,height()/9.0), world, scene);
    Bird *birdie_3 = new Bird(3.0f,1.75f,1.0f,&timer,QPixmap(":/image/BIRD_GREEN.png").scaled(height()/9.0,height()/9.0), world, scene);
    Bird *birdie_4 = new Bird(4.5f,1.75f,1.0f,&timer,QPixmap(":/image/BIRD_YELLOW.png").scaled(height()/9.0,height()/9.0), world, scene);
    itemList.push_back(birdie_1);
    itemList.push_back(birdie_2);
    itemList.push_back(birdie_3);
    itemList.push_back(birdie_4);
    // Setting the Velocity
    birdie_1->setLinearVelocity(b2Vec2(5,5));
    //create buttons
    restartButton = new QPushButton;
    restartButton->setText("restart");
    restartButton->setGeometry(740, 10, 100, 50);
    restartButton->setStyleSheet("color:black; background-color: transparent; font: bold 30px;");
    connect(restartButton, SIGNAL(clicked(bool)), this, SLOT(restart()));
    scene->addWidget(restartButton);
    endButton = new QPushButton;
    endButton->setText("exit");
    endButton->setGeometry(850, 10, 100, 50);
    endButton->setStyleSheet("color:black; background-color: transparent; font: bold 30px;");
    connect(endButton, SIGNAL(clicked(bool)), this, SLOT(endgame()));
    scene->addWidget(endButton);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    QMouseEvent *mouse = static_cast<QMouseEvent*>(event);
    if(event->type() == QEvent::MouseButtonPress)
    {
        if (mouse->button() == Qt::LeftButton)
        {
            if(countdown==0)
            {
                //xpos=mouse->pos().x;
                //ypos=mouse->pos().y;

            }
        }
        if (mouse->button() == Qt::RightButton)
        {

        }
        //std::cout << "Press !" << std::endl ;
    }
    if(event->type() == QEvent::MouseMove)
    {
        if (mouse->button() == Qt::LeftButton)
        {

        }
        //std::cout << "Move !" << std::endl ;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if (mouse->button() == Qt::LeftButton)
        {

        }
       // std::cout << "Release !" << std::endl ;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::restart()
{
    disconnect(&timer,SIGNAL(timeout()),this,SLOT(tick()));

    itemList.clear();

    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,960,540);
    ui->graphicsView->setScene(scene);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)
    itemList.push_back(new Land(16.0f,1.5f,32.0f,3.0f,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));
    // Create Slingshot
    itemList.push_back(new Slingshot(7.0,6.25,0,0,QPixmap(":/image/slingshot.png").scaled(50,100),world,scene));

    setAndCreate();

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

void MainWindow::endgame()
{
    close();
}

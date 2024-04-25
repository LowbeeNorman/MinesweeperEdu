/// Assignment 9: MinesweeperEdu
/// CS3505
/// 4/24/24
/// Written by: Caleb Norman, Winston Ji, Jayden Ferrin, Abdulahad Asim

#include "freeplaywinscreen.h"
#include "ui_freeplaywinscreen.h"
#include <QPaintEvent>

FreeplayWinScreen::FreeplayWinScreen(QWidget *parent)
    : QWidget(parent)
    , world(b2Vec2(0.0f, 0.0f))
    , ui(new Ui::FreeplayWinScreen)
{
    ui->setupUi(this);

    connect(timer, &QTimer::timeout, this, &FreeplayWinScreen::updateWorld);
    connect(ui->menuButton, &QPushButton::clicked, this, &FreeplayWinScreen::menuButtonClicked);
    connect(ui->nextLevelButton, &QPushButton::clicked, this, &FreeplayWinScreen::nextButtonClicked);

    setUpBox2D();
    background.load(":/images/tv.png");
}

FreeplayWinScreen::~FreeplayWinScreen()
{
    delete ui;
}

void FreeplayWinScreen::menuButtonClicked()
{
    emit returnToMenu(0);
}

void FreeplayWinScreen::nextButtonClicked()
{
    // generate another level when they click that button
    emit nextFreeplayLevel(4);
    emit newBoard();
}

void FreeplayWinScreen::gameLost()
{
    ui->winLabel->setStyleSheet (QString (
        "border-image: url(:/images/youLose.png);"
    ));
}

void FreeplayWinScreen::gameWon()
{
    ui->winLabel->setStyleSheet (QString (
        "border-image: url(:/images/youWin.png);"
        ));
}

void FreeplayWinScreen::paintEvent(QPaintEvent *event)
{
    // Draws the background image to the start screen
    painter.begin(this);
    painter.drawPixmap(rect(), background);
    painter.end();

    event->accept();
}

void FreeplayWinScreen::setUpBox2D()
{
    // Define the dynamic body. We set its position and call the body factory (next line)
    b2BodyDef bodyDef;

    // Dynamic bodies move, static bodies do not
    bodyDef.type = b2_dynamicBody;

    // Links body to specifications we just made, through a method in world
    body = world.CreateBody(&bodyDef);

    // Bounce angle
    body->SetTransform(body->GetPosition(), 45.0f * b2_pi / 180.0f);
    body->SetAngularVelocity(0.0f);
    b2Vec2 initialVelocity(std::cos(45.0f * b2_pi / 180.0f), std::sin(45.0f * b2_pi / 180.0f));
    body->SetLinearVelocity(initialVelocity);

    timer->setInterval (1.0f / 60.0f * 1000);
    timer->start ();

}
// 1.0f / 60.0f      100

void FreeplayWinScreen::updateWorld()
{
    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0f / 60.0f, 6, 2);

    // New position of the label
    b2Vec2 velocity = body->GetLinearVelocity();
    int newX = ui->winLabel->x() + velocity.x * 3.0f;
    int newY = ui->winLabel->y() + velocity.y * 3.0f;

    int labelWidth = ui->winLabel->width();
    int labelHeight = ui->winLabel->height();

    // Check if the new position hits any of the window edges
    // left edge
    if (newX < 0.19 * width()) {
        body->SetLinearVelocity(b2Vec2(-velocity.x, velocity.y));
        newX = 0.19 * width();
    }
    //right edge
    if (newX > 0.63 * width()) {
        body->SetLinearVelocity(b2Vec2(-velocity.x, velocity.y));
        newX = 0.63 * width();
    }
    //top edge
    if (newY < 0.35 * height()) {
        body->SetLinearVelocity(b2Vec2(velocity.x, -velocity.y));
        newY = 0.35 * height();
    }
    //bottom edge
    if (newY > 0.67 * height()) {
        body->SetLinearVelocity(b2Vec2(velocity.x, -velocity.y));
        newY = 0.67 * height();
    }


    // Position is changed
    ui->winLabel->setGeometry(newX, newY, labelWidth, labelHeight);
}


/// Assignment 9: Educational App
/// CS3505
/// 4/24/24
/// Edited by: Caleb Norman, Abdul Asim
///
#include "winscreen.h"
#include "ui_winscreen.h"
#include <QPaintEvent>

WinScreen::WinScreen(QWidget *parent)
    : QWidget(parent)
    , world(b2Vec2(0.0f, 0.0f))
    , ui(new Ui::WinScreen)
{
    ui->setupUi(this);

    connect(timer, &QTimer::timeout, this, &WinScreen::updateWorld);
    connect(ui->levelSelectButton, &QPushButton::clicked, this, &WinScreen::levelSelectButtonClicked);
    connect(ui->nextLessonButton, &QPushButton::clicked, this, &WinScreen::nextLessonButtonClicked);

    setUpBox2D();
    background.load(":/images/tv.png");
}

WinScreen::~WinScreen()
{
    delete ui;
}

void WinScreen::levelSelectButtonClicked()
{
    emit backToLevelSelect(1);
}

void WinScreen::nextLessonButtonClicked()
{
    emit goToNextLesson();
}

void WinScreen::paintEvent(QPaintEvent *event)
{
    // Draws the background image to the start screen
    painter.begin(this);
    painter.drawPixmap(rect(), background);
    painter.end();

    event->accept();
}

void WinScreen::setUpBox2D()
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

void WinScreen::updateWorld()
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



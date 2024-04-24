/// Assignment 9: Educational App
/// CS3505
/// 4/19/24
/// Edited by: Caleb Norman
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
    // Define the ground body.
    b2BodyDef groundBodyDef;

    // Choose where the ground is
    groundBodyDef.position.Set(0.0f, -20.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // Width of the ground, in half widths (similar to radius vs diameter)
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory (next line)
    b2BodyDef bodyDef;

    // Dynamic bodies move, static bodies do not
    bodyDef.type = b2_dynamicBody;

    // Starting position of moving item
    bodyDef.position.Set(0.0f, 0.0f);

    // Angle of moving item
    bodyDef.angle = 0.45f;

    // Links body to specifications we just made, through a method in world
    body = world.CreateBody(&bodyDef);

    // Bounce angle
    body->SetTransform(body->GetPosition(), 45.0f * b2_pi / 180.0f);
    body->SetAngularVelocity(0.0f);
    b2Vec2 initialVelocity(std::cos(45.0f * b2_pi / 180.0f), std::sin(45.0f * b2_pi / 180.0f));
    body->SetLinearVelocity(initialVelocity);

    // Slowdown rate, want it at 0 because it should not slow down
    body->SetLinearDamping(0.0f);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 0.0f;

    // Override the default friction.
    fixtureDef.friction = 0.0f;

    // Bounciness
    fixtureDef.restitution = 0.0f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    // timer->start(1.0f / 60.0f);
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
    int newX = ui->winLabel->x() + velocity.x * 5.0f;
    int newY = ui->winLabel->y() + velocity.y * 5.0f;

    int labelWidth = ui->winLabel->width();
    int labelHeight = ui->winLabel->height();

    // Check if the new position hits any of the window edges
    if (newX <= 0 || newX >= width() - labelWidth) {
        // If the label hits the left or right hand side of the window, the horizontal velocity will be inverted
        body->SetLinearVelocity(b2Vec2(-velocity.x, velocity.y));
    }
    if (newY <= 0 || newY >= height() - labelHeight) {
        // If the label hits the top or bottom side of the window, the vertical velocity will be inverted
        body->SetLinearVelocity(b2Vec2(velocity.x, -velocity.y));
    }

    // Position is changed
    ui->winLabel->setGeometry(newX, newY, labelWidth, labelHeight);
}



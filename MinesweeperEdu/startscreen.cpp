/// Assignment 9: Educational App
/// CS3505
/// 4/16/24
/// Written by: Caleb Norman, Abdul Asim

#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(QWidget *parent)
    : QWidget(parent)
    , world(b2Vec2(0.0f, -10.0f))
    , ui(new Ui::StartScreen)
{
    ui->setupUi(this);

    connect(timer, &QTimer::timeout, this, &StartScreen::updateWorld);

    // Standard ui to cpp connection
    connect(ui->newLessonButton, &QPushButton::clicked, this, &StartScreen::newLessonButtonClicked);
    connect(ui->continueButton, &QPushButton::clicked, this, &StartScreen::continueButtonClicked);

    // Call to set up box2d
    setUpBox2D();
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::newLessonButtonClicked() {
    emit startingNewGame();
    emit sendNewLessonClicked(1);
}

void StartScreen::continueButtonClicked() {
    emit sendContinueClicked();
}

void StartScreen::setUpBox2D()
{
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(1.0f, 1.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 0.7f;

    // Override the default friction.
    fixtureDef.friction = 0.0f;

    fixtureDef.restitution = 100.0f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    timer->start(100);
}
// 1.0f / 60.0f

void StartScreen::updateWorld()
{
    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    world.Step(100, 6, 2);

    // Now print the position and angle of the body.
    b2Vec2 position = body->GetPosition();
    float32 angle = body->GetAngle();
    ui->startScreenLabel->setGeometry(
        ui->startScreenLabel->x(),
        position.y * 5,
        ui->startScreenLabel->width(),
        ui->startScreenLabel->height()
        );


    // printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

}

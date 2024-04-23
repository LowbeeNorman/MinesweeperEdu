/// Assignment 9: Educational App
/// CS3505
/// 4/19/24
/// Written by: Caleb Norman, Abdul Asim

#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(QWidget *parent)
    : QWidget(parent)
    , world(b2Vec2(0.0f, -13.0f))
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

    // Angle of moving item (0 because I only care about 1D motion)
    bodyDef.angle = 0;

    // Links body to specifications we just made, through a method in world
    body = world.CreateBody(&bodyDef);

    // Slowdown rate, want it at 0 because it should not slow down
    body->SetLinearDamping(0.0f);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.0f;

    // Bounciness
    fixtureDef.restitution = 1.0f;



    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    // timer->start(1.0f / 60.0f);
    timer->setInterval (1.0f / 60.0f * 1000);
    timer->start ();
}
// 1.0f / 60.0f      100

void StartScreen::updateWorld()
{
    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0f / 60.0f, 6, 2);

    // Now print the position and angle of the body.
    b2Vec2 position = body->GetPosition();
    // float32 angle = body->GetAngle();
    ui->startScreenLabel->setGeometry(
        ui->startScreenLabel->x(),
        -position.y * 15.0f,
        ui->startScreenLabel->width(),
        ui->startScreenLabel->height()
        );


    // printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
}

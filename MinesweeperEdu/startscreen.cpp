/// Assignment 9: Educational App
/// CS3505
/// 4/16/24
/// Written by: Caleb Norman, Abdul Asim

#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartScreen)
{
    ui->setupUi(this);

    // Standard ui to cpp connection
    connect(ui->newLessonButton, &QPushButton::clicked, this, &StartScreen::newLessonButtonClicked);
    connect(ui->continueButton, &QPushButton::clicked, this, &StartScreen::continueButtonClicked);
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

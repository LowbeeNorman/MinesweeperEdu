/// Assignment 9: Educational App
/// CS3505
/// Written by: Caleb Norman

#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartScreen)
{
    ui->setupUi(this);
    connect(ui->newLessonButton, &QPushButton::clicked, this, &StartScreen::newLessonButtonClicked);
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::newLessonButtonClicked() {
    emit sendNewLessonClicked(1);
}

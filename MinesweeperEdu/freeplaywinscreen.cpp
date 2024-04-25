#include "freeplaywinscreen.h"
#include "ui_freeplaywinscreen.h"

FreeplayWinScreen::FreeplayWinScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FreeplayWinScreen)
{
    ui->setupUi(this);


    connect(ui->menuButton, &QPushButton::clicked, this, &FreeplayWinScreen::menuButtonClicked);
    connect(ui->nextLevelButton, &QPushButton::clicked, this, &FreeplayWinScreen::nextButtonClicked);
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
}

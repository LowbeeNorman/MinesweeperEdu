#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartScreen)
{
    ui->setupUi(this);
}

StartScreen::~StartScreen()
{
    delete ui;
}

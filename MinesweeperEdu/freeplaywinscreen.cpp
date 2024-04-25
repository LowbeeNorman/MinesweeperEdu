#include "freeplaywinscreen.h"
#include "ui_freeplaywinscreen.h"

FreeplayWinScreen::FreeplayWinScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FreeplayWinScreen)
{
    ui->setupUi(this);
}

FreeplayWinScreen::~FreeplayWinScreen()
{
    delete ui;
}

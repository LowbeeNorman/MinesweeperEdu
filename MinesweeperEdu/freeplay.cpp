/// Assignment 9: MinesweeperEdu
/// CS3505
/// 4/24/24
/// Written by: Caleb Norman, Winston Ji

#include "freeplay.h"
#include "ui_freeplay.h"

Freeplay::Freeplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Freeplay)
{
    ui->setupUi(this);

    connect(ui->menuButton, &QPushButton::clicked, this, &Freeplay::menuButtonClicked);
}

Freeplay::~Freeplay()
{
    delete ui;
}

MinesweeperView *Freeplay::getBoard ()
{
    return ui->board;
}

void Freeplay::display (int index)
{
    Q_UNUSED (index);
    ui->board->display ();
}

void Freeplay::menuButtonClicked()
{
    emit returnToMenu(0);
}

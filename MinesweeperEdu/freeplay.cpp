#include "freeplay.h"
#include "ui_freeplay.h"

Freeplay::Freeplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Freeplay)
{
    ui->setupUi(this);
}

Freeplay::~Freeplay()
{
    delete ui;
}

MinesweeperView *Freeplay::getBoard ()
{
    return ui->board;
}

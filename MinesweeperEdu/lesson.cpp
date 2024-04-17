/// Assignment 9: Educational App
/// CS3505
/// Written by: Caleb Norman

#include "lesson.h"
#include "ui_lesson.h"

Lesson::Lesson(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lesson)
{
    ui->setupUi(this);

    // testing stuff
}

Lesson::~Lesson()
{
    delete ui;
}

void Lesson::makeConnections (Minefield &mines)
{
    ui->board->setSize (mines.getSize ());
    connect (&mines, &Minefield::updateBoard, ui->board, &MinesweeperView::receiveBoard);
    mines.requestBoard ();
    connect (ui->board, &MinesweeperView::clear, &mines, &Minefield::clear);
    connect (ui->board, &MinesweeperView::flag,  &mines, &Minefield::flag);
    connect (ui->board, &MinesweeperView::chord, &mines, &Minefield::chord);
    connect (&mines, &Minefield::flagPlaced, ui->board, &MinesweeperView::flagPlaced);
    connect (&mines, &Minefield::flagRemoved, ui->board, &MinesweeperView::flagRemoved);
    connect (ui->board, &MinesweeperView::requestChord, &mines, &Minefield::getSurroundings);
    connect (&mines, &Minefield::sendChord, ui->board, &MinesweeperView::displayHighlight);
    connect (ui->board, &MinesweeperView::requestIfCovered, &mines, &Minefield::getIfCovered);
    connect (&mines, &Minefield::sendCovered, ui->board, &MinesweeperView::receiveIfCovered);
}

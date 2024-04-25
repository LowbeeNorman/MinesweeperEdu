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

    connect(ui->backButton, &QPushButton::clicked
            , this, &Lesson::backButtonClicked);
    connect(ui->nextButton, &QPushButton::clicked
            , this, &Lesson::nextButtonClicked);
    connect(ui->previousButton, &QPushButton::clicked
            , this, &Lesson::previousButtonClicked);

    ui->flagCounter->display(999);
}

Lesson::~Lesson()
{
    delete ui;
}

void Lesson::makeConnections (Minefield &mines)
{
    connect (&mines, &Minefield::updateBoard
            , ui->board, &MinesweeperView::receiveBoard);
    // mines.requestBoard ();
    connect (ui->board, &MinesweeperView::requestBoard
            , &mines, &Minefield::requestBoard);
    // ui->board->setBoardSize (mines.getSize ());

    connect (ui->board, &MinesweeperView::clear, &mines, &Minefield::clear);
    connect (ui->board, &MinesweeperView::flag,  &mines, &Minefield::flag);
    connect (ui->board, &MinesweeperView::chord, &mines, &Minefield::chord);
    connect (&mines, &Minefield::flagPlaced
            , ui->board, &MinesweeperView::flagPlaced);
    connect (&mines, &Minefield::flagRemoved
            , ui->board, &MinesweeperView::flagRemoved);
    connect (&mines, &Minefield::lessonHighlightPlaced, ui->board,
            &MinesweeperView::lessonHighlightPlaced);
    connect (&mines, &Minefield::lessonHighlightRemoved, ui->board,
            &MinesweeperView::lessonHighlightRemoved);
    connect (ui->board, &MinesweeperView::requestChord
            , &mines, &Minefield::getSurroundings);
    connect (&mines, &Minefield::sendChord
            , ui->board, &MinesweeperView::displayHighlight);
    connect (ui->board, &MinesweeperView::requestIfCovered
            , &mines, &Minefield::getIfCovered);
    connect (&mines, &Minefield::sendCovered
            , ui->board, &MinesweeperView::receiveIfCovered);
    connect (&mines, &Minefield::dead
            , ui->board, &MinesweeperView::dead);
    connect (&mines, &Minefield::won
            , ui->board, &MinesweeperView::won);
    // for when user is in Quiz and left clicks

    connect(&mines, &Minefield::numFlagsChanged
            , this, &Lesson::setFlagsRemaining);

    connect (this, &Lesson::updateCurrentProgress, ui->progressDisplay, &QProgressBar::setValue);
    connect (this, &Lesson::updateMaxProgress, ui->progressDisplay, &QProgressBar::setMaximum);

}

void Lesson::backButtonClicked()
{
    emit sendBackClicked(1);
    // set with some arbitrary max that we will never hit, makes checking the logic easier
    emit receiveProgressUpdate(0, 100);
}

void Lesson::nextButtonClicked()
{
    emit getNextMessage();
    emit requestProgressUpdate();
}

void Lesson::previousButtonClicked()
{
    emit getPreviousMessage();
}

void Lesson::receiveLessonInfo(const QString& topic, const QString& message, Minefield& minefield)
{
    ui->topicText->setText(topic);
    ui->instructions->setText(message);
    ui->feedback->clear();
    // makeConnections(minefield);
}

void Lesson::receiveNextMessage(const QString& message)
{
    ui->instructions->setText(message);
}

MinesweeperView *Lesson::getBoard ()
{
    return ui->board;
}

void Lesson::receiveFeedback (QString message)
{
    ui->feedback->setText(message);

}

void Lesson::receiveProgressUpdate (int current, int max)
{
    // Will not work for lessons with one part to them
    if(max != ui->progressDisplay->maximum() || current > ui->progressDisplay->value())
    {
        emit updateCurrentProgress(current);
        emit updateMaxProgress(max);
    }
}
void Lesson::setFlagsRemaining(int numFlags)
{
    ui->flagCounter->display(numFlags);
    qDebug() << numFlags;
}

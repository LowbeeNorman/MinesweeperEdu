/// Assignment 9: Educational App
/// CS3505
/// 4/24/2024
/// Written by: Caleb Norman

#include "lesson.h"
#include "ui_lesson.h"

Lesson::Lesson(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lesson)
{
    ui->setupUi(this);

    // Connections for buttons
    connect(ui->backButton, &QPushButton::clicked
            , this, &Lesson::backButtonClicked);
    connect(ui->nextButton, &QPushButton::clicked
            , this, &Lesson::nextButtonClicked);
    connect(ui->previousButton, &QPushButton::clicked
            , this, &Lesson::previousButtonClicked);

    // Connections for updating the progress bar
    connect (this, &Lesson::updateCurrentProgress
            , ui->progressDisplay, &QProgressBar::setValue);
    connect (this, &Lesson::updateMaxProgress, ui->progressDisplay
            , &QProgressBar::setMaximum);

    ui->flagCounter->display(999);
}

Lesson::~Lesson()
{
    delete ui;
}

void Lesson::makeConnections (Minefield &mines)
{
    // Connections for the minesweeper board
    connect(&mines, &Minefield::numFlagsChanged
            , this, &Lesson::setFlagsRemaining);
}

void Lesson::backButtonClicked()
{
    emit sendBackClicked(1);
    // set with some arbitrary max that we will never hit, makes checking the logic easier
    receiveProgressUpdate(0, 100);
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
    maxPage = 0;
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
    if(current < maxPage) {
        return;
    }
    emit updateCurrentProgress(current);
    emit updateMaxProgress(max);
    maxPage = current;
}

void Lesson::setFlagsRemaining(int numFlags)
{
    ui->flagCounter->display(numFlags);
}

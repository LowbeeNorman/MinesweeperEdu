/// Assignment 9: Educational App
/// CS3505
/// 4/12/24
/// Written by: Caleb Norman, Abdul Asim, and Kyle Stewart

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Model &model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // This connection is sent from the startPage widget that resides within
    // the mainwindow, and is received by the main window. This will be a
    // common pattern within our program with various widgets within the
    // main window
    connect(ui->startPage, &StartScreen::sendNewLessonClicked
            , this, &MainWindow::updateScreenIndex);
    connect(ui->startPage, &StartScreen::sendNewLessonClicked
            , this, &MainWindow::loadNew);

    connect(ui->startPage, &StartScreen::sendContinueClicked
            , this, &MainWindow::loadPrevious);
    connect(ui->levelSelectPage, &LevelSelect::sendMenuClicked
            , this, &MainWindow::updateScreenIndex);
    connect(ui->lessonPage, &Lesson::sendBackClicked
            , this, &MainWindow::updateScreenIndex);
    connect(ui->lessonPage, &Lesson::getNextMessage
            , &model, &Model::nextMessage);
    connect(ui->lessonPage, &Lesson::getPreviousMessage
            , &model, &Model::previousMessage);
    connect(ui->startPage , &StartScreen::startingNewGame
            , ui->levelSelectPage, &LevelSelect::receiveStartingNewGame);
    connect(ui->winScreenPage, &WinScreen::backToLevelSelect
            , this, &MainWindow::updateScreenIndex);
    connect(ui->winScreenPage, &WinScreen::goToNextLesson
            , this, &MainWindow::nextLessonShortcut);

    connect(ui->levelSelectPage, &LevelSelect::sendCurrentLevel
            , this, &MainWindow::receiveLevelIndex);
    // retrieves Lesson number
    connect(this, &MainWindow::getLesson, &model, &Model::setLesson);
    // sends Lesson info back
    connect(&model, &Model::sendLessonInfo
            , ui->lessonPage, &Lesson::receiveLessonInfo);
    // get next Message
    connect(&model, &Model::sendCurrentMessage
            , ui->lessonPage, &Lesson::receiveNextMessage);
    // get next Instruction
    connect(&model, &Model::sendCurrentInstruction
            , ui->lessonPage, &Lesson::receiveNextMessage);
    // get error message
    connect(&model, &Model::sendErrorMessage
            , ui->lessonPage, &Lesson::receiveFeedback);

    connect(ui->lessonPage->getBoard(), &MinesweeperView::clearAttempted
            , &model, &Model::receiveClearAttempted);
    connect(&model, &Model::updateCellClear
            , ui->lessonPage->getBoard(), &MinesweeperView::clearCell);

    connect(ui->lessonPage->getBoard(), &MinesweeperView::flagAttempted
            , &model, &Model::receiveFlagAttempted);
    connect(&model, &Model::updateCellFlag
            , ui->lessonPage->getBoard(), &MinesweeperView::flagCell);

    connect(this, &MainWindow::getNextLesson, &model, &Model::setLessonToNext);

    connect(&model, &Model::quizCompleted, this, &MainWindow::showWinScreen);

    connect(&model, &Model::quizTime
            , ui->lessonPage->getBoard(), &MinesweeperView::enableBoard);
    connect(&model, &Model::lessonTime
            , ui->lessonPage->getBoard(), &MinesweeperView::disableBoard);

    connect(&model, &Model::sendCurrentLevel
            , ui->levelSelectPage, &LevelSelect::updateCurrentLevel);

    // check if the level selected is valid
    connect(this, &MainWindow::checkAccess, &model, &Model::checkLessonNumber);
    connect(&model, &Model::tooBigLessonNumber
            , this, &MainWindow::invalidLessonSelected);
    connect(&model, &Model::validLessonNumber
            , this, &MainWindow::validLessonSelected);

    // make the connections with the minefield
    ui->lessonPage->makeConnections (model.getMinefield ());

    // connections for the progress bar updating during lessons
    connect(ui->lessonPage, &Lesson::requestProgressUpdate
            , &model, &Model::receiveProgressRequest);
    connect(&model, &Model::sendProgressUpdate
            , ui->lessonPage, &Lesson::receiveProgressUpdate);

    // load user progress
    connect(this, &MainWindow::loadUserProgress
            , &model, &Model::loadUserProgressFile);
    // reset progress
    connect(this, &MainWindow::resetUserProgress
            , &model, &Model::resetUserProgressInFile);
    // update progress
    connect(this, &MainWindow::passedLevel
            , &model, &Model::increaseMaxLessonValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateScreenIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);

    // Reset progress if they go off of the level
    // set with some arbitrary max that we will never hit, makes checking
    // the logic easier
    ui->lessonPage->receiveProgressUpdate(0, 100);
}

void MainWindow::receiveLevelIndex(int levelIndex){
    qDebug() << "Need to load level " << levelIndex + 1 << "(or index" << levelIndex << ")";
    emit checkAccess(levelIndex);
}

void MainWindow::validLessonSelected (int lessonNumber)
{
    emit getLesson(lessonNumber);
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::loadPrevious()
{
    // Do something from view -> model for loading
    qDebug() << "Need to load a game to continue";
    emit loadUserProgress ();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::nextLessonShortcut()
{
    // We will need to load the next lesson info in here somehow

    qDebug() << "Need to load the next level";

    ui->stackedWidget->setCurrentIndex(2);

    emit getNextLesson();

    // Reset progress for next level
    // set with some arbitrary max that we will never hit, makes checking
    // the logic easier
    ui->lessonPage->receiveProgressUpdate(0, 100);
}

void MainWindow::showWinScreen ()
{
    emit passedLevel();
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::invalidLessonSelected ()
{
    qDebug() << "reached";
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::loadNew (int index)
{
    emit resetUserProgress();

    ui->stackedWidget->setCurrentIndex(index);

    // Reset progress if they go off of the level
    // set with some arbitrary max that we will never hit, makes checking
    // the logic easier
    ui->lessonPage->receiveProgressUpdate(0, 100);
}



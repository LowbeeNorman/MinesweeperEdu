/// Assignment 9: Educational App
/// CS3505
/// 4/24/24
/// Written by: Caleb Norman, Abdul Asim, and Kyle Stewart

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Model &model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Start page signal connections
    connect(ui->startPage, &StartScreen::sendNewLessonClicked
            , this, &MainWindow::updateScreenIndex);
    connect(ui->startPage, &StartScreen::sendNewLessonClicked
            , this, &MainWindow::loadNew);
    connect (ui->startPage, &StartScreen::sendNewLessonClicked
            , &model, &Model::setInQuiz);
    connect(ui->startPage, &StartScreen::sendFreeplayClicked
            , this, &MainWindow::updateScreenIndex);
    connect (ui->startPage, &StartScreen::sendFreeplayClicked
            , ui->freeplayPage, &Freeplay::display);
    connect (ui->startPage, &StartScreen::sendFreeplayClicked
            , &model, &Model::setFreePlay);
    connect (ui->startPage, &StartScreen::sendFreeplayClicked
            , &model.getFreeplayField (), &Minefield::resetField);
    connect(ui->startPage, &StartScreen::sendContinueClicked
            , this, &MainWindow::loadPrevious);
    connect (ui->startPage, &StartScreen::sendContinueClicked
            , &model, &Model::setInQuiz);
    connect(ui->startPage , &StartScreen::startingNewGame
            , ui->levelSelectPage, &LevelSelect::receiveStartingNewGame);

    // level/lesson select page connections
    connect(ui->levelSelectPage, &LevelSelect::sendMenuClicked
            , this, &MainWindow::updateScreenIndex);
    connect(ui->levelSelectPage, &LevelSelect::sendCurrentLevel
            , this, &MainWindow::receiveLevelIndex);


    // lesson page connections
    connect(ui->lessonPage, &Lesson::sendBackClicked
            , this, &MainWindow::updateScreenIndex);
    connect(ui->lessonPage, &Lesson::getNextMessage
            , &model, &Model::nextMessage);
    connect(ui->lessonPage, &Lesson::getPreviousMessage
            , &model, &Model::previousMessage);
    connect(ui->lessonPage->getBoard(), &MinesweeperView::clearAttempted
            , &model, &Model::receiveClearAttempted);
    connect (ui->freeplayPage->getBoard (), &MinesweeperView::clearAttempted
            , &model, &Model::receiveClearAttempted);
    connect(ui->lessonPage->getBoard(), &MinesweeperView::flagAttempted
            , &model, &Model::receiveFlagAttempted);
    connect(ui->freeplayPage->getBoard(), &MinesweeperView::flagAttempted
            , &model, &Model::receiveFlagAttempted);
    connect(ui->lessonPage, &Lesson::requestProgressUpdate
            , &model, &Model::receiveProgressRequest);

    // win screen page connections
    connect(ui->winScreenPage, &WinScreen::backToLevelSelect
            , this, &MainWindow::updateScreenIndex);
    connect(ui->winScreenPage, &WinScreen::goToNextLesson
            , this, &MainWindow::nextLessonShortcut);
    connect(ui->levelSelectPage, &LevelSelect::disableNextLesson
            , ui->winScreenPage, &WinScreen::disableNextButton);
    connect(ui->levelSelectPage, &LevelSelect::enableNextLesson
            , ui->winScreenPage, &WinScreen::enableNextButton);

    // main window connections
    connect(this, &MainWindow::getLesson, &model, &Model::setLesson);
    connect(this, &MainWindow::getNextLesson, &model, &Model::setLessonToNext);
    connect(this, &MainWindow::checkAccess, &model, &Model::checkLessonNumber);
    connect(this, &MainWindow::loadUserProgress, &model, &Model::loadUserProgressFile);
    connect(this, &MainWindow::resetUserProgress, &model, &Model::resetUserProgressInFile);
    connect(this, &MainWindow::passedLevel, &model, &Model::increaseMaxLessonValue);

    // model connections
    connect(&model, &Model::sendLessonInfo
            , ui->lessonPage, &Lesson::receiveLessonInfo);
    connect(&model, &Model::sendCurrentMessage
            , ui->lessonPage, &Lesson::receiveNextMessage);
    connect(&model, &Model::sendCurrentInstruction
            , ui->lessonPage, &Lesson::receiveNextMessage);
    connect(&model, &Model::sendErrorMessage
            , ui->lessonPage, &Lesson::receiveFeedback);
    connect(&model, &Model::updateCellClear
            , ui->lessonPage->getBoard(), &MinesweeperView::clearCell);
    connect(&model, &Model::updateCellClear
            , ui->freeplayPage->getBoard(), &MinesweeperView::clearCell);
    connect(&model, &Model::updateCellFlag
            , ui->lessonPage->getBoard(), &MinesweeperView::flagCell);
    connect(&model, &Model::updateCellFlag
            , ui->freeplayPage->getBoard(), &MinesweeperView::flagCell);
    connect(&model, &Model::quizCompleted, this, &MainWindow::showWinScreen);
    connect(&model, &Model::quizTime
            , ui->lessonPage->getBoard(), &MinesweeperView::enableBoard);
    connect(&model, &Model::lessonTime
            , ui->lessonPage->getBoard(), &MinesweeperView::disableBoard);
    connect(&model, &Model::sendCurrentLevel
            , ui->levelSelectPage, &LevelSelect::updateCurrentLevel);
    connect(&model, &Model::sendProgressUpdate
            , ui->lessonPage, &Lesson::receiveProgressUpdate);
    connect(&model, &Model::tooBigLessonNumber
            , this, &MainWindow::invalidLessonSelected);
    connect(&model, &Model::validLessonNumber
            , this, &MainWindow::validLessonSelected);
    connect(&model, &Model::sendMaxLesson
            , ui->levelSelectPage, &LevelSelect::receiveMaxLesson);

    // make the connections with the minefield
    ui->lessonPage->makeConnections (model.getMinefield ());
    ui->lessonPage->getBoard()->makeConnections (model.getMinefield());
    ui->freeplayPage->getBoard()->makeConnections (model.getFreeplayField());


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
    connect(ui->freeplayPage, &Freeplay::returnToMenu, this, &MainWindow::updateScreenIndex);
    connect(ui->freeplayWinScreenPage, &FreeplayWinScreen::returnToMenu, this, &MainWindow::updateScreenIndex);
    connect(ui->freeplayWinScreenPage, &FreeplayWinScreen::nextFreeplayLevel, this, &MainWindow::updateScreenIndex);

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
    emit checkAccess(levelIndex);
}

void MainWindow::validLessonSelected (int lessonNumber)
{
    emit getLesson(lessonNumber);
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::loadPrevious()
{
    emit loadUserProgress ();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::nextLessonShortcut()
{
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



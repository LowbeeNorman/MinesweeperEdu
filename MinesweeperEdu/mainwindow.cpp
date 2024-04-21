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

    connect(ui->startPage, &StartScreen::sendContinueClicked, this, &MainWindow::loadPrevious);
    connect(ui->levelSelectPage, &LevelSelect::sendMenuClicked, this, &MainWindow::updateScreenIndex);
    connect(ui->lessonPage, &Lesson::sendBackClicked, this, &MainWindow::updateScreenIndex);
    connect(ui->lessonPage, &Lesson::getNextMessage, &model, &Model::nextMessage);
    connect(ui->startPage , &StartScreen::startingNewGame, ui->levelSelectPage, &LevelSelect::receiveStartingNewGame);
    connect(ui->winScreenPage, &WinScreen::backToLevelSelect, this, &MainWindow::updateScreenIndex);
    connect(ui->winScreenPage, &WinScreen::goToNextLesson, this, &MainWindow::nextLessonShortcut);

    connect(ui->levelSelectPage, &LevelSelect::sendCurrentLevel, this, &MainWindow::receiveLevelIndex);
    // retrieves Lesson number
    connect(this, &MainWindow::getLesson, &model, &Model::setLesson);
    // sends Lesson info back
    connect(&model, &Model::sendLessonInfo, ui->lessonPage, &Lesson::receiveLessonInfo);
    // get next Message
    connect(&model, &Model::sendCurrentMessage, ui->lessonPage, &Lesson::receiveNextMessage);

    connect(ui->lessonPage->getBoard(), &MinesweeperView::clearAttempted, &model, &Model::receiveClearAttempted);
    connect(&model, &Model::updateCellClear, ui->lessonPage->getBoard(), &MinesweeperView::clearCell);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeConnections (Minefield &mines)
{
    ui->lessonPage->makeConnections (mines);
}

void MainWindow::updateScreenIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void MainWindow::receiveLevelIndex(int levelIndex){
    qDebug() << "Need to load level " << levelIndex + 1 << "(or index" << levelIndex << ")";

    emit getLesson(levelIndex);

    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::loadPrevious()
{
    // Do something from view -> model for loading
    qDebug() << "Need to load a game to continue";
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::nextLessonShortcut()
{
    // We will need to load the next lesson info in here somehow

    qDebug() << "Need to load the next level";

    ui->stackedWidget->setCurrentIndex(2);
}



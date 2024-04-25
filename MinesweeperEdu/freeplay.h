/// Assignment 9: MinesweeperEdu
/// CS3505
/// 4/24/24
/// Written by: Caleb Norman, Winston Ji, Jayden Ferrin, Abdulahad Asim

#ifndef FREEPLAY_H
#define FREEPLAY_H

#include <QWidget>
#include "minesweeperview.h"

namespace Ui {
class Freeplay;
}

///
/// \brief The Freeplay class is responsible for the freeplay view.
///
class Freeplay : public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief Freeplay constructor
    /// \param parent Mainwindow
    ///
    explicit Freeplay(QWidget *parent = nullptr);

    ///
    ///  \brief Destructor
    ///
    ~Freeplay();

    ///
    /// \brief getBoard getter for the MinesweeperView in Freeplay
    /// \return MinesweeperView
    ///
    MinesweeperView* getBoard();

    ///
    /// \brief display
    ///
    void display ();

private:
    ///
    /// \brief ui for Freeplay
    ///
    Ui::Freeplay *ui;


signals:
    ///
    /// \brief Returns to the menu
    /// \param Index of the menu
    ///
    void returnToMenu(int i);

    ///
    /// \brief goToWinScreen emitted when the game ends
    /// \param index of the win screen in the stacked widget
    ///
    void goToWinScreen(int index);

public slots:

    ///
    /// \brief Listens for the menu button to be clicked
    ///
    void menuButtonClicked();

    ///
    /// \brief gameOver listens for the game to be over
    ///
    void gameOver();

    ///
    /// \brief setFlagsRemaining listens for the number of flags to be updated
    /// \param numFlags the current number of flags left
    ///
    void setFlagsRemaining(int numFlags);

};

#endif // FREEPLAY_H

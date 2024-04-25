/// Assignment 9: MinesweeperEdu
/// CS3505
/// 4/24/24
/// Written by: Caleb Norman, Winston Ji

#ifndef FREEPLAY_H
#define FREEPLAY_H

#include <QWidget>
#include "minefield.h"
#include "minesweeperview.h"

namespace Ui {
class Freeplay;
}

class Freeplay : public QWidget
{
    Q_OBJECT

public:
    explicit Freeplay(QWidget *parent = nullptr);
    ~Freeplay();
    MinesweeperView* getBoard();

    void display (int index);

private:
    Ui::Freeplay *ui;


signals:
    ///
    /// \brief Returns to the menu
    /// \param Index of the menu
    ///
    void returnToMenu(int i);

public slots:

    ///
    /// \brief Listens for the menu button to be clicked
    ///
    void menuButtonClicked();

};

#endif // FREEPLAY_H

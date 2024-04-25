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

private:
    Ui::Freeplay *ui;

};

#endif // FREEPLAY_H

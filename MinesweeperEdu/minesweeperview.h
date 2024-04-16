#ifndef MINESWEEPERVIEW_H
#define MINESWEEPERVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include "minefield.h"

#define TILE_SIZE 128

class MinesweeperView : public QGraphicsView
{
    Q_OBJECT
    QSize size;
    QPixmap *pixmap;
    QGraphicsScene *mainScene;
    QGraphicsPixmapItem *pixmapItem;

    int pointToIndex (int x, int y);

    QPixmap *flag, *cover;
    QPixmap *numbers[10];
public:
    MinesweeperView(QWidget *parent = nullptr);
    void setSize(QSize size);

public slots:
    void receiveBoard (int *board, Tile *covers);
};

#endif // MINESWEEPERVIEW_H

#ifndef MINESWEEPERVIEW_H
#define MINESWEEPERVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QMouseEvent>
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
    int numFlags;

    QPixmap *flagImage, *coverImage;
    QPixmap *numbers[10];

    Qt::MouseButton mouse;

    QPoint translateToMinesweeper (QPointF point);
    QPoint translateFromMinesweeper (QPoint point);
public:
    MinesweeperView (QWidget *parent = nullptr);
    ~MinesweeperView ();
    void setSize(QSize size);

    // mouse stuff
    void mousePressEvent (QMouseEvent *event) override;
    void mouseMoveEvent (QMouseEvent *event) override;
    void mouseReleaseEvent (QMouseEvent *event) override;

signals:
    void clear (QPoint origin);
    void flag  (QPoint origin);
    void chord (QPoint origin);
public slots:
    void receiveBoard (const int *board, const Tile *covers);
    void flagPlaced (QPoint point, int numFlags);
    void flagRemoved (QPoint point, int numFlags);
};

#endif // MINESWEEPERVIEW_H

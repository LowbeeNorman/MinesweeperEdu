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

    QList<QPoint> prevChord;

    Qt::MouseButton mouse;

    QPoint translateToMinesweeper (QPointF point);
    QPoint translateFromMinesweeper (QPoint point);

    bool enabled;
public:
    MinesweeperView (QWidget *parent = nullptr);
    ~MinesweeperView ();
    void setBoardSize(QSize size);

    // mouse stuff
    void mousePressEvent (QMouseEvent *event) override;
    void mouseMoveEvent (QMouseEvent *event) override;
    void mouseReleaseEvent (QMouseEvent *event) override;
    void resizeEvent (QResizeEvent* event) override;

signals:
    void clear (QPoint origin);
    void flag  (QPoint origin);
    void chord (QPoint origin);

    void requestBoard ();

    void requestChord (QPoint origin);
    void requestIfCovered (QPoint origin);

    ///
    /// \brief tells the model that a clear was attempted at the given origin
    /// \param origin cell that was clicked
    ///
    void clearAttempted (QPoint origin);
    ///
    /// \brief tells the model that a flag was attempted at the given origin
    /// \param origin cell that was clicked
    ///
    void flagAttempted (QPoint origin);
public slots:
    void receiveBoard (const int *board, const Tile *covers);
    void flagPlaced (QPoint point, int numFlags);
    void flagRemoved (QPoint point, int numFlags);
    void displayHighlight (QList<QPoint> coveredTiles);
    void receiveIfCovered (QPoint origin, bool covered);

    void dead (QPoint origin, QList<QPoint> mines);
    void won (QList<QPoint> mines);
    ///
    /// \brief clears the cell at the given point
    /// \param origin point
    ///
    void clearCell (QPoint origin);
    ///
    /// \brief flags the cell at the given point
    /// \param origin point
    ///
    void flagCell (QPoint origin);
    ///
    /// \brief Enables the board so that the user can interact with it
    ///
    void enableBoard ();
    ///
    /// \brief Disables the board so that the user can interact with it
    ///
    void disableBoard ();
};

#endif // MINESWEEPERVIEW_H

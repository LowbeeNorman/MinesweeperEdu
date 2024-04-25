/// Assignment 9: MinesweeperEdu
/// CS3505
/// 4/24/2024
/// Written by: Jayden Ferrin, Winston Ji

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

private:
    QSize size;
    QPixmap *pixmap;
    QGraphicsScene *mainScene;
    QGraphicsPixmapItem *pixmapItem;

    int pointToIndex (int x, int y);
    int numFlags;

    QPixmap *flagImage, *coverImage;
    QPixmap *redHighlight, *orangeHighlight, *yellowHighlight, *pinkHighlight, *blueHighlight, *purpleHighlight, *brownHighlight, *blackHighlight;
    QPixmap *numbers[10];

    QList<QPoint> prevChord;

    Qt::MouseButton mouse;

    // used to stop the user from interacting with the board
    bool enabled;

    ///
    /// \brief translateToMinesweeper translates a point in view space to
    /// be able to be used by the minesweeper game
    /// \param point the point in view space
    /// \return the point translated to minesweeper space
    ///
    QPoint translateToMinesweeper (QPointF point);
    ///
    /// \brief translateFromMinesweeper translates a point from minesweeper
    /// to view space
    /// \param point the coordinates in the minesweeper grid
    /// \return the point in view space
    ///
    QPoint translateFromMinesweeper (QPoint point);

    ///
    /// \brief internalResize performs the actual transformations on the
    /// view to make the board the right size
    ///
    void internalResize ();
public:
    ///
    /// \brief MinesweeperView default constructor
    /// \param parent parent widget to pass to the base class
    ///
    MinesweeperView (QWidget *parent = nullptr);
    ~MinesweeperView ();
    void setBoardSize(QSize size);

    // mouse stuff
    void mousePressEvent (QMouseEvent *event) override;
    void mouseMoveEvent (QMouseEvent *event) override;
    void mouseReleaseEvent (QMouseEvent *event) override;
    void resizeEvent (QResizeEvent* event) override;
    void makeConnections (Minefield &mines);

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
    void receiveBoard (const QSize &boardSize, const int *board, const Tile *covers);
    void flagPlaced (QPoint point, int numFlags);
    void flagRemoved (QPoint point, int numFlags);
    void lessonHighlightPlaced (QPoint point, int color);
    void lessonHighlightRemoved (QPoint point);
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

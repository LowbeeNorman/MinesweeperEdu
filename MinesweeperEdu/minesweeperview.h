/// Assignment 9: MinesweeperEdu
/// CS3505
/// 4/24/2024
/// Written by: Jayden Ferrin, Winston Ji, Noah Sikorski

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

    ///
    /// \brief pointToIndex converts a 2 dimensional point to an index in backing array
    /// \param x coordinate
    /// \param y coordinate
    /// \return int index in the backing array
    ///
    int pointToIndex (int x, int y);
    int numFlags;

    /// images for the tiles
    QPixmap flagImage, coverImage;
    QPixmap redHighlight, orangeHighlight, yellowHighlight, pinkHighlight;
    QPixmap blueHighlight, purpleHighlight, brownHighlight, blackHighlight;
    QPixmap numbers[10];

    ///
    /// \brief prevChord the tiles in the chord
    ///
    QList<QPoint> prevChord;

    ///
    /// \brief mouse events
    ///
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

    ///
    /// \brief display the board
    ///
    void display ();

    ///
    /// \brief setBoardSize of the current board
    /// \param size desired dimensions
    ///
    void setBoardSize (QSize size);

    // mouse stuff
    void mousePressEvent (QMouseEvent *event) override;
    void mouseMoveEvent (QMouseEvent *event) override;
    void mouseReleaseEvent (QMouseEvent *event) override;
    void resizeEvent (QResizeEvent* event) override;
    void makeConnections (Minefield &mines);

signals:
    ///
    /// \brief clear emitted when a tile is cleared
    /// \param origin the central tile that is being cleared
    ///
    void clear (QPoint origin);

    ///
    /// \brief flag emitted when a flag is placed
    /// \param origin the central tile that is being flagged
    ///
    void flag  (QPoint origin);

    ///
    /// \brief chord emitted when a tile is chorded on
    /// \param origin the central tile that is being chorded on
    ///
    void chord (QPoint origin);

    ///
    /// \brief requestBoard from the minefield
    ///
    void requestBoard ();

    ///
    /// \brief requestChord from the minefield
    /// \param origin the central tile that is being chorded on
    ///
    void requestChord (QPoint origin);

    ///
    /// \brief requestIfCovered at the origin tile
    /// \param origin tile that is being checked
    ///
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

    ///
    /// \brief viewWon emitted if the game is won
    ///
    void viewWon ();

    ///
    /// \brief viewDead emitted if the game is lost
    ///
    void viewDead ();

public slots:
    ///
    /// \brief receiveBoard receives the board from the model
    /// \param boardSize size of the board
    /// \param board the array of the underlying board
    /// \param covers the array of the covers on the board
    ///
    void receiveBoard (const QSize &boardSize, const int *board, const Tile *covers);

    ///
    /// \brief flagPlaced draws flag if it is placed
    /// \param point the tile being flagged
    /// \param numFlags the number of flags left
    ///
    void flagPlaced (QPoint point, int numFlags);

    ///
    /// \brief flagRemoved undraws flag if it is removed
    /// \param point the tile being unflagged
    /// \param numFlags the number of flags left
    ///
    void flagRemoved (QPoint point, int numFlags);

    ///
    /// \brief lessonHighlightPlaced draws highlight frame if it is being placed
    /// \param point the tile being highlighted
    /// \param color the color of the frame
    ///
    void lessonHighlightPlaced (QPoint point, int color);

    ///
    /// \brief lessonHighlightPlaced undraws highlight frame if it is being placed
    /// \param point the tile being unhighlighted
    /// \param color the color of the frame
    ///
    void lessonHighlightRemoved (QPoint point);

    ///
    /// \brief displayHighlight draws the highlighted tiles
    /// \param coveredTiles the tiles that are covered
    ///
    void displayHighlight (QList<QPoint> coveredTiles);

    ///
    /// \brief receiveIfCovered receives signal to see if a tile is covered
    /// \param origin the tile being checked
    /// \param covered the boolean value
    ///
    void receiveIfCovered (QPoint origin, bool covered);

    ///
    /// \brief dead receives if the game is lost
    /// \param origin the point from which the game was lost
    /// \param mines the list of mines on the board
    ///
    void dead (QPoint origin, QList<QPoint> mines);

    ///
    /// \brief won receives if the game is won
    /// \param mines the list of mines on the board
    ///
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

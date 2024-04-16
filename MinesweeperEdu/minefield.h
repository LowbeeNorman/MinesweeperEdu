#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <QObject>
#include <QSize>
#include <QPoint>
#include <QList>

enum class Tile {
    blank,
    covered,
    flagged
};

class Minefield : public QObject
{
    Q_OBJECT

public:
    Minefield(QSize boardSize, float mineFreq);

private:
    QSize boardSize;
    int arrayLength;
    float mineFreq;
    int numMines;
    int numFlags;
    int* field;
    Tile* tiles;
    bool firstMove;

    ///
    /// \brief initializeField initializes a randomized minefield using the proper
    /// boardSize and mineFreq values.
    ///
    void initializeField ();

    ///
    /// \brief guaranteeSafe guarantees the first move is a safe move
    /// by checking if there is a mine under the first move and moving
    /// it to a random location elsewhere on the minefield if there is space.
    /// \param firstTile specifies which tile to check.
    void guaranteeSafe (QPoint firstTile);

    ///
    /// \brief populateFieldNums populates each cell with the value corresponding to
    /// how many of its neighbors contain mines.
    ///
    void populateFieldNums ();

    ///
    /// \brief floodFill uses the recursive flood fill algorithm to automatically uncover
    /// connected tile which are covered and not flagged if they have no mines underneath.
    /// Border tiles are determined by tiles which are adjacent to mines.
    /// \param selectedTile the origin from which to floodFill.
    ///
    void floodFill (QPoint selectedTile);

    ///
    /// \brief pointToIndex converts a QPoint to an array index in the backing array
    /// for the field.
    /// \param point the point to convert.
    /// \return int index that represents the point.
    ///
    int pointToIndex (QPoint point);

    ///
    /// \brief checkNeighborAt checks whether the direct neighbor to the origin point at
    /// the relative x and y coordinates contains a mine.
    /// \param origin the centeral point of reference
    /// \param relativeX x coordinate of the neighbor relative to the origin
    /// \param relativeY y coordinate of the neighbor relative to the origin
    /// \return whether or not there is a mine there
    ///
    template<typename A>
    bool checkNeighborAt(QPoint origin, int relativeX, int relativeY, A *array, A check);

public slots:
    ///
    /// \brief flag sets a tile to be flag if it is still covered.
    /// \param point the tile to be flagged.
    /// \return true if able to be flagged, false if tile already uncovered.
    ///
    void flag (QPoint point);
    ///
    /// \brief clear calls floodFill to clear tiles which are safe.
    /// \param origin the starting point for floodFill.
    ///
    void clear (QPoint origin);
    void chord (QPoint origin);

signals:
    ///
    /// \brief flagPlaced emitted when a flag is placed
    /// \param point the location of the flag
    /// \param numFlags the total number of flags left
    ///
    void flagPlaced(QPoint point, int numFlags);

    ///
    /// \brief dead emitted when
    /// \param origin point of death
    ///
    void dead(QPoint origin);

    ///
    /// \brief updateBoard emitted when the board has changed
    ///
    void updateBoard();

    void sendChord (QList<QPoint> coveredTiles, QList<QPoint> flaggedTiles);
};

#endif // MINEFIELD_H

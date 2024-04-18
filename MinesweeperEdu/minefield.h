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
    Minefield (QSize boardSize, float mineFreq);
    Minefield (QSize boardSize, bool mines[]);
    Minefield (const Minefield &other);

    ~Minefield ();
    Minefield &operator= (Minefield other);

    QSize getSize ();
private:
    QSize boardSize;
    int arrayLength;
    int numMines;
    int numFlags;
    int* field;
    Tile* tiles;
    bool firstMove;
    bool initialized;

    ///
    /// \brief initializeField initializes a randomized minefield using the
    /// proper boardSize and mineFreq values.
    ///
    void initializeField (int numSafeSpaces);

    ///
    /// \brief guaranteeSafe guarantees the first move is a safe move
    /// by checking if there is a mine under the first move and moving
    /// it to a random location elsewhere on the minefield if there is space.
    /// \param firstTile specifies which tile to check.
    void guaranteeSafe (QPoint firstTile);

    ///
    /// \brief populateFieldNums populates each cell with the value
    /// corresponding to how many of its neighbors contain mines.
    ///
    void populateFieldNums ();

    ///
    /// \brief floodFill uses the recursive flood fill algorithm to
    /// automatically uncover connected tile which are covered and not flagged
    /// if they have no mines underneath. Border tiles are determined by tiles
    /// which are adjacent to mines.
    /// \param selectedTile the origin from which to floodFill.
    ///
    void floodFill (QPoint selectedTile);

    ///
    /// \brief pointToIndex converts a QPoint to an array index in the backing
    /// array for the field.
    /// \param point the point to convert.
    /// \return int index that represents the point.
    ///
    int pointToIndex (QPoint point);

    QPoint indexToPoint (int index);

    ///
    /// \brief checkNeighborAt checks whether the direct neighbor to the
    /// origin point at the relative x and y coordinates contains a mine.
    /// \param origin the centeral point of reference
    /// \param relativeX x coordinate of the neighbor relative to the origin
    /// \param relativeY y coordinate of the neighbor relative to the origin
    /// \return whether or not there is a mine there
    ///
    template<typename A>
    bool checkNeighborAt(QPoint origin, int relativeX, int relativeY
                         , A *array, A check);

    ///
    /// \brief internalClear
    /// \param origin
    /// \return if the clear changed anything
    ///
    bool internalClear (QPoint origin);

    bool checkForWin ();
    QList<QPoint> getMines ();

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
    void getSurroundings (QPoint origin);
    void getIfCovered (QPoint origin);
    void chord (QPoint origin);
    void requestBoard ();

signals:
    ///
    /// \brief flagPlaced emitted when a flag is placed
    /// \param point the location of the flag
    /// \param numFlags the total number of flags left
    ///
    void flagPlaced(QPoint point, int numFlags);
    void flagRemoved (QPoint point, int numFlags);

    ///
    /// \brief dead emitted when
    /// \param origin point of death
    ///
    void dead (QPoint origin, QList<QPoint> mines);
    void won (QList<QPoint> mines);

    ///
    /// \brief updateBoard emitted when the board has changed
    ///
    void updateBoard (const int *field, const Tile *tiles);

    void sendChord (QList<QPoint> coveredTiles);
    void sendCovered (QPoint origin, bool covered);
};

#endif // MINEFIELD_H

#ifndef MINEFIELD_H
#define MINEFIELD_H
#include <QSize>
#include <QPoint>

enum class Tile {
    blank,
    covered,
    flagged
};

class Minefield
{
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
    void initializeField();

    ///
    /// \brief guaranteeSafe guarantees the first move is a safe move
    /// by checking if there is a mine under the first move and moving
    /// it to a random location elsewhere on the minefield if there is space.
    /// \param firstTile specifies which tile to check.
    void guaranteeSafe(QPoint firstTile);

    ///
    /// \brief floodFill uses the recursive flood fill algorithm to automatically uncover
    /// connected tile which are covered and not flagged if they have no mines underneath.
    /// Border tiles are determined by tiles which are adjacent to mines.
    /// \param selectedTile the origin from which to floodFill.
    ///
    void floodFill(QPoint selectedTile);

    ///
    /// \brief pointToIndex converts a QPoint to an array index in the backing array
    /// for the field.
    /// \param point the point to convert.
    /// \return int index that represents the point.
    ///
    int pointToIndex(QPoint point);

public slots:
    bool flag(QPoint);
    bool clear(QPoint);

};

#endif // MINEFIELD_H

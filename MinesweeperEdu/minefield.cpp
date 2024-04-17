#include "minefield.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
#include <ctime>
// testing
#include <QDebug>
#include <QRect>
#include <QTimer>
#include <cstdio>
#include <cstring>

Minefield::Minefield(QSize boardSize, float mineFreq)
    : boardSize(boardSize)
    , mineFreq(mineFreq)
    , pos (0)
{
    arrayLength = boardSize.height() * boardSize.width();
    numMines = (int) (arrayLength * mineFreq);
    numFlags = numMines;
    field = new int[arrayLength] {0};
    tiles = new Tile[arrayLength];
    for (int i = 0; i < arrayLength; ++i)
        tiles[i] = Tile::covered;
    firstMove = true;
}

QSize Minefield::getSize ()
{
    return boardSize;
}

void Minefield::initializeField (int safeArea) {
    for (int i = 0; i < arrayLength; i++) {
        field[i] = (i < numMines) ? 9 : 0;
    }
    unsigned seed = std::chrono::system_clock::now()
                        .time_since_epoch().count();
    shuffle(field, field + arrayLength - safeArea
            , std::default_random_engine(seed));
}

bool adjacent (QPoint p1, QPoint p2)
{
    QPoint difference = p1 - p2;
    difference.setX (abs (difference.x ()));
    difference.setY (abs (difference.y ()));
    return difference.x () <= 1 && difference.y () <= 1;
}


void Minefield::guaranteeSafe (QPoint firstTile) {
    // ------ TESTING -------
    qInfo () << "made it to the method";
    // ------ TESTING -------
    // get a rectangle representing the area we want to keep safe
    QRect safeArea = QRect(QPoint (0, 0), boardSize)
                         .intersected(QRect(firstTile.x () - 1
                                            , firstTile.y () - 1
                                            , 3
                                            , 3));
    initializeField (safeArea.height () * safeArea.width ());
    // ------ TESTING -------
    qInfo () << "safe area: " << safeArea;
    int topLeft = pointToIndex (safeArea.topLeft ());
    qInfo () << "top left" << topLeft << "is at coords" << safeArea.topLeft ();
    for (int y = 0; y < boardSize.height (); ++y)
    {
        printf ("[%d", field[pointToIndex (QPoint (0, y))]);
        for (int x = 1; x < boardSize.width (); ++x)
        {
            printf (" %d", field[pointToIndex (QPoint (x, y))]);
        }
        printf ("]\n");
    }
    // ------ TESTING -------
    for (int i = 0; i < safeArea.height (); ++i)
    // for (int rowLeftIndex = pointToIndex (safeArea.topLeft ());
    //      rowLeftIndex < pointToIndex (safeArea.bottomRight ());
    //      rowLeftIndex += boardSize.width ())
    {
        // move everything from the left edge of this row of the rectangle to
        // the right edge
        int rowLeftIndex = topLeft + boardSize.width () * i;
        int rowRightIndex = rowLeftIndex + safeArea.width ();

        // ------ TESTING -------
        qInfo () << "left:" << rowLeftIndex << "is at coords" << indexToPoint (rowLeftIndex);
        qInfo () << "right:" << rowRightIndex << "is at coords" << indexToPoint (rowRightIndex);
        // ------ TESTING -------

        memmove (field + rowRightIndex
                , field + rowLeftIndex
                , (arrayLength - rowRightIndex) * sizeof *field);
        // set everything within the row of the rectangle to zero
        memset (field + rowLeftIndex, 0, safeArea.width () * sizeof *field);

        // ------ TESTING -------
        // printf ("setting %p and %d elements to 0\n", field + rowLeftIndex, safeArea.width ());
        for (int y = 0; y < boardSize.height (); ++y)
        {
            printf ("[%d", field[pointToIndex (QPoint (0, y))]);
            for (int x = 1; x < boardSize.width (); ++x)
            {
                printf (" %d", field[pointToIndex (QPoint (x, y))]);
            }
            printf ("]\n");
        }
        // ------ TESTING -------
    }

    // TODO this strategy is causing infinite loops, fix
    // int index = pointToIndex(firstTile);
    // qInfo () << "first: " << firstTile;
    // size_t millis = 50;
    // for (int destPos = arrayLength - 1, srcPos = arrayLength - 1 - 9;
    //      destPos >= 0;
    //      --destPos, --srcPos)
    // {
    //     // if there were supposed to be less safe positions than 9
    //     // set all these to 0 (maybe fix this later, right now I
    //     // can't be bothered)
    //     if (srcPos < 0)
    //     {
    //         field[destPos] = 0;
    //         continue;
    //     }
    //     // if this spot is too close to the firstTile, move the dest pos up
    //     // one so it can stay the same for the next iteration
    //     QPoint dest = indexToPoint (destPos);
    //     if (adjacent (firstTile, dest))
    //     {
    //         qInfo () << "dest: " << dest << "=" << destPos << " src: " << indexToPoint (srcPos) << "=" << srcPos;
    //         srcPos++;
    //         // move the bomb up one position
    //         continue;
    //     }
    //     field[destPos] = field[srcPos];
    //     qInfo () << "dest: " << destPos << " src: " << srcPos;
        // int *field_copy = new int[arrayLength];
        // Tile *tiles_copy = new Tile[arrayLength];
        // memcpy (field_copy, field, arrayLength);
        // memcpy (tiles_copy, tiles, arrayLength);
        // fields.append (field_copy);
        // tileses.append (tiles_copy);
        // qInfo () << "pos: " << pos << " size: " << fields.size ();
        // QTimer::singleShot (millis, this, [this] {emit updateBoard (fields.at (pos), tileses.at (pos++));});
        // millis += 50;
    // }
    // for (int y = 0; i < boardSize.height (); ++y)
    // {
    //     for (int x = 0; x < boardSize.width (); ++x)
    //     {

    //     }
    // }
    // if (field[index] != 9) {
    //     return;
    // }
    // if (numMines >= arrayLength) {
    //     return;
    // }
    // int randomInt;
    // qInfo () << "starting loop";
    // while ((randomInt = std::rand() % arrayLength) != index || field[randomInt] == 9);
    // qInfo () << "Made it out";
    // std::swap(field[index], field[randomInt]);
}

void Minefield::populateFieldNums () {
    for (int y = 0; y < boardSize.height(); y++) {
        for (int x = 0; x < boardSize.width(); x++) {
            QPoint origin(x, y);
            int index = pointToIndex(origin);
            if (field[index] == 9) {
                continue;
            }
            for (int relY = -1; relY <= 1; relY++){
                for (int relX = -1; relX <= 1; relX++) {
                    if (checkNeighborAt(origin, relX, relY, field, 9)) {
                        field[index]++;
                    }
                }
            }
        }
    }
}

void Minefield::floodFill(QPoint selectedTile) {
    if (selectedTile.x () < 0 || selectedTile.y () < 0
        || selectedTile.x () >= boardSize.width ()
        || selectedTile.y () >= boardSize.height ())
    {
        return;
    }
    int index = pointToIndex(selectedTile);
    if (index < 0 || index >= arrayLength
        || tiles[index] != Tile::covered
        || 9 == field[index]) {
        return;
    }
    tiles[index] = Tile::blank;
    if (field[index] != 0) {
        return;
    }

    // start left, counter clockwise wrap, order matters
    floodFill(QPoint(selectedTile.x() - 1, selectedTile.y()));
    floodFill(QPoint(selectedTile.x() - 1, selectedTile.y() - 1));
    floodFill(QPoint(selectedTile.x(), selectedTile.y() - 1));
    floodFill(QPoint(selectedTile.x() + 1, selectedTile.y() - 1));
    floodFill(QPoint(selectedTile.x() + 1, selectedTile.y()));
    floodFill(QPoint(selectedTile.x() + 1, selectedTile.y() + 1));
    floodFill(QPoint(selectedTile.x(), selectedTile.y() + 1));
    floodFill(QPoint(selectedTile.x() - 1, selectedTile.y() + 1));
}

int Minefield::pointToIndex (QPoint point) {
    return point.y() * boardSize.width() + point.x();
}

QPoint Minefield::indexToPoint (int index)
{
    return QPoint (index % boardSize.width (), index / boardSize.width ());
}

template<typename A>
bool Minefield::checkNeighborAt(QPoint origin, int relativeX, int relativeY
                                , A *array, A check)
{
    origin.setX(origin.x() + relativeX);
    origin.setY(origin.y() + relativeY);
    if (origin.x() < 0 || origin.y() < 0
        || origin.x() >= boardSize.width()
        || origin.y() >= boardSize.height())
    {
        return false;
    }
    return array[pointToIndex(origin)] == check;
}

void Minefield::flag (QPoint point) {
    int index = pointToIndex(point);
    if (Tile::blank == tiles[index]) {
        return;
    }
    if (Tile::flagged == tiles[index])
    {
        tiles[index] = Tile::covered;
        numFlags++;
        emit flagRemoved (point, numFlags);
        return;
    }
    tiles[index] = Tile::flagged;
    numFlags--;
    emit flagPlaced(point, numFlags);
}

bool Minefield::internalClear (QPoint origin)
{
    int index = pointToIndex (origin);
    if (index < 0 || index >= arrayLength)
        return false;
    if (tiles[index] != Tile::covered) {
        return false;
    }
    floodFill(origin);
    return true;
}

void Minefield::clear (QPoint origin)
{
    if (firstMove) {
        firstMove = false;
        guaranteeSafe (origin);
        populateFieldNums ();
    }
    // floodFill(origin);
    if (internalClear (origin))
        emit updateBoard (field, tiles);
    if (9 == field[pointToIndex (origin)])
        emit dead (origin);
}

void Minefield::chord (QPoint origin) {
    int index = pointToIndex (origin);
    // don't allow chords on any tile that is not blank
    if (Tile::blank != tiles[index])
        return;
    // count how many flags surround this point and see if it matches the
    // number in the grid
    int flagCount = 0;
    for (int relY = -1; relY <= 1; ++relY)
    {
        for (int relX = -1; relX <= 1; ++relX)
        {
            // don't check the origin
            if (0 == relY && 0 == relX)
                continue;
            if (checkNeighborAt (origin, relX, relY, tiles, Tile::flagged))
                flagCount++;
        }
    }
    // if the number of flagged tiles around the origin doesn't match the
    // number of mines around it, do nothing
    if (flagCount != field[index])
        return;
    // clear everything around the origin
    for (int relY = -1; relY <= 1; ++relY)
    {
        for (int relX =  -1; relX <= 1; ++relX)
        {
            QPoint toClear (origin.x () + relX, origin.y () + relY);
            if (internalClear (toClear))
            {
                // the only time we should check for bombs is if the clear
                // was successful
                if (9 == field[pointToIndex (toClear)])
                    emit dead (toClear);
            }
        }
    }
    emit updateBoard (field, tiles);
}

void Minefield::getSurroundings (QPoint origin)
{
    QList<QPoint> coveredTiles;
    for (int relY = -1; relY <= 1; relY++)
    {
        for (int relX = -1; relX <= 1; relX++)
        {
            if (checkNeighborAt(origin, relX, relY, tiles, Tile::covered))
            {
                coveredTiles.append(QPoint (origin.x () + relX
                                           , origin.y () + relY));
            }
        }
    }
    emit sendChord (coveredTiles);
}

void Minefield::requestBoard () {
    emit updateBoard (field, tiles);
}

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
    : QObject (nullptr)
    , boardSize(boardSize)
    , arrayLength (boardSize.width() * boardSize.height ())
    , numMines (arrayLength * mineFreq)
    , numFlags (numMines)
    , firstMove (true)
    , initialized (false)
{
    field = new int[arrayLength] {0};
    tiles = new Tile[arrayLength];
    for (int i = 0; i < arrayLength; ++i)
        tiles[i] = Tile::covered;
}

Minefield::Minefield (QSize boardSize, bool mines[])
    : QObject (nullptr)
    , boardSize (boardSize)
    , arrayLength (boardSize.width () * boardSize.height ())
    , numMines (0)
    , numFlags (0)
    , firstMove (true)
    , initialized (true)
{
    field = new int[arrayLength] {0};
    tiles = new Tile[arrayLength];
    for (int i = 0; i < arrayLength; ++i)
    {
        tiles[i] = Tile::covered;
        if (mines[i])
        {
            numMines++;
            field[i] = 9;
        }
    }
}

Minefield::Minefield (const Minefield &other)
    : QObject (other.parent ())
    , boardSize (other.boardSize)
    , arrayLength (other.arrayLength)
    , numMines (other.numMines)
    , numFlags (other.numFlags)
    , firstMove (other.firstMove)
    , initialized (other.initialized)
{
    field = new int[arrayLength];
    tiles = new Tile[arrayLength];
    for (int i = 0; i < arrayLength; ++i)
    {
        tiles[i] = other.tiles[i];
        field[i] = other.field[i];
    }
}

Minefield::~Minefield ()
{
    delete[] field;
    delete[] tiles;
}

Minefield &Minefield::operator= (Minefield other)
{
    std::swap (boardSize, other.boardSize);
    std::swap (numMines, other.numMines);
    std::swap (numFlags, other.numFlags);
    std::swap (firstMove, other.firstMove);
    std::swap (initialized, other.initialized);
    std::swap (field, other.field);
    std::swap (tiles, other.tiles);
    return *this;
}

QSize Minefield::getSize ()
{
    return boardSize;
}

void Minefield::initializeField (int numSafeSpaces) {
    if (initialized)
        return;
    for (int i = 0; i < arrayLength; i++) {
        field[i] = (i < numMines) ? 9 : 0;
    }
    unsigned seed = std::chrono::system_clock::now()
                        .time_since_epoch().count();
    shuffle(field, field + arrayLength - numSafeSpaces
            , std::default_random_engine(seed));
    initialized = true;
}

bool adjacent (QPoint p1, QPoint p2)
{
    QPoint difference = p1 - p2;
    difference.setX (abs (difference.x ()));
    difference.setY (abs (difference.y ()));
    return difference.x () <= 1 && difference.y () <= 1;
}


void Minefield::guaranteeSafe (QPoint firstTile) {
    // get a rectangle representing the area we want to keep safe
    QRect safeArea = QRect(QPoint (0, 0), boardSize)
                         .intersected(QRect(firstTile.x () - 1
                                            , firstTile.y () - 1
                                            , 3, 3));
    // set up the bombs now that we know how many spaces need to be safe
    initializeField (safeArea.height () * safeArea.width ());
    int topLeft = pointToIndex (safeArea.topLeft ());
    for (int i = 0; i < safeArea.height (); ++i)
    {
        // move everything from the left edge of this row of the rectangle to
        // the right edge
        int rowLeftIndex = topLeft + boardSize.width () * i;
        int rowRightIndex = rowLeftIndex + safeArea.width ();

        memmove (field + rowRightIndex
                , field + rowLeftIndex
                , (arrayLength - rowRightIndex) * sizeof *field);
        // set everything within the row of the rectangle to zero
        memset (field + rowLeftIndex, 0, safeArea.width () * sizeof *field);
    }
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

void Minefield::floodFill(QPoint selectedTile)
{
    if (selectedTile.x () < 0 || selectedTile.y () < 0
        || selectedTile.x () >= boardSize.width ()
        || selectedTile.y () >= boardSize.height ())
    {
        return;
    }
    int index = pointToIndex(selectedTile);
    if (index < 0 || index >= arrayLength
        || tiles[index] != Tile::covered)
    {
        return;
    }
    tiles[index] = Tile::blank;
    if (field[index] != 0)
    {
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

int Minefield::pointToIndex (QPoint point)
{
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

QList<QPoint> Minefield::getMines ()
{
    QList<QPoint> mines;
    for (int i = 0; i < arrayLength; ++i)
    {
        if (9 == field[i])
            mines.append (indexToPoint (i));
    }
    return mines;
}

bool Minefield::checkForWin ()
{
    for (int i = 0; i < arrayLength; ++i)
    {
        // only look at tiles that don't have a bomb under them
        if (9 == field[i])
            continue;
        if (Tile::blank != tiles[i])
            return false;
    }
    return true;
}

void Minefield::clear (QPoint origin)
{
    if (firstMove) {
        firstMove = false;
        guaranteeSafe (origin);
        populateFieldNums ();
    }
    if (internalClear (origin))
        emit updateBoard (field, tiles);
    if (9 == field[pointToIndex (origin)])
        emit dead (origin, getMines ());
    else if (checkForWin ())
        emit won (getMines ());
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
        for (int relX = -1; relX <= 1; ++relX)
        {
            QPoint toClear (origin.x () + relX, origin.y () + relY);
            if (internalClear (toClear))
            {
                // the only time we should check for bombs is if the clear
                // was successful
                if (9 == field[pointToIndex (toClear)])
                {
                    emit dead (toClear, getMines ());
                }
            }
        }
    }
    emit updateBoard (field, tiles);
    if (checkForWin ())
        emit won (getMines ());
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

void Minefield::getIfCovered (QPoint origin)
{
    emit sendCovered (origin, Tile::covered == tiles[pointToIndex (origin)]);
}

void Minefield::requestBoard () {
    emit updateBoard (field, tiles);
}

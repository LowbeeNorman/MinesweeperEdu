/// Assignment 9: MinesweeperEdu
/// CS3505
/// 4/24/2024
/// Written by: Jayden Ferrin, Winston Ji

#include "minefield.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
#include <QDebug>
#include <QRect>
#include <QTimer>
#include <cstring>

Minefield::Minefield (QObject *parent)
    : QObject (parent)
    , boardSize (0, 0)
    , arrayLength (0)
    , numMines (0)
    , numFlags (0)
    , field (nullptr)
    , tiles (nullptr)
    , firstMove (false)
    , initialized (false)
    , autocomplete (false)
{}

Minefield::Minefield(QSize boardSize, float mineFreq)
    : QObject (nullptr)
    , boardSize(boardSize)
    , arrayLength (boardSize.width() * boardSize.height ())
    , numMines (arrayLength * mineFreq)
    , numFlags (numMines)
    , firstMove (true)
    , initialized (false)
    , autocomplete (true)
{
    field = new int[arrayLength] {0};
    tiles = new Tile[arrayLength];
    for (int i = 0; i < arrayLength; ++i)
        tiles[i] = Tile::covered;

    emit numFlagsChanged(numFlags);
    emit updateBoard(boardSize, field, tiles);
}

Minefield::Minefield (QSize boardSize, int numMines)
    : QObject (nullptr)
    , boardSize(boardSize)
    , arrayLength (boardSize.width() * boardSize.height ())
    , numMines (numMines)
    , numFlags (numMines)
    , firstMove (true)
    , initialized (false)
    , autocomplete (true)
{
    field = new int[arrayLength] {0};
    tiles = new Tile[arrayLength];
    for (int i = 0; i < arrayLength; ++i)
        tiles[i] = Tile::covered;

    emit numFlagsChanged(numFlags);
}

Minefield::Minefield (QSize boardSize, bool mines[])
    : QObject (nullptr)
    , boardSize (boardSize)
    , arrayLength (boardSize.width () * boardSize.height ())
    , numMines (0)
    , numFlags (0)
    , firstMove (false)
    , initialized (true)
    , autocomplete (false)
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
    populateFieldNums();
    emit numFlagsChanged(numFlags);
}

Minefield::Minefield (const Minefield &other)
    : QObject (other.parent ())
    , boardSize (other.boardSize)
    , arrayLength (other.arrayLength)
    , numMines (other.numMines)
    , numFlags (other.numFlags)
    , firstMove (other.firstMove)
    , initialized (other.initialized)
    , autocomplete (other.autocomplete)
{
    field = new int[arrayLength];
    tiles = new Tile[arrayLength];
    for (int i = 0; i < arrayLength; ++i)
    {
        tiles[i] = other.tiles[i];
        field[i] = other.field[i];
    }

    emit numFlagsChanged(numFlags);
}

void Minefield::setField (QSize boardSize, bool mines[])
{
    this->boardSize = boardSize;
    arrayLength = boardSize.width () * boardSize.height ();
    firstMove = false;
    initialized = true;
    autocomplete = false;
    delete[] field;
    delete[] tiles;
    // make sure it doesn't crash
    if (arrayLength <= 0)
        return;
    field = new int[arrayLength] {0};
    tiles = new Tile[arrayLength];
    numMines = 0;
    for (int i = 0; i < arrayLength; ++i)
    {
        tiles[i] = Tile::covered;
        if (mines[i])
        {
            field[i] = 9;
            numMines++;
        }
    }
    numFlags = numMines;
    populateFieldNums ();
    emit updateBoard (boardSize, field, tiles);
    emit numFlagsChanged(numFlags);
}

void Minefield::resetField (QSize boardSize, float mineFreq)
{
    // set the new size
    this->boardSize = boardSize;
    arrayLength = boardSize.width () * boardSize.height ();
    numMines = mineFreq * arrayLength;
    numFlags = numMines;
    autocomplete = true;
    // reset to the first move
    firstMove = true;
    initialized = false;
    // delete the old field and tiles
    delete[] field;
    delete[] tiles;
    field = new int[arrayLength] {0};
    tiles = new Tile[arrayLength];
    for (int i = 0; i < numMines; ++i)
    {
        field[i] = 9;
    }
    for (int i = 0; i < arrayLength; ++i)
    {
        tiles[i] = Tile::covered;
    }
    emit updateBoard (boardSize, field, tiles);
    emit numFlagsChanged (numFlags);
}

void Minefield::setAutoComplete (bool autocomplete)
{
    this->autocomplete = autocomplete;
}

Minefield::~Minefield ()
{
    if (nullptr != field)
        delete[] field;
    if (nullptr != tiles)
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
    for (int y = 0; y < boardSize.height(); ++y) {
        for (int x = 0; x < boardSize.width(); ++x) {
            QPoint origin(x, y);
            int index = pointToIndex(origin);
            if (field[index] == 9) {
                continue;
            }
            for (int relY = -1; relY <= 1; ++relY){
                for (int relX = -1; relX <= 1; ++relX) {
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
    if (nullptr == tiles)
        return;
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
    emit numFlagsChanged(numFlags);
}

void Minefield::highlightPlaced(QPoint point, int color)
{
    emit lessonHighlightPlaced(point, color);
}

void Minefield::highlightRemoved(QPoint point)
{
    emit lessonHighlightRemoved(point);
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

QList<QPoint> Minefield::getMinesLeft ()
{
    QList<QPoint> mines;
    if (!autocomplete)
        return mines;
    for (int i = 0; i < arrayLength; ++i)
    {
        if (9 == field[i] && tiles[i] != Tile::flagged)
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
    if (nullptr == tiles)
        return;
    if (firstMove) {
        firstMove = false;
        guaranteeSafe (origin);
        populateFieldNums ();
    }
    if (!internalClear (origin))
        return;
    emit updateBoard (boardSize, field, tiles);
    if (9 == field[pointToIndex (origin)] && Tile::blank == tiles[pointToIndex (origin)])
        emit dead (origin, getMines ());
    else if (checkForWin ())
        emit won (getMinesLeft ());
}

void Minefield::chord (QPoint origin) {
    if (nullptr == tiles)
        return;
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
            if (!internalClear (toClear))
                continue;
            // the only time we should check for bombs is if the clear
            // was successful
            if (9 == field[pointToIndex (toClear)] && Tile::blank == tiles[pointToIndex (toClear)])
                emit dead (toClear, getMines ());
        }
    }
    emit updateBoard (boardSize, field, tiles);
    if (checkForWin ())
        emit won (getMinesLeft ());
}

void Minefield::getSurroundings (QPoint origin)
{
    QList<QPoint> coveredTiles;
    for (int relY = -1; relY <= 1; ++relY)
    {
        for (int relX = -1; relX <= 1; ++relX)
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

void Minefield::requestBoard ()
{
    emit updateBoard (boardSize, field, tiles);
}

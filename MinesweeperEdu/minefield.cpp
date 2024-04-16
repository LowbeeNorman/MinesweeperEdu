#include "minefield.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
#include <ctime>

Minefield::Minefield(QSize boardSize, float mineFreq)
    : boardSize(boardSize)
    , mineFreq(mineFreq)
{
    arrayLength = boardSize.height() * boardSize.width();
    numMines = (int)(arrayLength * mineFreq);
    numFlags = numMines;
    field = new int[arrayLength];
    tiles = new Tile[arrayLength];
    firstMove = true;
    initializeField();
}

void Minefield::initializeField() {
    for (int i = 0; i < arrayLength; i++) {
        field[i] = (i < numMines) ? 9 : 0;
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(field, field + arrayLength, std::default_random_engine(seed));
}

void Minefield::guaranteeSafe (QPoint firstTile) {
    int index = pointToIndex(firstTile);
    if (field[index] != 9) {
        return;
    }
    if (numMines >= arrayLength) {
        return;
    }
    int randomInt;
    while ((randomInt = std::rand() % arrayLength) != index || field[randomInt] == 9);
    std::swap(field[index], field[randomInt]);
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
    int index = pointToIndex(selectedTile);
    if (index < 0 || index >= arrayLength
        || tiles[index] != Tile::covered) {
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

template<typename A>
bool Minefield::checkNeighborAt(QPoint origin, int relativeX, int relativeY, A *array, A check) {
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
    if (tiles[index] != Tile::covered) {
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
        emit updateBoard ();
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
                // the only time we should check for bombs is if the clear was successful
                if (9 == field[pointToIndex (toClear)])
                    emit dead (toClear);
            }
        }
    }
    emit updateBoard ();
}

void Minefield::getSurroundings (QPoint origin)
{
    QList<QPoint> coveredTiles, flaggedTiles;
    for (int relY = -1; relY <= 1; relY++)
    {
        for (int relX = -1; relX <= 1; relX++)
        {
            if (checkNeighborAt(origin, relX, relY, tiles, Tile::covered))
            {
                coveredTiles.append(QPoint (origin.x () + relX, origin.y () + relY));
            }
            // TODO remove this part since the view doesn't really need to
            // know how many flags there are around this point
            if (checkNeighborAt(origin, relX, relY, tiles, Tile::flagged))
            {
                flaggedTiles.append(QPoint (origin.x () + relX, origin.y () + relY));
            }
        }
    }
    emit sendChord (coveredTiles, flaggedTiles);
}

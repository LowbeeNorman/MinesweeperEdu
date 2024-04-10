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
}

void Minefield::initializeField() {
    for (int i = 0; i < arrayLength; i++) {
        field[i] = (i < numMines) ? 9 : 0;
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(field, field + arrayLength, std::default_random_engine(seed));
}

void Minefield::guaranteeSafe(QPoint firstTile) {
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

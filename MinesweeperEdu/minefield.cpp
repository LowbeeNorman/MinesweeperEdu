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
    int arraySlot = firstTile.y() * boardSize.width() + firstTile.x();
    if (field[arraySlot] != 9) {
        return;
    }
    if (numMines >= arrayLength) {
        return;
    }
    int randomInt;
    while ((randomInt = std::rand() % arrayLength) != arraySlot || field[randomInt] == 9);
    std::swap(field[arraySlot], field[randomInt]);
}

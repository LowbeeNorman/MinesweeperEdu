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

    void initializeField();
    void guaranteeSafe(QPoint);
    void floodFill(QPoint);

public slots:
    bool flag(QPoint);
    bool clear(QPoint);

};

#endif // MINEFIELD_H

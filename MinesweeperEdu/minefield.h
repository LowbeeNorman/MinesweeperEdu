/// Assignment 9: MinesweeperEdu
/// CS3505
/// 4/24/2024
/// Written by: Jayden Ferrin, Winston Ji

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

///
/// \brief The minefield class represents all backend aspects for the minesweeper board included in lessons
///
class Minefield : public QObject
{
    Q_OBJECT

public:
    ///
    /// \brief Minefield default constructor that creates a minefield with
    /// uninitialized field and tiles
    /// \param parent passed to the base constructor
    ///
    Minefield (QObject *parent = nullptr);

    ///
    /// \brief Minefield constructor using size and frequencies to generate random board
    /// \param boardSize dimensions of the board
    /// \param mineFreq frequency of mines on the board
    ///
    Minefield (QSize boardSize, float mineFreq);

    ///
    /// \brief Minefield constructor used to load predetermined boards for quizzes
    /// \param boardSize dimensions of the board
    /// \param mines number of mines in the board
    ///
    Minefield (QSize boardSize, bool mines[]);

    // methods to implement rule of 3
    Minefield (const Minefield &other);
    ~Minefield ();
    Minefield &operator= (Minefield other);

    ///
    /// \brief setField used by model to setup a new board
    /// \param boardSize dimensions of the board
    /// \param mines number of mines
    ///
    void setField (QSize boardSize, bool mines[]);

    ///
    /// \brief setAutoComplete sets when a board is able to auto complete the rest of the flags
    /// \param autocomplete
    ///
    void setAutoComplete (bool autocomplete);

    ///
    /// \brief getSize getter for board size
    /// \return QSize of the board
    ///
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
    bool autocomplete;

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

    ///
    /// \brief Converts an index to a point
    /// \param index
    /// \return a QPoint
    ///
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

    ///
    /// \brief Check to see if the board is in a completed state
    /// \return true if it is completed, false otherwise
    ///
    bool checkForWin ();

    ///
    /// \brief A method to get the locations for mines
    /// \return A QList of QPoints that represent mine locations
    ///
    QList<QPoint> getMines ();

    ///
    /// \brief A method to get the locations for all mines remaining
    /// \return A QList of QPoints that represent mine locations for remaining mines
    ///
    QList<QPoint> getMinesLeft ();

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
    ///
    /// \brief listens for a highlight to be placed
    /// \param the point the highlight was placed on
    /// \param the color of the highlight
    ///
    void highlightPlaced (QPoint point, int color);
    ///
    /// \brief listens for a highlight to be removed
    /// \param the point the highlight was removed from
    ///
    void highlightRemoved (QPoint point);
    ///
    /// \brief listens for a click, and returns the surrounding numbers from that click
    /// \param the point clicked
    ///
    void getSurroundings (QPoint origin);

    ///
    /// \brief getIfCovered getter for if a tile is covered
    /// \param origin central tile that we are checking
    ///
    void getIfCovered (QPoint origin);

    ///
    /// \brief chord uncovers the tiles around the origin
    /// \param origin the central tile that we are checking
    ///
    void chord (QPoint origin);

    ///
    /// \brief requestBoard listens for if the MinesweeperView is needing the current board.
    ///
    void requestBoard ();

    ///
    /// \brief resetField used by Freeplay to reset the board
    /// \param boardSize dimensions of the board
    /// \param mineFreq frequency of mines on the board
    ///
    void resetField (QSize boardSize, float mineFreq);

signals:
    ///
    /// \brief flagPlaced emitted when a flag is placed
    /// \param point the location of the flag
    /// \param numFlags the total number of flags left
    ///
    void flagPlaced(QPoint point, int numFlags);

    ///
    /// \brief numFlagsChanged emitted when a flag is used or unused
    /// \param numFlags the current number of flags remaining
    ///
    void numFlagsChanged(int numFlags);

    ///
    /// \brief flagRemoved emitted when a flag is removed
    /// \param point the location of the old flag
    /// \param numFlags the total number of flags left
    ///
    void flagRemoved (QPoint point, int numFlags);
    ///
    /// \brief dead emitted when lesson is failed
    /// \param origin point of death
    ///
    void dead (QPoint origin, QList<QPoint> mines);
    ///
    /// \brief won emitted when lesson is completed
    /// \param mines all mines that were on the board
    ///
    void won (QList<QPoint> mines);

    ///
    /// \brief updateBoard emitted when the board has changed
    ///
    void updateBoard (const QSize &boardSize, const int *field, const Tile *tiles);

    ///
    /// \brief sendChord emits which tiles are in the chord
    /// \param coveredTiles the tiles in the chord
    ///
    void sendChord (QList<QPoint> coveredTiles);

    ///
    /// \brief sendCovered sends if a tile is covered
    /// \param origin the central tile we are checking
    /// \param covered boolean of if the tile is covered
    ///
    void sendCovered (QPoint origin, bool covered);

    ///
    /// \brief lessonHighlightPlaced emitted when a highlight has been placed on the board
    /// \param point the tile to be highlighted
    /// \param color the color of the frame
    ///
    void lessonHighlightPlaced (QPoint point, int color);

    ///
    /// \brief lessonHighlightRemoved
    /// \param point
    ///emitted when a highlight has been removed from the board
    void lessonHighlightRemoved (QPoint point);
};

#endif // MINEFIELD_H

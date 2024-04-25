/// Assignment 9: MinesweeperEdu
/// CS3505
/// 4/24/2024
/// Written by: Kyle Stewart, Noah Sikorski, Jayden Ferrin

#ifndef USERMOVE_H
#define USERMOVE_H
#include <QPoint>
#include <QJsonObject>

///
/// \brief UserMove represents a click that the user can make on the minesweeper board
///
class UserMove
{
public:
    UserMove(QPoint cell);
    UserMove();
    ///
    /// \brief Builds a UserMove from JSON
    /// \param obj
    ///
    UserMove(QJsonObject &obj);
    enum class MoveType
    {
        FLAG, CLEAR, RED, ORANGE, YELLOW, PINK, BLUE, PURPLE, BROWN, BLACK, HIGHLIGHTREMOVED
    };

    ///
    /// \brief get the cell that the user clicked on
    /// \return a qpoint
    ///
    QPoint getCell ();
    ///
    /// \brief get the type of square that is on a square
    /// \return a movetype, representing what the square is
    ///
    MoveType getType ();
    ///
    /// \brief get the index of the current instruction
    /// \return an index, representing the current location
    ///
    int getInstructionIndex();
private:
    QPoint cell;
    MoveType type;
    int instructionIndex;
};

#endif // USERMOVE_H

/// Assignment 9: MinesweeperEdu
/// CS3505
/// 4/24/2024
/// Written by: Kyle Stewart, Noah Sikorski, Jayden Ferrin

#ifndef USERMOVE_H
#define USERMOVE_H
#include <QPoint>
#include <QJsonObject>
#include <QHash>

class UserMove;

///
/// \brief The MoveType enum defines types for moves the user can make
///
enum class MoveType
{
    FLAG, CLEAR,
    RED, ORANGE, YELLOW, PINK, BLUE, PURPLE, BROWN, BLACK, HIGHLIGHTREMOVED
};

///
/// \brief qHash provides a hashing method for the UserMove class so it can
/// be used in a QSet
/// \param key the UserMove object to hash
/// \param seed hash to be passed to make things more secure
/// \return the hash of the key
///
size_t qHash (const UserMove &key, size_t seed = 0) noexcept;

///
/// \brief UserMove represents a click that the user can make
/// on the minesweeper board
///
class UserMove
{
public:
    UserMove (QPoint cell, MoveType type);
    UserMove();
    ///
    /// \brief Builds a UserMove from JSON
    /// \param obj
    ///
    UserMove(QJsonObject &obj);

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

    ///
    /// \brief operator == defines equality for UserMove objects, used in
    /// putting them in the QSet
    /// \param other object to test equality against
    /// \return whether the 2 objects are equal
    ///
    bool operator== (const UserMove &other) const noexcept;
    // declare the qHash function as a friend so it can access internal members
    friend size_t qHash (const UserMove &key, size_t seed) noexcept;
private:
    QPoint cell;
    MoveType type;
    int instructionIndex;
};

#endif // USERMOVE_H

#ifndef USERMOVE_H
#define USERMOVE_H
#include <QPoint>
#include <QJsonObject>
#include <QHash>

class UserMove;

enum class MoveType
{
    FLAG, CLEAR, RED, ORANGE, YELLOW, PINK, BLUE, PURPLE, BROWN, BLACK, HIGHLIGHTREMOVED
};

size_t qHash (const UserMove &key, size_t seed = 0) noexcept;

class UserMove
{
public:
    UserMove (QPoint cell, MoveType type); //TODO add parameter for Right/Left Click
    UserMove();
    ///
    /// \brief Builds a UserMove from JSON
    /// \param obj
    ///
    UserMove(QJsonObject &obj);

    QPoint getCell ();
    MoveType getType ();
    int getInstructionIndex();

    bool operator== (const UserMove &other) const noexcept;
    friend size_t qHash (const UserMove &key, size_t seed) noexcept;
private:
    QPoint cell;
    MoveType type;
    int instructionIndex;
};

#endif // USERMOVE_H

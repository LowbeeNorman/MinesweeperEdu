#ifndef USERMOVE_H
#define USERMOVE_H
#include <QPoint>
#include <QJsonObject>

class UserMove
{
public:
    UserMove(QPoint cell); //ToDo add parameter for Right/Left Click
    UserMove();
    ///
    /// \brief Builds a UserMove from JSON
    /// \param obj
    ///
    UserMove(QJsonObject &obj);
    enum class MoveType
    {
        FLAG, CLEAR, RED, ORANGE, YELLOW, PINK, BLUE, PURPLE, BROWN
    };

    QPoint getCell ();
    MoveType getType ();
    int getInstructionIndex();
private:
    QPoint cell;
    MoveType type;
    int instructionIndex;
};

#endif // USERMOVE_H

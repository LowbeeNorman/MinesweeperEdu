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
        FLAG, CLEAR
    };
private:
    QPoint cell;
    MoveType type;
};

#endif // USERMOVE_H

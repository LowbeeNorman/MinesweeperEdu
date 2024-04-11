#ifndef USERMOVE_H
#define USERMOVE_H
#include <QPoint>

class UserMove
{
public:
    UserMove(QPoint cell); //ToDo add parameter for Right/Left Click
    UserMove();
    enum class MoveType
    {
        FLAG, CLEAR
    };
    MoveType type;
private:
    QPoint cell;
};

#endif // USERMOVE_H

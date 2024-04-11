#ifndef USERMOVE_H
#define USERMOVE_H
#include <QPoint>

class UserMove
{
public:
    UserMove();
private:
    QPoint cell;
    enum class MoveType
    {
        FLAG, CLEAR
    };
    MoveType type;
};

#endif // USERMOVE_H

#include "usermove.h"

UserMove::UserMove() {}

UserMove::UserMove(QJsonObject &obj) {
    QJsonObject qPointObj = obj.value("cell").toObject();
    int x = qPointObj.value("x").toInt();
    int y = qPointObj.value("y").toInt();
    cell = QPoint(x, y);

    int typeVal = obj.value("type").toInt();
    type = static_cast<MoveType>(typeVal);
}

QPoint UserMove::getCell ()
{
    return cell;
}

UserMove::MoveType UserMove::getType ()
{
    return type;
}

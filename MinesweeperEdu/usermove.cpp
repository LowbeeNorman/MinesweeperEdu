/// Assignment 9: MinesweeperEdu
/// CS3505
/// 4/24/2024
/// Written by: Kyle Stewart, Noah Sikorski, Jayden Ferrin

#include "usermove.h"

UserMove::UserMove() {}

UserMove::UserMove(QJsonObject &obj) {
    QJsonObject qPointObj = obj.value("cell").toObject();
    int x = qPointObj.value("x").toInt();
    int y = qPointObj.value("y").toInt();
    cell = QPoint(x, y);

    int typeVal = obj.value("type").toInt();
    type = static_cast<MoveType>(typeVal);

    instructionIndex = obj.value("index").toInt();
}

QPoint UserMove::getCell ()
{
    return cell;
}

UserMove::MoveType UserMove::getType ()
{
    return type;
}

int UserMove::getInstructionIndex ()
{
    return instructionIndex;
}

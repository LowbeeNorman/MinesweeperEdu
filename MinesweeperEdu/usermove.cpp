#include "usermove.h"

UserMove::UserMove() {}

UserMove::UserMove (QPoint cell, MoveType type)
    : cell (cell)
    , type (type)
{}

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

MoveType UserMove::getType ()
{
    return type;
}

int UserMove::getInstructionIndex ()
{
    return instructionIndex;
}

bool UserMove::operator== (const UserMove &other) const noexcept
{
    return cell == other.cell && type == other.type;
}

size_t qHash (const UserMove &key, size_t seed) noexcept
{
    QtPrivate::QHashCombine hash;
    seed = hash (seed, key.cell);
    seed = hash (seed, key.type);
    return seed;
}

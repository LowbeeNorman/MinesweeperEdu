#include "quiz.h"
#include <QJsonArray>

Quiz::Quiz() : minefield(nullptr) {}

Quiz& Quiz::operator=(Quiz rhs) {
    std::swap(correctMoves, rhs.correctMoves);
    std::swap(instructions, rhs.instructions);
    // swap minefields
    std::swap(minefield, rhs.minefield);
    return *this;
}

Quiz::Quiz (const Quiz &other)
    : correctMoves (other.correctMoves)
    , instructions (other.instructions)
{
    minefield = new Minefield (*other.minefield);
}

Quiz::~Quiz() {
    if(minefield != nullptr)
        delete minefield;
}

Quiz::Quiz(QJsonObject &obj) {
    int width = obj.value("width").toInt();
    int height = obj.value("height").toInt();

    QJsonArray minefieldArr = obj.value("minefield").toArray();
    bool field[minefieldArr.size ()] = {false};
    // Add all boolean values contained in the QJsonArray to the bool[]
    for(int i = 0; i < minefieldArr.size (); ++i)
    {
        field[i] = minefieldArr[i].toBool();
    }
    // Call method in minefield that constructs the board using the values collected.
    minefield = new Minefield (QSize (width, height), field);
    // Extract correct moves
    QJsonArray correctMovesArr = obj.value("correctMoves").toArray();
    for(int i = 0; i < correctMovesArr.size(); ++i)
    {
        QJsonObject userMoveObj = correctMovesArr.at(i).toObject();
        correctMoves.append(UserMove(userMoveObj));
    }
}

Minefield *Quiz::getMinefield ()
{
    return minefield;
}

/// Assignment 9: MinesweeperEdu
/// CS3505
/// 4/24/2024
/// Written by: Kyle Stewart and Noah Sikorski

#include "quiz.h"
#include <QJsonArray>

Quiz::Quiz() : minefield(nullptr) {}

Quiz& Quiz::operator=(Quiz rhs) {
    std::swap(correctMoves, rhs.correctMoves);
    std::swap(completedMoves, rhs.completedMoves);
    std::swap(instructions, rhs.instructions);
    std::swap(numInstructions, rhs.numInstructions);
    std::swap(numCorrectMovesLeft, rhs.numCorrectMovesLeft);
    // swap minefields
    std::swap(minefield, rhs.minefield);
    return *this;
}

Quiz::Quiz (const Quiz &other)
    : correctMoves (other.correctMoves)
    , completedMoves (other.completedMoves)
    , instructions (other.instructions)
    , minefield (other.minefield)
    , numInstructions (other.numInstructions)
    , numCorrectMovesLeft (other.numCorrectMovesLeft)
{}

Quiz::~Quiz() {}

Quiz::Quiz(QJsonObject &obj, Minefield *minefield)
    : minefield (minefield)
{
    int width = obj.value("width").toInt();
    int height = obj.value("height").toInt();

    {
        // set up the minefield with the values from json
        QJsonArray minefieldArr = obj.value("minefield").toArray();
        bool field[minefieldArr.size ()] = {false};
        // Add all boolean values contained in the QJsonArray to the bool[]
        for(int i = 0; i < minefieldArr.size (); ++i)
        {
            field[i] = minefieldArr[i].toBool();
        }
        minefield->setField (QSize (width, height), field);
    }

    // Extract correct moves
    QJsonArray correctMovesArr = obj.value("correctMoves").toArray();
    for(int i = 0; i < correctMovesArr.size(); ++i)
    {
        QJsonObject userMoveObj = correctMovesArr.at(i).toObject();
        correctMoves.insert(UserMove(userMoveObj));
    }
    numCorrectMovesLeft = correctMovesArr.size();

    //Extract completed moves
    QJsonArray completedMovesArr = obj.value("completedMoves").toArray();
    for(int i = 0; i < completedMovesArr.size(); ++i)
    {
        QJsonObject completedMovesObj = completedMovesArr.at(i).toObject();
        completedMoves.append(UserMove(completedMovesObj));
    }

    //Carry out moves
    executeMovesAtIndex(0, false);
    // Extract instructions
    QJsonArray instructionsArr = obj.value("instructions").toArray();
    numInstructions = 0;
    for(int i = 0; i < instructionsArr.size(); ++i)
    {
        instructions.append(instructionsArr.at(i).toString());
    }
    numInstructions = instructionsArr.size();
}

Minefield *Quiz::getMinefield ()
{
    return minefield;
}

const QString &Quiz::getInstructionFromIndex(int indexOfInstruction)
{
    return instructions.at(indexOfInstruction);
}

int Quiz::getNumInstructions ()
{
    return numInstructions;
}

int Quiz::getNumCorrectMovesLeft ()
{
    return numCorrectMovesLeft;
}

bool Quiz::hasCorrectMovesLeft ()
{
    return !(numCorrectMovesLeft == 0);
}

void Quiz::executeMovesAtIndex (int index, bool highlightOnly)
{
    for(int i = 0; i < completedMoves.size(); ++i)
    {
        if(completedMoves[i].getInstructionIndex() == index)
        {
            if (completedMoves[i].getType() == MoveType::FLAG && !highlightOnly)
            {
                this->minefield->flag(completedMoves[i].getCell());
            }
            else if (completedMoves[i].getType() == MoveType::CLEAR && !highlightOnly)
            {
                this->minefield->clear(completedMoves[i].getCell());
            }
            else if (completedMoves[i].getType()
                       == MoveType::HIGHLIGHTREMOVED)
            {
                this->minefield->highlightRemoved
                    (completedMoves[i].getCell());
            }
            else
            {
                this->minefield
                    ->highlightPlaced
                    (completedMoves[i].getCell()
                    , (int) completedMoves[i].getType());
            }
        }
    }
}

bool Quiz::verifyUserMove (QPoint coords, MoveType type)
{
    // UserMove currentMove = correctMoves.at(correctMoves.size()
    //                                        - numCorrectMovesLeft);
    UserMove currentMove(coords, type);
    //if (currentMove.getCell() == coords && currentMove.getType() == type)
    if (correctMoves.contains (currentMove))
    {
        numCorrectMovesLeft--;
        correctMoves.remove (currentMove);
        return true;
    }
    return false;
}

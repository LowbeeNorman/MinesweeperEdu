/// Assignment 9: MinesweeperEdu
/// CS3505
/// 4/24/2024
/// Caleb Norman

#include "model.h"
#include <QJsonDocument>
#include <QFile>
#include <QByteArray>
#include <QSaveFile>

Model::Model(QObject *parent)
    : QObject{parent}
    , numLessons (20)
    // , lessons (createLessonLevels ())
    // , currentLesson (lessons[0])
    , currentLessonIndex (0)
    , currentMessageIndex (0)
    , currentInstructionIndex (0)
    , maxLesson (0)
{}

Model::~Model () {}

Minefield &Model::getMinefield ()
{
    return minefield;
}

QList<LessonLevel> Model::createLessonLevels () {
    QList<LessonLevel> lessons;
    for (int i = 1; i <= numLessons; ++i)
    {
        lessons.append
            (constructLessonLevelFromJSON
                       (QString (":/json/lesson%1.json").arg (i)));
    }
    return lessons;
}

LessonLevel Model::constructLessonLevelFromJSON(QString filename) {
    QJsonDocument doc;
    QFile file (filename);
    // Return nothing if file cannot be opened
    if (!file.open (QIODevice::ReadOnly))
    {
        return LessonLevel ();
    }
    // array of bytes contained in file
    QByteArray array = file.readAll ();
    // make the json doc
    doc = QJsonDocument::fromJson (array);
    // create the lesson level from json
    return LessonLevel (doc, &minefield);
}

void Model::setLesson(int lessonNumber)
{
    // load this lesson from json
    currentLesson = constructLessonLevelFromJSON
        (QString (":/json/lesson%1.json").arg (lessonNumber));
    // TODO find out what the lesson wants the board to look like
    currentLessonIndex = lessonNumber;
    emit lessonTime ();
    emit sendLessonInfo (currentLesson.getTopic()
                        , currentLesson.getMessageFromIndex(0)
                        , currentLesson.getMinefield());
    emit sendCurrentLevel(lessonNumber);
    currentMessageIndex = 0;
    currentInstructionIndex = 0;
    currentLessonQuizMoves = currentLesson.getNumCorrectMovesLeft();
}

void Model::nextMessage()
{
    if (currentMessageIndex < currentLesson.getNumMessages() - 1)
    {
        currentMessageIndex++;
        currentLesson.executeMovesAtIndex(currentMessageIndex);
        emit sendCurrentMessage
            (currentLesson.getMessageFromIndex(currentMessageIndex));
    }
    else if (currentInstructionIndex < currentLesson.getNumInstructions())
    {
        emit sendCurrentInstruction
            (currentLesson.getInstructionFromIndex(currentInstructionIndex));
        currentInstructionIndex++;
        if (currentInstructionIndex == currentLesson.getNumInstructions())
        {
            // this will be used to enable the board so that the user can
            // conduct the quiz
            emit quizTime();
        }
    }
    // NOT SURE IF THIS IS NEEDED
    // User has completed the Quiz: moves on to next LessonLevel
    else if (!currentLesson.hasCorrectMovesLeft())
    {
        currentMessageIndex = 0;
        currentInstructionIndex = 0;
        emit quizCompleted ();
    }
    else if (currentLesson.hasCorrectMovesLeft())
    {
        // this will be used to enable the board so that the user can
        // conduct the quiz
        emit quizTime();
    }
}

void Model::previousMessage ()
{
    if (currentMessageIndex == 0)
        emit sendCurrentMessage
            (currentLesson.getMessageFromIndex(0));
    else if (currentInstructionIndex != 0)
    {
        currentInstructionIndex--;
        emit sendCurrentInstruction
            (currentLesson.getInstructionFromIndex(currentInstructionIndex));
    }
    else if (currentInstructionIndex == 0)
    {
        currentMessageIndex--;
        currentLesson.executeMovesAtIndex(currentMessageIndex);
        emit sendCurrentMessage
            (currentLesson.getMessageFromIndex(currentMessageIndex));
    }
}

void Model::receiveClearAttempted (QPoint origin)
{
    if(currentLesson.hasCorrectMovesLeft())
    {
        if(currentLesson.checkMove(origin, UserMove::MoveType::CLEAR))
        {
            emit updateCellClear (origin);

        }
        else
        {
            emit sendErrorMessage("Wrong move");
        }
    }
    else
    {
        emit sendErrorMessage ("All correct moves have been completed!"
                               " Click \"Next\" to move on!");
    }
    receiveProgressRequest();
}

void Model::receiveFlagAttempted (QPoint origin)
{
    if(currentLesson.hasCorrectMovesLeft())
    {
        if(currentLesson.checkMove(origin, UserMove::MoveType::FLAG))
        {
            emit updateCellFlag (origin);
        }
        else
        {
            emit sendErrorMessage("Wrong move");
        }
    }
    else
    {
        emit sendErrorMessage("All correct moves have been completed!"
                              " Click \"Next\" to move on!");
    }
    receiveProgressRequest();
}

void Model::setLessonToNext ()
{
    setLesson(++currentLessonIndex);
}

void Model::receiveProgressRequest()
{
    emit sendProgressUpdate(currentMessageIndex + currentLessonQuizMoves - currentLesson.getNumCorrectMovesLeft() + currentInstructionIndex
                            , currentLesson.getNumMessages() - 1 + currentLessonQuizMoves + currentLesson.getNumInstructions());
}

void Model::checkLessonNumber (int lessonNumber)
{
    if (lessonNumber - 1 > maxLesson)
        emit tooBigLessonNumber ();
    else
        emit validLessonNumber (lessonNumber);
}

void Model::loadUserProgressFile ()
{
    QFile file ("userProgress.json");
    // Return nothing if file cannot be opened
    if (!file.open (QIODevice::ReadOnly))
    {
        return;
    }
    // array of bytes contained in file
    QByteArray array = file.readAll ();
    // make the json doc
    QJsonDocument doc = QJsonDocument::fromJson (array);
    // get the json object
    QJsonObject obj = doc.object();
    // set maxLesson
    maxLesson = obj.value("maxLesson").toInt();
    file.close();
}

void Model::resetUserProgressInFile ()
{
    writeMaxLessonsToFile(0);
    maxLesson = 0;
}

void Model::writeMaxLessonsToFile (int maxLessonValue)
{
    // json object that holds value
    QJsonObject obj;
    obj.insert("maxLesson", maxLessonValue);
    // document to convert object to text stream
    QJsonDocument doc;
    doc.setObject(obj);
    // byte array of values
    QByteArray bytes = doc.toJson(QJsonDocument::Indented);
    // file to write to
    QSaveFile file("userProgress.json");
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << file.errorString();
        return;
    }
    if(file.write(bytes) < 0)
        return;
    file.commit();
}

void Model::increaseMaxLessonValue ()
{
    if (currentLessonIndex > maxLesson)
        maxLesson++;
    writeMaxLessonsToFile(maxLesson);
}

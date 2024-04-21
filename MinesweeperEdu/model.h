#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include <QObject>
#include "lessonlevel.h"

class Model : public QObject
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = nullptr);
    ~Model();

private:
    // list of tips
    QList<QString> gameTips;
    // list of all Lessons
    QList<LessonLevel> lessons;
    // number of lessons
    int numLessons;
    // current LessonLevel the user is on
    LessonLevel currentLesson;
    // current Message index of the current LessonLevel the user is on
    int currentMessageIndex;
    // currrent instruction index of the currnet LessonLevel the user is on
    int currentInstructionIndex;
    ///
    /// \brief Constructs all the LessonLevels for the application.
    ///
    void createLessonLevels();

    ///
    /// \brief Reads a JSON file from the given filename and returns the LessonLevel
    /// constructed from the JSON.
    /// \param filename name of the file to construct the LessonLevel from
    /// \return LessonLevel
    ///
    LessonLevel constructLessonLevelFromJSON(QString filename);

public slots:
    ///
    /// \brief Sets the LessonLevel number to the number passed.
    /// \param lessonNumber number of the LessonLevel
    ///
    void setLesson (int lessonNumber);

    ///
    /// \brief Returns the next message to the view
    ///
    void nextMessage ();

    ///
    /// \brief receives event of clear attempted at the origin
    /// \param origin cell left-clicked
    ///
    void receiveClearAttempted (QPoint origin);
signals:
    ///
    /// \brief Sends the information of the current LessonLevel back to the view
    /// \param topic topic of the LessonLevel
    /// \param firstMessage first message of the LessonLevel
    /// \param minefield the minefield representing the minesweeper board for this LessonLevel
    ///
    void sendLessonInfo(const QString &topic, const QString &firstMessage, Minefield &minefield);
    ///
    /// \brief Sends the current message the LessonLevel user is on
    /// \param message message
    ///
    void sendCurrentMessage(const QString &message);
    ///
    /// \brief Sends the current instruction the LessonLevel user is on
    /// \param message message
    ///
    void sendCurrentInstruction(const QString &instruction);
    ///
    /// \brief Tells the view to update the board by clearing the cell at the origin
    /// \param origin cell
    ///
    void updateCellClear (QPoint origin);
};

#endif // MODEL_H

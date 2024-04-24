#ifndef MODEL_H
#define MODEL_H

#include <QList>
#include <QObject>
#include "lessonlevel.h"

class Model : public QObject
{
    Q_OBJECT

public:
    explicit Model (QObject *parent = nullptr);
    ~Model ();

    Minefield &getMinefield ();

private:
    Minefield minefield;

    // list of tips
    QList<QString> gameTips;
    // number of lessons
    int numLessons;
    // list of all Lessons
    QList<LessonLevel> lessons;
    // current LessonLevel the user is on
    LessonLevel currentLesson;
    int currentLessonIndex;
    // current Message index of the current LessonLevel the user is on
    int currentMessageIndex;
    // currrent instruction index of the currnet LessonLevel the user is on
    int currentInstructionIndex;
    // the maximum lesson index a user can access
    int maxLesson;
    ///
    /// \brief Constructs all the LessonLevels for the application.
    ///
    QList<LessonLevel> createLessonLevels ();

    ///
    /// \brief Reads a JSON file from the given filename and returns the
    /// LessonLevel constructed from the JSON.
    /// \param filename name of the file to construct the LessonLevel from
    /// \return LessonLevel
    ///
    LessonLevel constructLessonLevelFromJSON (QString filename);

    ///
    /// \brief writes the given value to the user's progress file
    /// \param maxLessonValue max lesson value
    ///
    void writeMaxLessonsToFile (int maxLessonValue);

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
    /// \brief Returns the previous message to the view
    ///
    void previousMessage ();

    ///
    /// \brief receives event of clear attempted at the origin
    /// \param origin cell left-clicked
    ///
    void receiveClearAttempted (QPoint origin);

    ///
    /// \brief receives event of flag attempted at the origin
    /// \param origin cell right-clicked
    ///
    void receiveFlagAttempted (QPoint origin);

    ///
    /// \brief Sets the LessonLevel number to be the next one
    ///
    void setLessonToNext ();
    ///
    /// \brief Listens for a request on the progress of the current lesson
    ///
    void receiveProgressRequest ();

    ///
    /// \brief checks to see if the given lesson number is less than the max
    /// \param lessonNumber lesson number
    ///
    void checkLessonNumber (int lessonNumber);


    ///
    /// \brief loads in the file that contains the user's progress
    ///
    void loadUserProgressFile ();

    ///
    /// \brief resets the user's progress in the file
    ///
    void resetUserProgressInFile ();

    ///
    /// \brief increases the maxLesson value by 1
    ///
    void increaseMaxLessonValue ();
signals:
    ///
    /// \brief Sends the information of the current LessonLevel back to
    /// the view
    /// \param topic topic of the LessonLevel
    /// \param firstMessage first message of the LessonLevel
    /// \param minefield the minefield representing the minesweeper board for
    /// this LessonLevel
    ///
    void sendLessonInfo (const QString &topic, const QString &firstMessage
                        , Minefield &minefield);
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
    /// \brief Tells the view to update the board by clearing the cell at
    /// the origin
    /// \param origin cell
    ///
    void updateCellClear (QPoint origin);
    ///
    /// \brief Tells the view to update the board by flagging the cell at
    /// the origin
    /// \param origin cell
    ///
    void updateCellFlag (QPoint origin);
    ///
    /// \brief Informs the view that the Quiz has been completed successfully
    ///
    void quizCompleted ();
    ///
    /// \brief Sends an error message to be displayed
    /// \param message
    ///
    void sendErrorMessage (QString message);
    ///
    /// \brief Informs the view it is time for the user to complete the quiz
    ///
    void quizTime ();
    ///
    /// \brief Informs the view it is time for the user to start a lesson
    ///
    void lessonTime ();

    ///
    /// \brief Sends the levelIndex to whatever asks for it
    /// \param levelIndex - lesson number
    ///
    void sendCurrentLevel(int levelIndex);
    ///
    /// \brief Emits an update of the lesson progress to all listeners
    /// \param The current progress
    /// \param The current max, when the user is done with that portion of the lesson
    ///
    void sendProgressUpdate(int current, int max);

    ///
    /// \brief informs the view the lesson number selected is too big
    ///
    void tooBigLessonNumber ();

    ///
    /// \brief informs the view the lesson number selected is valid
    ///
    void validLessonNumber (int lessonNumber);
};

#endif // MODEL_H

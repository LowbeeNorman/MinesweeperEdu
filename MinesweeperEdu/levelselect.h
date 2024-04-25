/// Assignment 9: Educational App
/// CS3505
/// 4/16/2024
/// Written by: Caleb Norman, Abdul Asim

#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QButtonGroup>

namespace Ui {
class LevelSelect;
}
///
/// \brief The LevelSelect class deals with view concerns for the part of the program
/// that allows users to select a level. This class is meant to be put into the mainwindow
///
class LevelSelect : public QWidget
{
    Q_OBJECT

public:
    explicit LevelSelect(QWidget *parent = nullptr);
    ~LevelSelect();
    QPushButton *currentButton = nullptr;

private:
    Ui::LevelSelect *ui;
    int currentLevel = 0;

    QGraphicsPixmapItem *pixmapItem;
    QPixmap *levels[40];
    QGraphicsScene *scene;

    QButtonGroup *group;

public slots:

    /// \brief Receives the current level and button from the view
    /// \param Index of the currently selected level
    /// \param Last clicked button
    void getCurrentLevel(QAbstractButton *button, bool checked);

    ///
    /// \brief Listens to the play button being clicked
    ///
    void playButtonClicked();

    ///
    /// \brief Listens to the menu button being clicked
    ///
    void menuButtonClicked();

    ///
    /// \brief Handles some logic for resetting UI when starting a new game
    /// it listens to the startscreen class
    ///
    void receiveStartingNewGame();

    ///
    /// \brief Highlights the level button that is sent to the method
    ///
    void updateCurrentLevel(int levelIndex);

    ///
    /// \brief receiveMaxLesson from the model and updates level button locks
    ///
    void receiveMaxLesson(int maxLesson);

signals:
    ///
    /// \brief Emits the current level, so that we can load the correct lesson
    /// \param The selected lesson to load
    ///
    void sendCurrentLevel(int levelIndex);

    ///
    /// \brief Emits that the menu button has been clicked, and the view should be
    /// updated correspondingly
    /// \param The index to change the mainwindow stacked widget to
    ///
    void sendMenuClicked(int menuIndex);

    ///
    /// \brief disableNextLesson
    ///
    void disableNextLesson();

    ///
    /// \brief enableNextLesson
    ///
    void enableNextLesson();
};

#endif // LEVELSELECT_H

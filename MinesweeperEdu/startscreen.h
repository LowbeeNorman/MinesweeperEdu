/// Assignment 9: Educational App
/// CS3505
/// 4/17/24
/// Written by: Caleb Norman, Abdul Asim, Winston Ji

#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QPainter>

namespace Ui {
class StartScreen;
}

///
/// \brief The StartScreen class deals with view concerns for the part of the program
/// that allows users to start a new game or continue the same one. This class is meant
/// to be put into the mainwindow
///
class StartScreen : public QWidget
{
    Q_OBJECT
    b2World world;
    b2Body* body;
    QTimer* timer = new QTimer(this);

public:
    ///
    /// \brief StartScreen default constructor for the startscreen
    /// \param parent object to be passed to the base class constructor
    ///
    explicit StartScreen(QWidget *parent = nullptr);
    ~StartScreen();
    ///
    /// \brief setUpBox2D sets up the box2d simulation for the bouncing trophy
    ///
    void setUpBox2D();
    ///
    /// \brief paintEvent handles painting to the screen
    /// \param event the event passed to paint
    ///
    void paintEvent(QPaintEvent *event) override;

private:
    QPainter painter;
    QPixmap background;
    Ui::StartScreen *ui;

public slots:
    ///
    /// \brief This slot will receive the signal from the new lesson button
    /// that resides within the ui
    ///
    void newLessonButtonClicked();

    ///
    /// \brief This slot will receive the signal from the continue button
    /// that resides within the ui
    ///
    void continueButtonClicked();

    ///
    /// \brief This slot will receuve the signal from the free play button
    /// that resides within the ui
    ///
    void freePlayButtonClicked();

    ///
    /// \brief Updates the world based on a time increment
    ///
    void updateWorld();



signals:
    ///
    /// \brief This signal notifies any listeners that the newLessonButton has been clicked,
    /// and the page should be updated
    /// \param The index of the page to move to
    ///
    void sendNewLessonClicked(int index);

    ///
    /// \brief This signal notifies any listeners that the continueButton has been clicked,
    /// and the page should be updated
    ///
    void sendContinueClicked();

    ///
    /// \brief This signal will let the levelselect know that it should reset it's view,
    /// because a new game has been started
    ///
    void startingNewGame();

    ///
    /// \brief Gets a new height for the start screen label that bounces in a loop
    ///
    void newStartScreenLabelHeight(int y);

    ///
    /// \brief Sends a singal when the free play button is clicked to all connected slots
    ///
    void sendFreeplayClicked(int stackedWidgetIndex);

};

#endif // STARTSCREEN_H

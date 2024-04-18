/// Assignment 9: Educational App
/// CS3505
/// 4/12/24
/// Written by: Caleb Norman, Abdul Asim

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "minefield.h"
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

///
/// \brief The MainWindow class provides the view for the start of the program. From this window, other
/// widgets can be traded out for the current one using a stackedwidget
///
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Model &model, QWidget *parent = nullptr);
    ~MainWindow();

    void makeConnections (Minefield &mines);

private:
    Ui::MainWindow *ui;

public slots:
    ///
    /// \brief Updates the currently displayed page of our program
    /// \param The page index we will go to
    ///
    void updateScreenIndex(int index);

    ///
    /// \brief Listens for the currently selected level index, so that it can
    /// load the correct level when the user selects play
    /// \param Index to load, corresponds to the level number - 1
    ///
    void receiveLevelIndex(int levelIndex);

    ///
    /// \brief Listens to know if a previous game needs to be loaded in
    ///
    void loadPrevious();
};
#endif // MAINWINDOW_H

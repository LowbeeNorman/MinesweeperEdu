/// Assignment 9: Educational App
/// CS3505
/// 4/12/24
/// Written by: Caleb Norman

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    ///
    /// \brief Updates the currently displayed page of our program
    /// \param The page index we will go to
    ///
    void updateScreenIndex(int index);
    void receiveLevelIndex(int levelIndex);
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOWSECOND_H
#define MAINWINDOWSECOND_H

#include <QMainWindow>

namespace Ui {
class MainWindowSecond;
}

class MainWindowSecond : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowSecond(QWidget *parent = nullptr);
    ~MainWindowSecond();

private:
    Ui::MainWindowSecond *ui;
};

#endif // MAINWINDOWSECOND_H

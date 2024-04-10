#ifndef STACKEDWIDGETTEST_H
#define STACKEDWIDGETTEST_H

#include <QStackedWidget>

namespace Ui {
class StackedWidgetTest;
}

class StackedWidgetTest : public QStackedWidget
{
    Q_OBJECT

public:
    explicit StackedWidgetTest(QWidget *parent = nullptr);
    ~StackedWidgetTest();

private:
    Ui::StackedWidgetTest *ui;
};

#endif // STACKEDWIDGETTEST_H

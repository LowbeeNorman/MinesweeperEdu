#include "stackedwidgettest.h"
#include "ui_stackedwidgettest.h"

StackedWidgetTest::StackedWidgetTest(QWidget *parent)
    : QStackedWidget(parent)
    , ui(new Ui::StackedWidgetTest)
{
    ui->setupUi(this);
}

StackedWidgetTest::~StackedWidgetTest()
{
    delete ui;
}

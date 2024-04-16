QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    lesson.cpp \
    levelselect.cpp \
    boardview.cpp \
    main.cpp \
    mainwindow.cpp \
    minesweeperview.cpp \
    minesweeperview.cpp \
    startscreen.cpp \
    minefield.cpp \
    model.cpp \
    tipsview.cpp \

HEADERS += \
    lesson.h \
    levelselect.h \
    boardview.h \
    mainwindow.h \
    minesweeperview.h \
    minesweeperview.h \
    startscreen.h \
    minefield.h \
    model.h \
    tipsview.h \

FORMS += \
    lesson.ui \
    levelselect.ui \
    mainwindow.ui \
    minesweeperview.ui \
    startscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc \
    resources.qrc

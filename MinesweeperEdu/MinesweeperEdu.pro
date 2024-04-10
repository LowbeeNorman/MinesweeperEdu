QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    lesson.cpp \
    levelselect.cpp \
    startwindow.cpp \
    boardview.cpp \
    main.cpp \
    mainwindow.cpp \
    startscreen.cpp \
    model.cpp \
    tipsview.cpp

HEADERS += \
    lesson.h \
    levelselect.h \
    startwindow.h \
    boardview.h \
    mainwindow.h \
    startscreen.h
    model.h \
    tipsview.h

FORMS += \
    lesson.ui \
    levelselect.ui \
    mainwindow.ui \
    startscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

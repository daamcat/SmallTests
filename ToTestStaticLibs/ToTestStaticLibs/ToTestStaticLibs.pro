#-------------------------------------------------
#
# Project created by QtCreator 2021-10-14T20:02:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToTestStaticLibs
TEMPLATE = app



# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp 


# Error: No rule to make target 'MainWindow.ui', needed by 'ui_MainWindow.h'.  Stop.

# error: MainWindow.h: No such file or directory
INCLUDEPATH += $$PWD/../L1

# error: undefined reference to `MainWindow::~MainWindow()
# Adds the L1.lib to the linker
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../L1/release/ -lL1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../L1/debug/ -lL1

# Without adding linker to L2 libs, we get no compiler error, but the application will not run.
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../L2/release/ -lL2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../L2/debug/ -lL2

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../L3/el3/release/ -lel3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../L3/el3/debug/ -lel3


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

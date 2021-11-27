#-------------------------------------------------
#
# Project created by QtCreator 2021-10-14T20:02:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

############# DropboxQt #####################
QT       += core network
DROPBOX_DIR=C:/Projects/DropboxQt/dropboxQt-master-temp
SRC_DIR = $${DROPBOX_DIR}/src
INCLUDEPATH += $${SRC_DIR}
LIBS += -L$${DROPBOX_DIR}/prj/release/ -ldropboxQt
############# DropboxQt #####################


TARGET = L1
TEMPLATE = lib

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

INCLUDEPATH += $$PWD/../L2
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../L2/release/ -lL2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../L2/debug/ -lL2

INCLUDEPATH += $$PWD/../L3/el3
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../L3/el3/release/ -lel3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../L3/el3/debug/ -lel3

SOURCES += \
        MainWindow.cpp

HEADERS += \
        MainWindow.h

FORMS += \
        MainWindow.ui


QT       += core sql
QT       -= gui

CONFIG += c++11

TARGET = Inloquent
TEMPLATE = app

DEFINES += INLOQUENT_LIBRARY

unix {
    target.path = /usr/lib
    INSTALLS += target
}
include(Orm.pri)

SOURCES += main.cpp

QT       += core sql
QT       -= gui

CONFIG += c++11

TARGET = QEloquentOrm
TEMPLATE = app


unix {
    target.path = /usr/lib
    INSTALLS += target
}
include(Orm.pri)

SOURCES += main.cpp

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connItem.cpp \
    main.cpp \
    myscene.cpp \
    widget.cpp \
    workItem.cpp

HEADERS += \
    connItem.h \
    myscene.h \
    widget.h \
    workItem.h

FORMS += widget.ui

TARGET = SkudEmu

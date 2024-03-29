QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=
./items \

SOURCES += \
    agent.cpp \
    buffer.cpp \
    connectorDialog.cpp \
    main.cpp \
    myscene.cpp \
    utils.cpp \
    widget.cpp \
    ./items/workItem.cpp \
    ./items/connItem.cpp \
    ./items/connectorlineitem.cpp

HEADERS += \
    agent.h \
    buffer.h \
    connectorDialog.h \
    myscene.h \
    utils.h \
    widget.h \
    ./items/workItem.h \
    ./items/connItem.h \
    ./items/connectorlineitem.h

FORMS += widget.ui \
    connectorDialog.ui

TARGET = SkudEmu

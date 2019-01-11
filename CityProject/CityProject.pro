#-------------------------------------------------
#
# Project created by QtCreator 2018-10-04T15:12:09
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CityProject
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

LIBS += -Iglut -IGLU

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    building.cpp \
    squaredbuilding.cpp \
    circularbuilding.cpp \
    house.cpp \
    tower.cpp \
    baseglwidget.cpp \
    basegeometry.cpp \
    conebuilding.cpp \
    district.cpp \
    downtown.cpp \
    periphery.cpp \
    activityarea.cpp \
    gridsurfacedialog.cpp \
    factory.cpp\
    surface_ville.cpp \
    block.cpp

HEADERS += \
        mainwindow.h \
    building.h \
    squaredbuilding.h \
    circularbuilding.h \
    house.h \
    tower.h \
    baseglwidget.h \
    basegeometry.h \
    conebuilding.h \
    district.h \
    downtown.h \
    periphery.h \
    activityarea.h \
    gridsurfacedialog.h \
    factory.h\
    surface_ville.h \
    block.h

FORMS += \
        mainwindow.ui \
    gridsurfacedialog.ui

#-------------------------------------------------
#
# Project created by QtCreator 2018-12-01T23:08:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = exam_paper_editor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
    main.cpp \
    data/data.cpp \
    data/data_cmd.cpp \
    data/dependency_key.cpp \
    data/container.cpp

HEADERS += \
    data/data.h \
    data/data_cmd.h \
    data/data_type.h \
    data/dependency_key.h \
    data/container.h \
    data/container_type.h \
    data/type_enum_ref.h

#-------------------------------------------------
#
# Project created by QtCreator 2013-06-16T08:35:55
#
#-------------------------------------------------

QT -= core gui
QT += sql

TARGET = QCL
TEMPLATE = lib
CONFIG += staticlib

DEFINES += BOOST_CHRONO_DONT_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0

win32 {
  CONFIG(release, debug|release) {
    DESTDIR = "../Library/win32/release"
    OBJECTS_DIR = "../Library/win32/release/object/GCL"
  }
  else {
    DESTDIR = "../Library/win32/debug"
    OBJECTS_DIR = "../Library/win32/debug/object/GCL"
  }
}

unix {
  CONFIG(release,debug|release) {
    DESTDIR = "../Library/unix/release"
    OBJECTS_DIR = "../Library/unix/release/object/QCL"
  }
  else {
    DESTDIR = "../Library/unix/debug"
    OBJECTS_DIR = "../Library/unix/debug/object/QCL"
  }
}

QMAKE_CXXFLAGS += -std=c++17

INCLUDEPATH += \
  "../boost 1.62" \
  "../GCL" \
  "../SCL"

SOURCES += \
    source/database.cpp

HEADERS += \
    include/database.h


#-------------------------------------------------
#
# Project file for Qt Class Library (QCL)
#
#-------------------------------------------------

TARGET = QCL
TEMPLATE = lib
CONFIG += staticlib create_prl

QT += sql

QMAKE_CXXFLAGS += -std=c++20

DEFINES += BOOST_CHRONO_DONT_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0

DESTDIR = ""
OBJECTS_DIR = "objects"

INCLUDEPATH += \
  "../GCL" \
  "../MCL" \
  "../SCL"

SOURCES += \
    source/database.cpp \
    source/common.cpp \
    source/dialog.cpp \
    source/fileDownloadManager.cpp

HEADERS += \
    include/database.h \
    include/qt.h \
    QCL \
    include/common.h \
    include/dialog.h \
    include/fileDownloadManager.h


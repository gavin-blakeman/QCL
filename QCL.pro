#-------------------------------------------------
#
# Project file for Qt Class Library (QCL)
#
#-------------------------------------------------

TARGET = QCL
TEMPLATE = lib
CONFIG += staticlib create_prl

QT += sql

QMAKE_CXXFLAGS += -std=c++17

DEFINES += BOOST_CHRONO_DONT_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0

win32:CONFIG(release, debug|release) {
  DESTDIR = "../Library/win32/release"
  OBJECTS_DIR = "../Library/win32/release/object/SCL"
}
else:win32:CONFIG(debug, debug|release) {
  DESTDIR = "../Library/win32/debug"
  OBJECTS_DIR = "../Library/win32/debug/object/SCL"
}
else:unix:CONFIG(release, debug|release) {
  DESTDIR = "../Library/unix/release"
  OBJECTS_DIR = "../Library/unix/release/object/SCL"
}
else:unix:CONFIG(debug, debug|release) {
  DESTDIR = ""
  OBJECTS_DIR = "objects"
}

INCLUDEPATH += \
  "/home/gavin/Documents/Projects/software/Library/Boost/boost_1_71_0" \
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


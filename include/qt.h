//**********************************************************************************************************************************
//
// PROJECT:             QCL (Qt Class Library)
// FILE:			          Qt
// SUBSYSTEM:           Qt headers
// TARGET OS:	          WINDOWS, LINUX, UNIX, MAC
// NAMESPACE:						QCL
// AUTHOR:              Gavin Blakeman
// LICENSE:             GPLv2
//
//                      Copyright 2015-2018 Gavin Blakeman.
//                      This file is part of the Qt Class Library (QCL)
//
//                      QCL is free software: you can redistribute it and/or modify it under the terms of the GNU General
//                      Public License as published by the Free Software Foundation, either version 2 of the License, or (at your
//                      option) any later version.
//
//                      QCL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
//                      the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
//                      License for more details.
//
//                      You should have received a copy of the GNU General Public License along with QCL.  If not,
//                      see <http://www.gnu.org/licenses/>.
//
// OVERVIEW:	          Header files for Qt
//
// CLASSES:		          None
//
// HISTORY:             2015-09-22 GGB - astroManager 2015.09 release
//
//**********************************************************************************************************************************

#ifndef QT_H_
#define QT_H_

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4104)
#pragma warning(disable: 4127)
#pragma warning(disable: 4244)
#pragma warning(disable: 4251)
#pragma warning(disable: 4275)
#pragma warning(disable: 4505)
#pragma warning(disable: 4512)
#pragma warning(disable: 4800)
#endif

#include <Qt>

#if QT_VERSION >= 0x050000
#ifdef QT_GUI_LIB
  #include <QtGui>
#endif
#include <QtPlugin>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#ifdef QT_NETWORK_LIB
  #include <QtNetwork>
#endif
#ifdef QT_SQL_LIB
  #include <QtSql>
  #include <QSqlQuery>
#endif
#include <QtUiTools/QUiLoader>
#else
#include <Qt>
#include <QtCore/Qt>
#include <QtGui/QtGui>
#include <QtNetwork/QtNetwork>
#include <QNetworkAccessManager>
#include <QtSql>
#include <QtUiTools/QtUiTools>
#endif

#include <GCL>


#ifdef _MSC_VER
#pragma warning(pop)
#endif

  /// @def ASSOCIATE_CONTROL(WIDGET, CONTROL, TYPE)
  /// This macro is used for associating controls in dialogs or similar with a variable.
  /// @param[in] WIDGET - The widget that contains the code.
  /// @param[in] CONTROL - The control and variable name. The control name is always assumed to be the same as the variable name.
  /// @param[in] TYPE - The Qt type of the control (QCheckBox etc)
  /// @version 2015-09-22/GGB - Macro created.

#define ASSOCIATE_CONTROL(POINTERNAME, WIDGET, CONTROLNAME, TYPE) \
  POINTERNAME = WIDGET->findChild<TYPE *>(CONTROLNAME); \
  RUNTIME_ASSERT(astroManager, POINTERNAME, "Control "#CONTROLNAME" not found." );

#define ASSOCIATE_LABEL(POINTERNAME, WIDGET, CONTROLNAME) ASSOCIATE_CONTROL(POINTERNAME, WIDGET, CONTROLNAME, QLabel)
#define ASSOCIATE_RADIOBUTTON(POINTERNAME, WIDGET, CONTROLNAME) ASSOCIATE_CONTROL(POINTERNAME, WIDGET, CONTROLNAME, QRadioButton)
#define ASSOCIATE_PUSHBUTTON(POINTERNAME, WIDGET, CONTROLNAME) ASSOCIATE_CONTROL(POINTERNAME, WIDGET, CONTROLNAME, QPushButton)
#define ASSOCIATE_SPINBOX(POINTERNAME, WIDGET, CONTROLNAME) ASSOCIATE_CONTROL(POINTERNAME, WIDGET, CONTROLNAME, QSpinBox)
#define ASSOCIATE_TABLEVIEW(POINTERNAME, WIDGET, CONTROLNAME) ASSOCIATE_CONTROL(POINTERNAME, WIDGET, CONTROLNAME, QTableView)

#endif // QT_H_H

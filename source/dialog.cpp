//**********************************************************************************************************************************
//
// PROJECT:             QCL
// FILE:			          Qt
// SUBSYSTEM:           Dialog extension
// TARGET OS:	          WINDOWS, LINUX, UNIX, MAC
// NAMESPACE:						AstroManager::photometry
// AUTHOR:              Gavin Blakeman
// LICENSE:             GPLv2
//
//                      Copyright 2020 Gavin Blakeman.
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
// OVERVIEW:
//
// CLASSES:		          CDialog
//
// HISTORY:             2020-09-19 GGB - File created. (Code moved from dialogs in astroManager.)
//
//**********************************************************************************************************************************
#include "include/dialog.h"

  // Miscellaneous library header files

#include "boost/locale.hpp"

namespace QCL
{
  /// @brief        Constructor taking a single argument. The calling function/derived dialog must load the dialog template.
  /// @param[in]    parent: The parent (owner) of this instance.
  /// @version      2013-05-10/GGB - Function created.

  CDialog::CDialog(QObject *parent) : QObject(parent)
  {
  }

  /// @brief        Constructor for the CDialog class.
  /// @param[in]    szDialog: String value representing the dialog resource name.
  /// @param[in]    parent: The parent object
  /// @throws       CRuntimeError
  /// @version      2014-02-10/GGB - Added check and exception after opening the file and loading the dialog.
  /// @version      2010-06-21/GGB - Function created.

  CDialog::CDialog(QString szDialog, QObject *parent) : QObject(parent)
  {
    QUiLoader loader;

    QFile file(szDialog);

    if (!QFile::exists(szDialog))
    {
      RUNTIME_ERROR(boost::locale::translate("Resource does not exist: ").str() + szDialog.toStdString());
    }

    if (!file.open(QFile::ReadOnly))
    {
      RUNTIME_ERROR(boost::locale::translate("Could not open the resource: ").str() + szDialog.toStdString());
    };

    dlg = static_cast<QDialog *>(loader.load(&file));

    RUNTIME_ASSERT(dlg != nullptr, boost::locale::translate("The dialog template could not be loaded."));

    file.close();
  }

  /// @brief        Default destructor for the class.
  /// @version      2010-06-21/GGB - Function created.

  CDialog::~CDialog()
  {
  }

  /// @brief        Exec function
  /// @version      2010-06-21/GGB - Function created.

  int CDialog::exec()
  {
    return ( dlg->exec() );
  }
}

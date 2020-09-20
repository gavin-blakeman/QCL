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

#ifndef QCL_DIALOG_H
#define QCL_DIALOG_H

#include "qt.h"

namespace QCL
{
  class CDialog : public QObject
  {
    Q_OBJECT

  private:
  protected:
    QDialog *dlg;

    template<typename T>
    T findChild(const QString &childName)
    {
      T returnValue = dlg->findChild<T>(childName);
      RUNTIME_ASSERT(returnValue != nullptr, "Control " + childName.toStdString() + " not found." );

      return returnValue;
    }

  public:
    CDialog(QObject * = nullptr);
    CDialog(QString, QObject * = nullptr);
    ~CDialog();

    virtual int exec();

//  public slots:
//    virtual void accepted() {}
//    virtual void rejected() { std::cout << "CDialog::rejected called" << std::endl; }
  };
}

#endif // QCL_DIALOG_H

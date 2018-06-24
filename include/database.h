//*********************************************************************************************************************************
//
// PROJECT:							Qt Class Library (GCL)
// FILE:								database
// SUBSYSTEM:						Generic Database Class for Qt
// TARGET OS:	          WINDOWS, LINUX, UNIX, MAC
// AUTHOR:              Gavin BLakeman (GGB)
// LICENSE:             GPLv2
//
//                      Copyright 2015, 2018 Gavin Blakeman.
//                      This file is part of the Qt Class Library (QCL)
//
//                      QCL is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
//                      License as published by the Free Software Foundation, either version 2 of the License, or (at your option)
//                      any later version.
//
//                      QCL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
//                      warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
//                      more details.
//
//                      You should have received a copy of the GNU General Public License along with QCL.  If not,
//                      see <http://www.gnu.org/licenses/>.
//
// CLASSES INCLUDED:    CDatabase
//
// HIERARCHY:           CDatabase
//
// HISTORY:             2015-03-29 GGB - File Created
//
//*********************************************************************************************************************************

#ifndef QCL_DATABASE_H
#define QCL_DATABASE_H

#include "qt.h"

  // Standard header files

#include <list>
#include <map>
#include <string>

// General class library

#include <GCL>

namespace QCL
{
  QString const QDRV_MYSQL("QMYSQL");
  QString const QDRV_ORACLE("QOCI");
  QString const QDRV_ODBC("QODBC");
  QString const QDRV_SQLITE("QSQLITE");

  class CDatabase
  {
  public:
    enum
    {
      SQLDB_MYSQL,
      SQLDB_QOCI,
      SQLDB_SQLITE,
      SQLDB_PSQL,
      SQLDB_ODBC,
      SQLDB_TDS,
    };
  private:
    CDatabase() = delete;                         // Not allowed as must initialise connection name.

  protected:
    QString szConnectionName;                     ///< Name of the connection.
    QSqlDatabase *dBase;                          ///< Pointer to the database driver.
    GCL::sqlwriter::CSQLWriter sqlWriter;         ///< The mapped SQL writer that the instances can customise and use.

    virtual bool createConnectionODBC(QString const &, QString const &);
    virtual bool createConnectionSQLite(QString const &, QString const &);

  public:
    class SDatabaseDriver
    {
    public:
      QString driverText;
      QString driverName;

      SDatabaseDriver(QString const &st1, QString const &st2) : driverText(st1), driverName(st2) {}
      SDatabaseDriver() {}
    };
    typedef std::map<int, SDatabaseDriver> TDatabaseDriverStorage;

    CDatabase(QString const &connectionName);

    virtual bool createConnection(QString const &, QString const &, std::uint16_t, QString const &, QString const &, QString const &);

    QString getDriverName(int driverID) const;
    bool isDriverAvailable(int driverID) const;

    static TDatabaseDriverStorage databaseDrivers;
    static void initialiseDrivers();
  };

  CDatabase extern database;

} // namespace QCL

#endif // DATABASE_H

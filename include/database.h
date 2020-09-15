//*********************************************************************************************************************************
//
// PROJECT:             Qt Class Library
// FILE:			          database
// SUBSYSTEM:           database Support Functions
// TARGET OS:	          WINDOWS, LINUX, UNIX, MAC
// LIBRARY DEPENDANCE:	Qt
// NAMESPACE:						QCL
// AUTHOR:              Gavin BLakeman (GGB)
// LICENSE:             GPLv2
//
//                      Copyright 2012-2020 Gavin Blakeman.
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
// OVERVIEW:            Database support functions.
//
// CLASSES INCLUDED:    CDatabase
//
// HIERARCHY:           CDatabase
//
// HISTORY:             2018-09-02 GGB - astroManager database class merged and migrated to QCL database class.
//                      2018-04-13 GGB - Project Name changed to astroManager.
//                      2015-09-22 GGB - astroManager 2015.09 release
//                      2013-05-15 GGB - Split CDatabaseWeather into own file.
//                      2013-03-22 GGB - astroManager 2013.03 release.
//                      2013-02-24 GGB - Split CATID into it's own file
//                      2013-01-20 GGB - astroManager 0000.00 release.
//                      2012-01-04 GGB - Classes developed for astroManager
//
//*********************************************************************************************************************************

#ifndef QCL_DATABASE_H
#define QCL_DATABASE_H

  // Standard C++ library header files

#include <list>
#include <map>
#include <memory>
#include <string>

  // Miscellaneous header files.

#include "qt.h"
#include <GCL>
#include <QCL>

#ifdef _MSC_VER
# pragma warning( disable : 4290 )  /* Disable the warning about C++ exception specifications. */
#endif

namespace QCL
{
  const int ROLE_FILTERID  = Qt::UserRole + 0;

  QString const QDRV_MYSQL("QMYSQL");
  QString const QDRV_ORACLE("QOCI");
  QString const QDRV_ODBC("QODBC");
  QString const QDRV_SQLITE("QSQLITE");

  class CDatabase : public QObject
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
  protected:
    QString szConnectionName;                     ///< Name of the connection.
    QSqlDatabase *dBase;                          ///< Pointer to the database driver.
    std::unique_ptr<QSqlQuery> sqlQuery;
    GCL::sqlWriter sqlWriter;         ///< The mapped SQL writer that the instances can customise and use.

    virtual bool createConnection(QString const &, QString const &, std::uint16_t, QString const &, QString const &, QString const &);
    virtual bool createConnectionODBC(QString const &, QString const &);
    virtual bool createConnectionSQLite(QString const &, QString const &);

    virtual bool ODBC() = 0;
    virtual bool Oracle() = 0;
    virtual bool MySQL() = 0;
    virtual bool SQLite() = 0;
    virtual bool PostgreSQL() = 0;

    void processErrorInformation() const;

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

    static TDatabaseDriverStorage databaseDrivers;

    static void initialiseDrivers();
    static QString getDriverName(int);
    static bool isDriverAvailable(int);

    CDatabase(QString const &);
    inline QSqlDatabase &database() { return *dBase;}

    virtual bool connectToDatabase(QString const &);

    void readMapFile(boost::filesystem::path const &mfn);
  };

} // namespace QCL

#endif  // QCL_DATABASE_H

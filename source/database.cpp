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
//                      Copyright 2012-2022 Gavin Blakeman.
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

#include "include/database.h"

  // QCL Library header files

#include "include/qt.h"

  // Miscellaneous library header files.

#include <boost/algorithm/string.hpp>
#include "boost/locale.hpp"

namespace QCL
{

  CDatabase::TDatabaseDriverStorage CDatabase::databaseDrivers;

  //*****************************************************************************************************************************
  //
  // Class CDatabase
  //
  //*****************************************************************************************************************************

  /// @brief      Constructor for the database class.
  /// @param[in]  connectionName: The name of the connection associated with the database.
  /// @throws     None
  /// @version    2017-06-20/GGB - Function created.

  CDatabase::CDatabase(QString const &connectionName) : szConnectionName(connectionName), dBase(nullptr)
  {
  }

  /// @brief      Creates a connection to the database by calling the relevant functions.
  /// @param[in]  szDatabase: Database driver string to use.
  /// @returns    true - Connection created
  /// @returns    false - The driver type is not supported.
  /// @throws     None.
  /// @version    2017-07-01/GGB - Function created.

  bool CDatabase::connectToDatabase(QString const &szDatabase)
  {
    bool returnValue = false;

    if (szDatabase == "Oracle")
    {
      if (isDriverAvailable(SQLDB_QOCI))
      {
        Oracle();
        returnValue = true;
      }
      else
      {
        WARNINGMESSAGE(boost::locale::translate("The database driver QOCI is not available or has not been loaded."));
      }
    }
    else if (szDatabase == "ODBC")
    {
      if (isDriverAvailable(SQLDB_ODBC))
      {
        returnValue = ODBC();
      }
      else
      {
        WARNINGMESSAGE(boost::locale::translate("The database driver QODBC is not available or has not been loaded."));
      };
    }
    else if (szDatabase == "MySQL")
    {
      if (isDriverAvailable(SQLDB_MYSQL))
      {
        returnValue = MySQL();
      }
      else
      {
        WARNINGMESSAGE(boost::locale::translate("The database driver QMYSQL is not available or has not been loaded."));
      };
    }
    else if (szDatabase == "SQLite")
    {
      if (isDriverAvailable(SQLDB_SQLITE))
      {
        returnValue =  SQLite();
      }
      else
      {
        WARNINGMESSAGE(boost::locale::translate("The database driver QSQLITE is not available or has not been loaded."));
      }
    }
    else if (szDatabase == "PostgreSQL")
    {
      if (isDriverAvailable(SQLDB_PSQL))
      {
        returnValue = PostgreSQL();
      }
      else
      {
        WARNINGMESSAGE(boost::locale::translate("The database driver QPSQL is not available or has not been loaded."));
      }
    }
    else
    {
      WARNINGMESSAGE("The database driver " + szDatabase.toStdString() + " is unknown.");
    }

    return returnValue;
  }

  /// @brief        Connects to the specified database.
  /// @param[in]    driverName: The name of the driver to use to connect with.
  /// @param[in]    hostName: The name or IP address of the host to connect to.
  /// @param[in]    portNumber: The number of the port to connect to on the host.
  /// @param[in]    databaseName: The name of the database to connect to.
  /// @param[in]    userName: The name of the user to connect to.
  /// @param[in]    password: The password to use when connecting.
  /// @returns      true - Connection created.
  /// @returns      false - Unable to create connection.
  /// @pre          1. szConnectionName must have been set before this function is called.
  /// @throws
  /// @version      2017-06-19/GGB - Function created.

  bool CDatabase::createConnection(QString const &driverName, QString const &hostName, std::uint16_t portNumber,
                                   QString const &databaseName,
                                   QString const &userName, QString const &password)
  {
    bool returnValue = false;

    // Create the database instance and setup the connection strings.

    dBase = new QSqlDatabase();
    (*dBase) = QSqlDatabase::addDatabase(driverName, szConnectionName);
    dBase->setHostName(hostName);
    dBase->setDatabaseName(databaseName);
    dBase->setUserName(userName);
    dBase->setPassword(password);
    dBase->setPort(portNumber);

    // Attempt to open the database and if there is an error, throw an exception.

    if ( !dBase->open() )
    {
      QSqlError error = dBase->lastError();     // 1045 - Access denied
                                                // 2005 - Unable to connect

      ERRORMESSAGE(boost::locale::translate("Error while connecting to Database: ").str() + hostName.toStdString() + "." + databaseName.toStdString());
      ERRORMESSAGE(boost::locale::translate("Error returned by Driver: ").str() + error.nativeErrorCode().toStdString());
      ERRORMESSAGE(boost::locale::translate("Text returned by driver: ").str() + error.driverText().toStdString());
      ERRORMESSAGE(boost::locale::translate("Text returned by database: ").str() + error.databaseText().toStdString());
    }
    else
    {
      INFOMESSAGE(boost::locale::translate("Connected to MySQL Database: ").str() + hostName.toStdString() + "." + databaseName.toStdString());
      returnValue = true;
    }

    return returnValue;
  }

  /// @brief        Connects to a specified ODBC database driver
  /// @param[in]    driverName: The driver to use for the connection.
  /// @param[in]    databaseName: The name of the database to open.
  /// @returns      true - Connection created.
  /// @returns      false - Connection not created.
  /// @throws       None.
  /// @version      2017-07-01/GGB - Return type changed from void to bool.
  /// @pre          1. szConnectionName must have been set before this function is called
  /// @version      2017-06-20/GGB - Function created.

  bool CDatabase::createConnectionODBC(QString const &driverName, QString const &databaseName)
  {
    bool returnValue = false;

    dBase = new QSqlDatabase();
    (*dBase) = QSqlDatabase::addDatabase(driverName, szConnectionName);
    dBase->setDatabaseName(databaseName);

    if (!dBase->open())
    {
      QSqlError error = dBase->lastError();

      ERRORMESSAGE(boost::locale::translate("Error while connecting to ODBC Database: ").str() + databaseName.toStdString());
      ERRORMESSAGE(boost::locale::translate("Error returned by ODBC Driver: ").str() + error.nativeErrorCode().toStdString());
      ERRORMESSAGE(boost::locale::translate("Text returned by driver: ").str() + error.driverText().toStdString());
      ERRORMESSAGE(boost::locale::translate("Text returned by database: ").str() + error.databaseText().toStdString());
    }
    else
    {
      INFOMESSAGE(boost::locale::translate("Connected to ODBC Database: ").str() + databaseName.toStdString());
      returnValue = true;
    };

    return returnValue;
  }

  /// @brief        Connect to a specified SQLite database.
  /// @param[in]    driverName: The name of the driver to use for the connection.
  /// @param[in]    databaseName: The name of the database to connect to.
  /// @returns      true - Connection created.
  /// @returns      false - Connection not created.
  /// @throws       None.
  /// @version      2017-07-01/GGB - Return type changed from void to bool.
  /// @pre          1. szConnectionName must have been set before this function is called
  /// @version      2017-06-20/GGB - Function created.

  bool CDatabase::createConnectionSQLite(QString const &driverName, QString const &databaseName)
  {
    bool returnValue = false;

    dBase = new QSqlDatabase();
    (*dBase) = QSqlDatabase::addDatabase(driverName, szConnectionName);
    dBase->setDatabaseName(databaseName);

    if ( !dBase->open() )
    {
      QSqlError error = dBase->lastError();

      ERRORMESSAGE(boost::locale::translate("Error while connecting to SQLite Database: ").str() + databaseName.toStdString());
      ERRORMESSAGE(boost::locale::translate("Error returned by SQLLite Driver: ").str() + error.nativeErrorCode().toStdString());
      ERRORMESSAGE(boost::locale::translate("Text returned by driver: ").str() + error.driverText().toStdString());
      ERRORMESSAGE(boost::locale::translate("Text returned by database: ").str() + error.databaseText().toStdString());
    }
    else
    {
      INFOMESSAGE(boost::locale::translate("Connected to SQLite Database: ").str() + databaseName.toStdString());
      returnValue = true;
    };

    return returnValue;
  }

  /// @brief        Returns the requested driver name if it exists.
  /// @returns      The specified driver name.
  /// @version      2017-07-01/GGB - Function created.

  QString CDatabase::getDriverName(int driverID)
  {
    return databaseDrivers[driverID].driverName;
  }

  /// @brief        Determines if a driver is available and been loaded.
  /// @param[in]    driverID: The ID value of the driver to check.
  /// @returns      true - SQL Driver is available
  /// @returns      false - SQL Driver is not available.
  /// @throws       None.
  /// @version      2017-07-01/GGB - Function created.

  bool CDatabase::isDriverAvailable(int driverID)
  {
    return ( databaseDrivers.find(driverID) != databaseDrivers.end() );
  }

  /// @brief        Initialises the list of drivers available for use.
  /// @throws       None.
  /// @version      2017-07-01/GGB - Function created.

  void CDatabase::initialiseDrivers()
  {
    // Only load the relevant database drivers.

    QStringList driverList = QSqlDatabase::drivers();

    if (driverList.contains("QMYSQL"))
    {
      databaseDrivers.insert(std::pair<int, SDatabaseDriver>(SQLDB_MYSQL, SDatabaseDriver("MySQL", "QMYSQL")));
      INFOMESSAGE(boost::locale::translate("Enabling MySQL DBMS Support"));

    };
    if (driverList.contains("QOCI"))
    {
      databaseDrivers.insert(std::pair<int, SDatabaseDriver>(SQLDB_QOCI, SDatabaseDriver("Oracle", "QOCI")));
      INFOMESSAGE(boost::locale::translate("Enabling Oracle DBMS Support"));
    };
    if (driverList.contains("QSQLITE"))
    {
      databaseDrivers.insert(std::pair<int, SDatabaseDriver>(SQLDB_SQLITE, SDatabaseDriver("SQLite", "QSQLITE")));
      INFOMESSAGE(boost::locale::translate("Enabling SQLite DBMS Support"));
    };
    if (driverList.contains("QPSQL"))
    {
      databaseDrivers.insert(std::pair<int, SDatabaseDriver>(SQLDB_PSQL, SDatabaseDriver("PostgreSQL", "QPSQL")));
      INFOMESSAGE(boost::locale::translate("Enabling Postgre DBMS Support"));
    };
    if (driverList.contains("QODBC"))
    {
      databaseDrivers.insert(std::pair<int, SDatabaseDriver>(SQLDB_ODBC, SDatabaseDriver("ODBC", "QODBC")));
      INFOMESSAGE(boost::locale::translate("Enabling ODBC DBMS Support"));
    };
  }

  /// @brief    Processes and displays the error information.
  /// @throws   None.
  /// @version  2020-09-09/GGB - Added parameter sqlQuery.
  /// @version  2017-08-13/GGB - FUnction created.

  void CDatabase::processErrorInformation(QSqlQuery const &sqlQuery) const
  {
    QSqlError error = sqlQuery.lastError();

    ERRORMESSAGE(boost::locale::translate("Error while executing query: ").str() + sqlWriter.string());
    ERRORMESSAGE(boost::locale::translate("Error returned by Driver: ").str() + error.nativeErrorCode().toStdString());
    ERRORMESSAGE(boost::locale::translate("Text returned by driver: ").str() + error.driverText().toStdString());
    ERRORMESSAGE(boost::locale::translate("Text returned by database: ").str() + error.databaseText().toStdString());
  }

  /// @brief      Overloaded readMapFile().
  /// @param[in]  mfn: Map file name.
  /// @throws
  /// @version    2018-09-28/GGB - Moved into CDatabase.
  /// @version    2013-01-26/GGB - Function created.

  void CDatabase::readMapFile(std::filesystem::path const &mfn)
  {
    sqlWriter.readMapFile(mfn);
  }

}	// namespace QCL

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

#include "../include/database.h"

#include "../include/QCLError.h"

namespace QCL
{
  CDatabase::TDatabaseDriverStorage CDatabase::databaseDrivers;

  //*****************************************************************************************************************************
  //
  // Class CDatabase
  //
  //*****************************************************************************************************************************

  /// @brief Constructor for the database class.
  /// @param[in] connectionName - The name of the connection associated with the database.
  /// @throws None
  /// @version 2017-06-20/GGB - Function created.

  CDatabase::CDatabase(QString const &connectionName) : szConnectionName(connectionName), dBase(nullptr)
  {
  }

  /// @brief Connects to the specified database.
  /// @param[in] driverName: The name of the driver to use to connect with.
  /// @param[in] hostName: The name or IP address of the host to connect to.
  /// @param[in] portNumber: The number of the port to connect to on the host.
  /// @param[in] databaseName: The name of the database to connect to.
  /// @param[in] userName: The name of the user to connect to.
  /// @param[in] password: The password to use when connecting.
  /// @returns true - Connection created.
  /// @returns false - Unable to create connection.
  /// @pre 1. szConnectionName must have been set before this function is called. (Should be set in constructor.)
  /// @throws
  /// @version 2017-06-19/GGB - Function created.

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

      ERRORMESSAGE("Error while connecting to Database: " + hostName.toStdString() + "." + databaseName.toStdString());
      ERRORMESSAGE("Error returned by Driver: " + error.nativeErrorCode().toStdString());
      ERRORMESSAGE("Text returned by driver: " + error.driverText().toStdString());
      ERRORMESSAGE("Text returned by database: " + error.databaseText().toStdString());
    }
    else
    {
      INFOMESSAGE("Connected to MySQL Database: " + hostName.toStdString() + "." + databaseName.toStdString());
      returnValue = true;
    }

    return returnValue;
  }

  /// @brief Connects to a specified ODBC database driver
  /// @param[in] driverName - The driver to use for the connection.
  /// @param[in] databaseName - The name of the database to open.
  /// @returns true - Connection created.
  /// @returns false - Connection not created.
  /// @throws None.
  /// @version 2017-07-01/GGB - Return type changed from void to bool.
  /// @pre 1. szConnectionName must have been set before this function is called
  /// @version 2017-06-20/GGB - Function created.

  bool CDatabase::createConnectionODBC(QString const &driverName, QString const &databaseName)
  {
    bool returnValue = false;

    dBase = new QSqlDatabase();
    (*dBase) = QSqlDatabase::addDatabase(driverName, szConnectionName);
    dBase->setDatabaseName(databaseName);

    if (!dBase->open())
    {
      QSqlError error = dBase->lastError();

      ERRORMESSAGE("Error while connecting to ODBC Database: " + databaseName.toStdString());
      ERRORMESSAGE("Error returned by ODBC Driver: " + error.nativeErrorCode().toStdString());
      ERRORMESSAGE("Text returned by driver: " + error.driverText().toStdString());
      ERRORMESSAGE("Text returned by database: " + error.databaseText().toStdString());
    }
    else
    {
      INFOMESSAGE("Connected to ODBC Database: " + databaseName.toStdString());
      returnValue = true;
    };

    return returnValue;
  }

  /// @brief Connect to a specified SQLite database.
  /// @param[in] driverName - The name of the driver to use for the connection.
  /// @param[in] databaseName - The name of the database to connect to.
  /// @returns true - Connection created.
  /// @returns false - Connection not created.
  /// @throws None.
  /// @version 2017-07-01/GGB - Return type changed from void to bool.
  /// @pre 1. szConnectionName must have been set before this function is called
  /// @version 2017-06=-20/GGB - Function created.

  bool CDatabase::createConnectionSQLite(QString const &driverName, QString const &databaseName)
  {
    bool returnValue = false;

    dBase = new QSqlDatabase();
    (*dBase) = QSqlDatabase::addDatabase(driverName, szConnectionName);
    dBase->setDatabaseName(databaseName);

    if ( !dBase->open() )
    {
      QSqlError error = dBase->lastError();

      ERRORMESSAGE("Error while connecting to SQLite Database: " + databaseName.toStdString());
      ERRORMESSAGE("Error returned by SQLLite Driver: " + error.nativeErrorCode().toStdString());
      ERRORMESSAGE("Text returned by driver: " + error.driverText().toStdString());
      ERRORMESSAGE("Text returned by database: " + error.databaseText().toStdString());
    }
    else
    {
      INFOMESSAGE("Connected to SQLite Database: " + databaseName.toStdString());
      returnValue = true;
    };

    return returnValue;
  }

  /// @brief Returns the requested driver name if it exists.
  /// @returns The specified driver name.
  /// @throws None.
  /// @version 2017-07-01/GGB - Function created.

  QString CDatabase::getDriverName(int driverID) const
  {
    return databaseDrivers[driverID].driverName;
  }

  /// @brief Determines if a driver is available and been loaded.
  /// @param[in] driverID - The ID value of the driver to check.
  /// @returns true - SQL Driver is available
  /// @returns false - SQL Driver is not available.
  /// @throws None.
  /// @version 2017-07-01/GGB - Function created.

  bool CDatabase::isDriverAvailable(int driverID) const
  {
    return ( databaseDrivers.find(driverID) != databaseDrivers.end() );
  }

  /// @brief initialises the list of drivers available for use.
  /// @throws None.
  /// @version 2017-07-01/GGB - Function created.

  void CDatabase::initialiseDrivers()
  {
      // Only load the relevant database drivers.

    QStringList driverList = QSqlDatabase::drivers();

    if (driverList.contains("QMYSQL"))
    {
      databaseDrivers.insert(std::pair<int, SDatabaseDriver>(SQLDB_MYSQL, SDatabaseDriver("MySQL", "QMYSQL")));
      INFOMESSAGE("Enabling MySQL DBMS Support");

    };
    if (driverList.contains("QOCI"))
    {
      databaseDrivers.insert(std::pair<int, SDatabaseDriver>(SQLDB_QOCI, SDatabaseDriver("Oracle", "QOCI")));
      INFOMESSAGE("Enabling Oracle DBMS Support");
    };
    if (driverList.contains("QSQLITE"))
    {
      databaseDrivers.insert(std::pair<int, SDatabaseDriver>(SQLDB_SQLITE, SDatabaseDriver("SQLite", "QSQLITE")));
      INFOMESSAGE("Enabling SQLite DBMS Support");
    };
    if (driverList.contains("QPSQL"))
    {
      databaseDrivers.insert(std::pair<int, SDatabaseDriver>(SQLDB_PSQL, SDatabaseDriver("PostgreSQL", "QPSQL")));
      INFOMESSAGE("Enabling Postgre DBMS Support");
    };
    if (driverList.contains("QODBC"))
    {
      databaseDrivers.insert(std::pair<int, SDatabaseDriver>(SQLDB_ODBC, SDatabaseDriver("ODBC", "QODBC")));
      INFOMESSAGE("Enabling ODBC DBMS Support");
    };
  }


} // namespace QCL

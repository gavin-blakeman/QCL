//**********************************************************************************************************************************
//
// PROJECT:             QCL
// FILE:			          fileDownloadManager
// SUBSYSTEM:           Download files from a URL
// TARGET OS:	          WINDOWS, LINUX, UNIX, MAC
// NAMESPACE:						QCL
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
// CLASSES:
//
// HISTORY:             2020-10-03 GGB - File created.
//
//**********************************************************************************************************************************

#ifndef FILEDOWNLOADMANAGER_H
#define FILEDOWNLOADMANAGER_H

  // C++ standard library header files

#include <cstdint>
#include <functional>

  // Miscellaneous library header files

#include "boost/filesystem.hpp"

  // QCL library header files

#include "include/qt.h"

namespace QCL
{
  class CFileDownloadManager: public QObject
  {
    Q_OBJECT

  public:
    using callback_fn = std::function<void(std::uint32_t, QNetworkReply *)>;

    struct SDownloadData
    {
      std::uint32_t uniqueID;
      boost::filesystem::path filename;                                     ///< Filename to save as
      callback_fn successCallback;
      callback_fn errorCallback;
    };

  private:
    QNetworkAccessManager networkManager;
    QMap<QNetworkReply *, SDownloadData> currentDownloads;
    static std::uint32_t downloadUID;                   ///< Unique ID supplied to the calling routine to seperate download calls.

  protected:
    bool saveToDisk(QString const &filename, QIODevice *data);

  public:
    CFileDownloadManager();

    std::uint32_t startDownload(QUrl const &, boost::filesystem::path const &, callback_fn, callback_fn);

  public slots:
    void finished(QNetworkReply *reply);
    void sslErrors(const QList<QSslError> &errors);
  };


} // namespace QCL

#endif // FILEDOWNLOADMANAGER_H

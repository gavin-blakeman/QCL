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
//                      Copyright 2018 Gavin Blakeman.
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
// OVERVIEW:						Common definitions that can be used by multiple files
//
// CLASSES INCLUDED:		None
//
// CLASS HIERARCHY:     None.
//
// FUNCTIONS INCLUDED:  std::string getVersionString()
//
// HISTORY:             2018-09-22 GGB - File created.
//
//*********************************************************************************************************************************

#include "../include/common.h"

  // Standard C++ library header files

#include <iomanip>
#include <sstream>
#include <string>

  // Miscellaneous library header files

#include <boost/algorithm/string.hpp>

namespace SCL
{

  unsigned int const QCL_MAJORVERSION = 2018;           ///< The Major version number (yyyy)
  unsigned int const QCL_MINORVERSION = 9;              ///< The Minor version number (mm)
  unsigned int const QCL_BUILDNUMBER  = 0x005F;         ///< The build numnber - incremented on each build.

  /// @brief Returns the library version and build number that was used for editing the library.
  /// @returns A string with the application name, version, build.
  /// @throws Nothing.
  /// @version 2018-09-22/GGB - Function created.

  std::string getVersionString()
  {
    std::stringstream s;

    s << QCL_MAJORVERSION << "." << std::setfill('0') << std::setw(2) << QCL_MINORVERSION << std::setw(4) << std::hex << QCL_BUILDNUMBER << std::endl;

    std::string returnValue = s.str();
    boost::algorithm::to_upper(returnValue);

    return returnValue;
  }
}

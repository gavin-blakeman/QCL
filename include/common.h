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
// HISTORY:             2015-09-22 GGB - astroManager 2015.09 release
//                      2015-06-29 GGB - File Created
//
//*********************************************************************************************************************************

#ifndef QCL_COMMON_H
#define QCL_COMMON_H

  // Standard libraries

#include <cstdint>
#include <string>

namespace QCL
{
  std::string const SCL_LIBNAME       = "QCL";

  std::string getVersionString();
}

#endif // QCL_COMMON_H

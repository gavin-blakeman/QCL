//*********************************************************************************************************************************
//
// PROJECT:							Qt Class Library (QCL)
// FILE:								QCLError
// SUBSYSTEM:						Qt Class Library Exception subsystem
// LANGUAGE:						C++
// TARGET OS:						All (Standard C++)
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:						GCL
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2015 Gavin Blakeman.
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
// OVERVIEW:            This file implements exceptions that are used for error reporting by the GCL library.
//
// CLASSES INCLUDED:    CGCLError
//
// HISTORY:             2015-05-30 GGB - File created.
//
//*********************************************************************************************************************************

#include "../Include/QCLError.h"

#include <cstdlib>

#include "boost/lexical_cast.hpp"

#include <GCL>

namespace QCL
{
  std::map<size_t, std::string> CQCLError::errorMessages;

  struct SErrorCodes
  {
    size_t errorCode_;
    std::string errorMessage;
  };

  SErrorCodes errorArray[] = 
  {  
    {0x0001, std::string("MAPPED SQL WRITER: Invalid Map file name.")},
    {0x0002, std::string("MAPPED SQL WRITER: Syntax Error.")},
    {0x0003, std::string("MAPPED SQL WRITER: Invalid Command.")},
    {0x0004, std::string("MAPPED SQL WRITER: Invalid Table Name.")},
    {0x0005, std::string("MAPPED SQL WRITER: Invalid Column Name.")},
    {0x0006, std::string("MAPPED SQL WRITER: Invalid ORDER BY direction (ACS, DESC)")},
    {0x0007, std::string("MAPPED SQL WRITER: No Select fields in select clause.")},
    {0x0008, std::string("MAPPED SQL WRITER: No from fields in select clause.")},
    {0x1000, std::string("LOGGER: Unable to open log file.")},
    {0x1001, std::string("LOGGER: Unable to start thread.")},
    {0x1002, std::string("LOGGER: Text Edit not assignd.")}
  };

  // Returns the string of the error message.
  //
  // 2013-01-26/GGB - Function created.

  std::string CQCLError::errorMessage() const
  {
    std::map <size_t, std::string> :: const_iterator errorData;

    if ((errorData = errorMessages.find(errorCode_)) == errorMessages.end() )
		{
				// Error message not found - Error code has not been defined. 
				// This is a non-recoverable error.

      exit(0xFFFE);		// Non-recoverable error within an error
		}
    else
      return (errorData->second);
  }

  // Static function to copy all the error messages from the array into the map.
  // The error messages do not have to be in order or contiguous in the array.
  //
  // 2013-01-26/GGB - Function created

  void CQCLError::loadErrorMessages()
  {
    size_t elements = sizeof(errorArray) / sizeof(SErrorCodes);   // Work out how many elements stored.
    size_t index;

    for (index = 0; index < elements; index++)
      errorMessages[errorArray[index].errorCode_] = errorArray[index].errorMessage;
  }

  /// Function to write the error message to a logFile.
  /// This is not automatically done in the library when an exception is thrown as the library may be able to recover from the
  /// exception without having to terminate.
  //
  // 2014-12-24/GGB - Function created.

  void CQCLError::logErrorMessage() const
  {
    std::map<size_t, std::string>::const_iterator errorData;

    if ((errorData = errorMessages.find(errorCode_)) == errorMessages.end() )
    {
        // Error message not found - Error code has not been defined.
        // This is a non-recoverable error.

      GCL::logger::defaultLogger().logMessage(GCL::logger::error,
                                           "Non recoverable error within an error in GCL library. Error Code: " +
                                           boost::lexical_cast<std::string>(errorCode_) + ". Terminating");
      exit(0xFFFE);		// Non-recoverable error within an error
    }
    else
      GCL::logger::defaultLogger().logMessage(GCL::logger::warning,
                                           "QCL Error Code: " + boost::lexical_cast<std::string>(errorData->first) +
                                           " - " + errorData->second);
  }

  //********************************************************************************************************************************
  //
  // CQCLCodeError
  //
  //********************************************************************************************************************************

  // Displays the error message in a QMessageBox.
	//
  // 2015-05-30/GGB - Function created.

  std::string CQCLCodeError::errorMessage() const
	{
    std::ostringstream o;

    o << "A code error has occurred in the GCL Library." << std::endl;
    o << "File name: " << fileName << " dated: " << timeStamp << std::endl;
    o << "Line number: " << lineNo << std::endl;

    return o.str();
  }

  /// Function to write the error message to a logFile.
  /// This is not automatically done in the library when an exception is thrown as the library may be able to recover from the
  /// exception without having to terminate.
  //
  // 2014-12-24/GGB - Function created.

  void CQCLCodeError::logErrorMessage() const
  {
    GCL::logger::defaultLogger().logMessage(GCL::logger::error,
                                         "A Code Error has occurred in the QCL library File Name: " + fileName +
                                         ". Line Number: " + boost::lexical_cast<std::string>(lineNo));
  }

}  // namespace QCL

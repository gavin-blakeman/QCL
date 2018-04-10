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

#ifndef QCL_ERROR_H
#define QCL_ERROR_H

#include <stdexcept>
#include <string>
#include <map>

namespace QCL
{

  class CQCLError : public std::runtime_error
  {
  private:
    static std::map<size_t, std::string> errorMessages;
    size_t errorCode_;

  public:
    inline explicit CQCLError(size_t newError) : std::runtime_error("GCL Error"), errorCode_(newError) {}

    virtual size_t errorCode() const { return errorCode_;}
    virtual std::string errorMessage() const;
    virtual void logErrorMessage() const;

    static void loadErrorMessages();
  };

  class CQCLCodeError : public CQCLError
  {
  private:
    long lineNo;
    std::string fileName;
    std::string timeStamp;

  public:
    inline explicit CQCLCodeError(const std::string newFile, const std::string newTime, long newLine)
      : CQCLError(0xFFFF), lineNo(newLine), fileName(newFile), timeStamp(newTime) {}

    virtual ~CQCLCodeError() {}

    virtual std::string errorMessage() const;
    virtual void logErrorMessage() const;
  };

#define QCL_ERROR(errorNo) (throw(CQCLError(errorNo)))
#define QCL_CODE_ERROR throw (CQCLCodeError( __FILE__, __TIMESTAMP__, (long) __LINE__) )

}	// namespace QCL

#endif // QCL_ERROR_H

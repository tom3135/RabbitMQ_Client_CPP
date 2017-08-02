// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef UTIL_INPUT_UTIL_H
#define UTIL_INPUT_UTIL_H

#include <ConfigUtil.h>
#include <string>

namespace UtilInternal
{

//
// Portable strtoll/_strtoi64
//
UTIL_API Util::Int64 strToInt64(const char*, char**, int);

//
// stringToInt64 converts a string into a signed 64-bit integer.
// It's a simple wrapper around strToInt64.
//
// Semantics:
//
// - Ignore leading whitespace
//
// - If the string starts with '0', parse as octal
//
// - If the string starts with "0x" or "0X", parse as hexadecimal
//
// - Otherwise, parse as decimal
//
// - return value == true indicates a successful conversion and result contains the converted value
// - return value == false indicates an unsuccessful conversion:
//      - result == 0 indicates that no digits were available for conversion
//      - result == "Int64 Min" or result == "Int64 Max" indicate underflow or overflow.
//
UTIL_API  bool stringToInt64(const std::string&, Util::Int64&);

}

#endif

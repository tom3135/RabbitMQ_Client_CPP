// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <ConfigUtil.h>
#include <vector>

namespace UtilInternal
{

//
// Add escape sequences (like "\n", or "\0xxx") to make a string
// readable in ASCII.
//
UTIL_API std::string escapeString(const std::string&, const std::string&);

//
// Remove escape sequences added by escapeString. Throws IllegalArgumentException
// for an invalid input string.
//
UTIL_API std::string unescapeString(const std::string&, std::string::size_type, std::string::size_type);

//
// Split a string using the given delimiters. Considers single and double quotes;
// returns false for unbalanced quote, true otherwise.
//
UTIL_API bool splitString(const std::string&, const std::string&, std::vector<std::string>&);

//
// Join a list of strings using the given delimiter. 
//
UTIL_API std::string joinString(const std::vector<std::string>&, const std::string&);

//
// Trim white space
//
UTIL_API std::string trim(const std::string&);

//
// If a single or double quotation mark is found at the start
// position, then the position of the matching closing quote is
// returned. If no quotation mark is found at the start position, then
// 0 is returned. If no matching closing quote is found, then
// std::string::npos is returned.
//
UTIL_API std::string::size_type checkQuote(const std::string&, std::string::size_type = 0);

//
// Match `s' against the pattern `pat'. A * in the pattern acts
// as a wildcard: it matches any non-empty sequence of characters
// other than a period (`.'). We match by hand here because
// it's portable across platforms (whereas regex() isn't).
//
UTIL_API bool match(const std::string&, const std::string&, bool = false);

//
// Get the error message for the last error code or given error code.
//
UTIL_API std::string lastErrorToString();
#ifdef _WIN32
UTIL_API std::string errorToString(int, LPCVOID = NULL);
#else
UTIL_API std::string errorToString(int);
#endif

//
// Functions to convert to lower/upper case. These functions accept
// UTF8 string/characters but ignore non ASCII characters. Unlike, the
// C methods, these methods are not local dependent.
//
UTIL_API std::string toLower(const std::string&);
UTIL_API std::string toUpper(const std::string&);
UTIL_API bool isAlpha(char);
UTIL_API bool isDigit(char);

//
// Remove all whitespace from a string
//
UTIL_API std::string removeWhitespace(const std::string&);

}

#endif

// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef UTIL_UNICODE_H
#define UTIL_UNICODE_H

#include <ConfigUtil.h>
#include <Exception.h>

namespace Util
{

enum ConversionFlags
{
    strictConversion = 0,
    lenientConversion
};

UTIL_API std::string wstringToString(const std::wstring&, ConversionFlags = lenientConversion);
UTIL_API std::wstring stringToWstring(const std::string&, ConversionFlags = lenientConversion);

typedef unsigned char Byte;

UTIL_API bool
isLegalUTF8Sequence(const Byte* source, const Byte* end);

enum ConversionError
{
    partialCharacter,
    badEncoding
};

//
// UTFConversionException is raised by wstringToString() or stringToWstring()
// to report a conversion error 
//
class UTIL_API UTFConversionException : public Exception
{
public:
    
    UTFConversionException(const char*, int, ConversionError);
    virtual std::string name() const;
    virtual void print(std::ostream&) const;
    virtual UTFConversionException* clone() const;
    virtual void throwex() const;

    ConversionError conversionError() const;
private:

    const ConversionError _conversionError;
    static const char* _name;    
};

}

namespace UtilInternal
{

//
// Converts UTF-8 byte-sequences to and from UTF-16 or UTF-32 (with native
// endianness) depending on sizeof(wchar_t).
//
// These are thin wrappers over the UTF8/16/32 converters provided by 
// unicode.org
//

enum ConversionResult
{
        conversionOK,           /* conversion successful */
        sourceExhausted,        /* partial character in source, but hit end */
        targetExhausted,        /* insuff. room in target for conversion */
        sourceIllegal           /* source sequence is illegal/malformed */
};

UTIL_API ConversionResult 
convertUTFWstringToUTF8(const wchar_t*& sourceStart, const wchar_t* sourceEnd, 
                        Util::Byte*& targetStart, Util::Byte* targetEnd, Util::ConversionFlags flags);

UTIL_API ConversionResult
convertUTF8ToUTFWstring(const Util::Byte*& sourceStart, const Util::Byte* sourceEnd, 
                        wchar_t*& targetStart, wchar_t* targetEnd, Util::ConversionFlags flags);

UTIL_API ConversionResult 
convertUTF8ToUTFWstring(const Util::Byte*& sourceStart, const Util::Byte* sourceEnd, 
                        std::wstring& target, Util::ConversionFlags flags);

}

#endif

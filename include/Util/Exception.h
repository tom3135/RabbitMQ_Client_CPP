// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef UTIL_EXCEPTION_H
#define UTIL_EXCEPTION_H

#include <ConfigUtil.h>

#include <exception>

namespace Util
{

class UTIL_API Exception : public std::exception
{
public:

    Exception();
    Exception(const char*, int);

    virtual ~Exception() throw();
    virtual std::string name() const;
    virtual void print(std::ostream&) const;
    virtual const char* what() const throw();
    virtual Exception* clone() const;
    virtual void throwex() const;

    const char* file() const;
    int line() const;
    const std::string& stackTrace() const;
    
private:
    
    const char* _file;
    int _line;
    static const char* _name;
    const std::string _stackTrace;
    mutable ::std::string _str; // Initialized lazily in what().
};

UTIL_API std::ostream& operator<<(std::ostream&, const Exception&);

class UTIL_API NullHandleException : public Exception
{
public:
    
    NullHandleException(const char*, int);
    virtual ~NullHandleException() throw();
    virtual std::string name() const;
    virtual NullHandleException* clone() const;
    virtual void throwex() const;

private:

    static const char* _name;
};

class UTIL_API IllegalArgumentException : public Exception
{
public:
    
    IllegalArgumentException(const char*, int);
    IllegalArgumentException(const char*, int, const std::string&);
    virtual ~IllegalArgumentException() throw();
    virtual std::string name() const;
    virtual void print(std::ostream&) const;
    virtual IllegalArgumentException* clone() const;
    virtual void throwex() const;

    std::string reason() const;

private:

    static const char* _name;
    std::string _reason;
};

class UTIL_API SyscallException : public Exception
{
public:

    SyscallException(const char*, int, int);
    virtual std::string name() const;
    virtual void print(std::ostream&) const;
    virtual SyscallException* clone() const;
    virtual void throwex() const;

    int error() const;

private:

    const int _error;
    static const char* _name;
};

class UTIL_API FileLockException : public Exception
{
public:

    FileLockException(const char*, int, int, const std::string&);
    virtual ~FileLockException() throw();
    virtual std::string name() const;
    virtual void print(std::ostream&) const;
    virtual FileLockException* clone() const;
    virtual void throwex() const;

    std::string path() const;
    int error() const;

private:

    const int _error;
    static const char* _name;
    std::string _path;
};

class UTIL_API OptionalNotSetException : public Exception
{
public:
    
    OptionalNotSetException(const char*, int);
    virtual ~OptionalNotSetException() throw();
    virtual std::string name() const;
    virtual OptionalNotSetException* clone() const;
    virtual void throwex() const;

private:

    static const char* _name;
};

}

#endif

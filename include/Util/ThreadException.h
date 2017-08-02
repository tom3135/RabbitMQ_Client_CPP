// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef UTIL_THREAD_EXCEPTION_H
#define UTIL_THREAD_EXCEPTION_H

#include <Exception.h>
#include <TimeEx.h>

namespace Util
{

class UTIL_API ThreadSyscallException : public SyscallException
{
public:

    ThreadSyscallException(const char*, int, int);
    virtual std::string name() const;
    virtual ThreadSyscallException* clone() const;
    virtual void throwex() const;

private:

    static const char* _name;
};

class UTIL_API ThreadLockedException : public Exception
{
public:

    ThreadLockedException(const char*, int);
    virtual std::string name() const;
    virtual ThreadLockedException* clone() const;
    virtual void throwex() const;

private:

    static const char* _name;
};

class UTIL_API ThreadStartedException : public Exception
{
public:

    ThreadStartedException(const char*, int);
    virtual std::string name() const;
    virtual ThreadStartedException* clone() const;
    virtual void throwex() const;

private:

    static const char* _name;
};

class UTIL_API ThreadNotStartedException : public Exception
{
public:

    ThreadNotStartedException(const char*, int);
    virtual std::string name() const;
    virtual ThreadNotStartedException* clone() const;
    virtual void throwex() const;

private:

    static const char* _name;
};

class UTIL_API BadThreadControlException : public Exception
{
public:

    BadThreadControlException(const char*, int);
    virtual std::string name() const;
    virtual BadThreadControlException* clone() const;
    virtual void throwex() const;

private:

    static const char* _name;
};

class UTIL_API InvalidTimeoutException : public Exception
{
public:

    InvalidTimeoutException(const char*, int, const Time&);
    virtual std::string name() const;
    virtual void print(std::ostream&) const;
    virtual InvalidTimeoutException* clone() const;
    virtual void throwex() const;

private:
    
    Time _timeout;
    static const char* _name;
};
    
}

#endif


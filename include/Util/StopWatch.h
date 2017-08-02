// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef UTIL_STOPWATCH_H
#define UTIL_STOPWATCH_H

#include <Time.h>

namespace UtilInternal
{

class StopWatch
{
public:

    StopWatch() { }

    void start()
    {
        _s = Util::Time::now(Util::Time::Monotonic);
    }
    
    Util::Int64 stop()
    {
        assert(isStarted());
        Util::Int64 d = (Util::Time::now(Util::Time::Monotonic) - _s).toMicroSeconds();
        _s = Util::Time();
        return d;
    }

    bool isStarted() const
    {
        return _s != Util::Time();
    }

    Util::Int64 delay()
    {
        return (Util::Time::now(Util::Time::Monotonic) - _s).toMicroSeconds();
    }

private:

    Util::Time _s;
};

} // End namespace UtilInternal

#endif

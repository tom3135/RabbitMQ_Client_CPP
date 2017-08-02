// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef UTIL_TIMER_H
#define UTIL_TIMER_H

#include <Shared.h>
#include <Thread.h>
#include <Monitor.h>
#include <Time.h>

#include <set>
#include <map>

namespace Util
{

class Timer;
typedef Util::Handle<Timer> TimerPtr;

//
// Extend the TimerTask class and override the runTimerTask() method to execute
// code at a specific time or repeatedly.
//
class UTIL_API TimerTask : virtual public Util::Shared
{
public:

    virtual ~TimerTask() { }

    virtual void runTimerTask() = 0;
};
typedef Util::Handle<TimerTask> TimerTaskPtr;

//
// The timer class is used to schedule tasks for one-time execution or
// repeated execution. Tasks are executed by the dedicated timer thread 
// sequentially.
//
class UTIL_API Timer : public virtual Util::Shared, private virtual Util::Thread
{
public:

    //
    // Construct a timer and starts its execution thread.
    //
    Timer();


    //
    // Construct a timer and starts its execution thread with the priority.
    //
    Timer(int priority);

    //
    // Destroy the timer and detach its execution thread if the calling thread 
    // is the timer thread, join the timer execution thread otherwise.
    //
    void destroy();

    //
    // Schedule a task for execution after a given delay.
    //
    void schedule(const TimerTaskPtr&, const Util::Time&);

    //
    // Schedule a task for repeated execution with the given delay
    // between each execution.
    //
    void scheduleRepeated(const TimerTaskPtr&, const Util::Time&);

    //
    // Cancel a task. Returns true if the task has not yet run or if
    // it's a task scheduled for repeated execution. Returns false if
    // the task has already run, was already cancelled or was never
    // schedulded.
    //
    bool cancel(const TimerTaskPtr&);

private:

    struct Token
    {
        Util::Time scheduledTime;
        Util::Time delay;
        TimerTaskPtr task;

        inline Token(const Util::Time&, const Util::Time&, const TimerTaskPtr&);
        inline bool operator<(const Token& r) const;
    };

    virtual void run();

    Util::Monitor<Util::Mutex> _monitor;
    bool _destroyed;
    std::set<Token> _tokens;
    
    class TimerTaskCompare : public std::binary_function<TimerTaskPtr, TimerTaskPtr, bool>
    {
    public:
        
        bool operator()(const TimerTaskPtr& lhs, const TimerTaskPtr& rhs) const
        {
            return lhs.get() < rhs.get();
        }
    };
    std::map<TimerTaskPtr, Util::Time, TimerTaskCompare> _tasks;
    Util::Time _wakeUpTime;
};
typedef Util::Handle<Timer> TimerPtr;

inline 
Timer::Token::Token(const Util::Time& st, const Util::Time& d, const TimerTaskPtr& t) :
    scheduledTime(st), delay(d), task(t)
{
}

inline bool
Timer::Token::operator<(const Timer::Token& r) const
{
    if(scheduledTime < r.scheduledTime)
    {
        return true;
    }
    else if(scheduledTime > r.scheduledTime)
    {
        return false;
    }
    
    return task.get() < r.task.get();
}

}

#endif


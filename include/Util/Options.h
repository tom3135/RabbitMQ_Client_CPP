// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef UTIL_OPTIONS_H
#define UTIL_OPTIONS_H

#include <ConfigUtil.h>
#include <RecMutex.h>
#include <Shared.h>
#include <Handle.h>
#include <Exception.h>
#include <string>
#include <vector>
#include <map>

namespace UtilInternal
{

class UTIL_API APIException : public Util::Exception
{
public:

    APIException(const char*, int, const ::std::string&);
    virtual ~APIException() throw();
    virtual ::std::string name() const;
    virtual void print(std::ostream&) const;
    virtual APIException* clone() const;
    virtual void throwex() const;

    ::std::string reason;

private:

    static const char* _name;
};

UTIL_API ::std::ostream& operator<<(::std::ostream&, const APIException&);

class UTIL_API BadOptException : public Util::Exception
{
public:

    BadOptException(const char*, int, const ::std::string&);
    virtual ~BadOptException() throw();
    virtual ::std::string name() const;
    virtual void print(std::ostream&) const;
    virtual BadOptException* clone() const;
    virtual void throwex() const;

    ::std::string reason;

private:

    static const char* _name;
};

UTIL_API ::std::ostream& operator<<(::std::ostream&, const BadOptException&);

class UTIL_API Options
{
public:

    enum LengthType { ShortOpt, LongOpt };
    enum RepeatType { Repeat, NoRepeat };
    enum ArgType { NeedArg, NoArg };

    Options();
    void addOpt(const ::std::string&, const ::std::string& = "",
                ArgType = NoArg, ::std::string = "", RepeatType = NoRepeat);

    typedef ::std::vector< ::std::string> StringVector;

    static StringVector split(const ::std::string&);
    StringVector parse(const StringVector&);
    StringVector parse(int, const char* const []);
    bool isSet(const ::std::string&) const;
    ::std::string optArg(const ::std::string&) const;
    StringVector argVec(const ::std::string&) const;

private:

    struct OptionDetails : public Util::Shared
    {
        LengthType length;
        ArgType arg;
        RepeatType repeat;
        bool hasDefault;
    };
    typedef Util::Handle<OptionDetails> ODPtr;

    struct OptionValue : public Util::Shared
    {
        ::std::string val;
    };
    typedef Util::Handle<OptionValue> OValPtr;

    struct OptionValueVector : public Util::Shared
    {
        ::std::vector< ::std::string> vals;
    };
    typedef Util::Handle<OptionValueVector> OVecPtr;

    typedef ::std::map< ::std::string, ODPtr> ValidOpts; // Valid options and their details.
    typedef ::std::map< ::std::string, OValPtr> Opts; // Value of non-repeating options.
    typedef ::std::map< ::std::string, OVecPtr> ROpts; // Value of repeating options.
    typedef ::std::map< ::std::string, ::std::string> Synonyms; // Map from short to long option and vice versa.

    void addValidOpt(const ::std::string&, const ::std::string&, ArgType, const ::std::string&, RepeatType);
    ValidOpts::iterator checkOpt(const ::std::string&, LengthType);
    void setOpt(const ::std::string&, const ::std::string&, const ::std::string&, RepeatType);
    void setNonRepeatingOpt(const ::std::string&, const ::std::string&);
    void setRepeatingOpt(const ::std::string&, const ::std::string&);
    ValidOpts::const_iterator checkOptIsValid(const ::std::string&) const;
    ValidOpts::const_iterator checkOptHasArg(const ::std::string&) const;
    void updateSynonyms(const ::std::string&, const ::std::string&);
    ::std::string getSynonym(const ::std::string&) const;

    ValidOpts _validOpts;
    Opts _opts;
    ROpts _ropts;
    Synonyms _synonyms;

    bool parseCalled;

    Util::RecMutex _m;

    Options(const Options&); // Not allowed.
    void operator=(const Options&); // Not allowed.

    static void checkArgs(const ::std::string&, const ::std::string&, bool, const ::std::string&);
};

}

#endif

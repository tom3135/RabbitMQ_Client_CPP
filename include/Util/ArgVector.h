// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef UTIL_ARGVECTOR_H
#define UTIL_ARGVECTOR_H

#include <ConfigUtil.h>
#include <vector>
#include <string>

namespace UtilInternal
{

class UTIL_API ArgVector
{
public:

    ArgVector(int argc, char* const argv[]);
    ArgVector(const ::std::vector< ::std::string>&);
    ArgVector(const ArgVector&);
    ArgVector& operator=(const ArgVector&);
    ~ArgVector();

    int argc;
    char** argv;

private:

    ::std::vector< ::std::string> _args;
    void setupArgcArgv();
};

}

#endif

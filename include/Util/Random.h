// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef UTIL_RANDOM_H
#define UTIL_RANDOM_H

#include <ConfigUtil.h>
#include <Exception.h>

namespace UtilInternal
{

UTIL_API void generateRandom(char*, int);
UTIL_API unsigned int random(int = 0);

}

#endif

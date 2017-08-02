// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef UTIL_MUTEX_PROTOCOL_H
#define UTIL_MUTEX_PROTOCOL_H

#include <ConfigUtil.h>

namespace Util
{

enum MutexProtocol
{
    PrioInherit,
    PrioNone
};

UTIL_API MutexProtocol getDefaultMutexProtocol();

} // End namespace Util

#endif

// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef UTIL_UTIL_H
#define UTIL_UTIL_H

//
// This file must include *all* other headers of Util, except
// for DisableWarnings.h and headers with only UtilInternal symbols
//

#include <Config.h>
#include <AbstractMutex.h>
#include <Cache.h>
#include <Cond.h>
#ifndef OS_WINRT
#   include <CtrlCHandler.h>
#endif
#include <Exception.h>
#include <Functional.h>
#include <Handle.h>
#include <Lock.h>
#include <Monitor.h>
#include <MutexProtocol.h>
#include <Mutex.h>
#include <MutexPtrLock.h>
#include <RecMutex.h>
#include <ScopedArray.h>
#include <Shared.h>
#include <Thread.h>
#include <ThreadException.h>
#include <Time.h>
#include <Timer.h>
#include <UUID.h>
#include <Unicode.h>
#include <UniquePtr.h>
#include <IniFile.h>

#endif

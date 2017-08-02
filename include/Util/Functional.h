// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef UTIL_FUNCTIONAL_H
#define UTIL_FUNCTIONAL_H

#include <Handle.h>
#include <functional>

namespace UtilInternal
{

// ----------------------------------------------------------------------
// Various function objects that work with handles instead of plain
// pointers.
// ----------------------------------------------------------------------

template<class R, class T, class H>
class MemFun : public std::unary_function<H, R>
{
    typedef R (T::*MemberFN)(void);
    MemberFN _mfn;

public:

    explicit MemFun(MemberFN p) : _mfn(p) { }
    R operator()(H handle) const
    {
        return (handle.get() ->* _mfn)();
    }
};

template<class R, class T, class H, class A>
class MemFun1 : public std::binary_function<H, A, R>
{
    typedef R (T::*MemberFN)(A);
    MemberFN _mfn;

public:

    explicit MemFun1(MemberFN p) : _mfn(p) { }
    R operator()(H handle, A arg) const
    {
        return (handle.get() ->* _mfn)(arg);
    }
};

template<class T, class H>
class VoidMemFun : public std::unary_function<H, void>
{
    typedef void (T::*MemberFN)(void);
    MemberFN _mfn;

public:

    explicit VoidMemFun(MemberFN p) : _mfn(p) { }
    void operator()(H handle) const
    {
        (handle.get() ->* _mfn)();
    }
};

template<class T, class H, class A>
class VoidMemFun1 : public std::binary_function<H, A, void>
{
    typedef void (T::*MemberFN)(A);
    MemberFN _mfn;

public:

    explicit VoidMemFun1(MemberFN p) : _mfn(p) { }
    void operator()(H handle, A arg) const
    {
        (handle.get() ->* _mfn)(arg);
    }
};

template<class R, class K, class T, class H>
class SecondMemFun : public std::unary_function<std::pair<K, H>, R>
{
    typedef R (T::*MemberFN)(void);
    MemberFN _mfn;

public:

    explicit SecondMemFun(MemberFN p) : _mfn(p) { }
    R operator()(std::pair<K, H> pair) const
    {
        return (pair.second.get() ->* _mfn)();
    }
};

template<class R, class K, class T, class H, class A>
class SecondMemFun1 : public std::binary_function<std::pair<K, H>, A, R>
{
    typedef R (T::*MemberFN)(A);
    MemberFN _mfn;

public:

    explicit SecondMemFun1(MemberFN p) : _mfn(p) { }
    R operator()(std::pair<K, H> pair, A arg) const
    {
        return (pair.second.get() ->* _mfn)(arg);
    }
};

template<class K, class T, class H>
class SecondVoidMemFun : public std::unary_function<std::pair<K, H>, void>
{
    typedef void (T::*MemberFN)(void);
    MemberFN _mfn;

public:

    explicit SecondVoidMemFun(MemberFN p) : _mfn(p) { }
    void operator()(std::pair<K, H> pair) const
    {
        (pair.second.get() ->* _mfn)();
    }
};

template<class K, class T, class H, class A>
class SecondVoidMemFun1 : public std::binary_function<std::pair<K, H>, A, void>
{
    typedef void (T::*MemberFN)(A);
    MemberFN _mfn;

public:

    explicit SecondVoidMemFun1(MemberFN p) : _mfn(p) { }
    void operator()(std::pair<K, H> pair, A arg) const
    {
        (pair.second.get() ->* _mfn)(arg);
    }
};

template<class R, class T, class H>
class ConstMemFun : public std::unary_function<H, R>
{
    typedef R (T::*MemberFN)(void) const;
    MemberFN _mfn;

public:

    explicit ConstMemFun(MemberFN p) : _mfn(p) { }
    R operator()(H handle) const
    {
        return (handle.get() ->* _mfn)();
    }
};

template<class R, class T, class H, class A>
class ConstMemFun1 : public std::binary_function<H, A, R>
{
    typedef R (T::*MemberFN)(A) const;
    MemberFN _mfn;

public:

    explicit ConstMemFun1(MemberFN p) : _mfn(p) { }
    R operator()(H handle, A arg) const
    {
        return (handle.get() ->* _mfn)(arg);
    }
};

template<class T, class H>
class ConstVoidMemFun : public std::unary_function<H, void>
{
    typedef void (T::*MemberFN)(void) const;
    MemberFN _mfn;

public:

    explicit ConstVoidMemFun(MemberFN p) : _mfn(p) { }
    void operator()(H handle) const
    {
        (handle.get() ->* _mfn)();
    }
};

template<class T, class H, class A>
class ConstVoidMemFun1 : public std::binary_function<H, A, void>
{
    typedef void (T::*MemberFN)(A) const;
    MemberFN _mfn;

public:

    explicit ConstVoidMemFun1(MemberFN p) : _mfn(p) { }
    void operator()(H handle, A arg) const
    {
        (handle.get() ->* _mfn)(arg);
    }
};

template<class R, class K, class T, class H>
class SecondConstMemFun : public std::unary_function<std::pair<K, H>, R>
{
    typedef R (T::*MemberFN)(void) const;
    MemberFN _mfn;

public:

    explicit SecondConstMemFun(MemberFN p) : _mfn(p) { }
    R operator()(std::pair<K, H> pair) const
    {
        return (pair.second.get() ->* _mfn)();
    }
};

template<class R, class K, class T, class H, class A>
class SecondConstMemFun1 : public std::binary_function<std::pair<K, H>, A, R>
{
    typedef R (T::*MemberFN)(A) const;
    MemberFN _mfn;

public:

    explicit SecondConstMemFun1(MemberFN p) : _mfn(p) { }
    R operator()(std::pair<K, H> pair, A arg) const
    {
        return (pair.second.get() ->* _mfn)(arg);
    }
};

template<class K, class T, class H>
class SecondConstVoidMemFun : public std::unary_function<std::pair<K, H>, void>
{
    typedef void (T::*MemberFN)(void) const;
    MemberFN _mfn;

public:

    explicit SecondConstVoidMemFun(MemberFN p) : _mfn(p) { }
    void operator()(std::pair<K, H> pair) const
    {
        (pair.second.get() ->* _mfn)();
    }
};

template<class K, class T, class H, class A>
class SecondConstVoidMemFun1 : public std::binary_function<std::pair<K, H>, A, void>
{
    typedef void (T::*MemberFN)(A) const;
    MemberFN _mfn;

public:

    explicit SecondConstVoidMemFun1(MemberFN p) : _mfn(p) { }
    void operator()(std::pair<K, H> pair, A arg) const
    {
        (pair.second.get() ->* _mfn)(arg);
    }
};

}

// ----------------------------------------------------------------------
// Inline functions that return function objects that work with
// Util::Handle
// ----------------------------------------------------------------------

namespace Util
{

template<class R, class T>
inline ::UtilInternal::MemFun<R, T, Handle<T> >
memFun(R (T::*p)(void))
{
    return ::UtilInternal::MemFun<R, T, Handle<T> >(p);
}

template<class R, class T, class A>
inline ::UtilInternal::MemFun1<R, T, Handle<T>, A>
memFun1(R (T::*p)(A))
{
    return ::UtilInternal::MemFun1<R, T, Handle<T>, A>(p);
}

template<class T>
inline ::UtilInternal::VoidMemFun<T, Handle<T> >
voidMemFun(void (T::*p)(void))
{
    return ::UtilInternal::VoidMemFun<T, Handle<T> >(p);
}

template<class T, class A>
inline ::UtilInternal::VoidMemFun1<T, Handle<T>, A>
voidMemFun1(void (T::*p)(A))
{
    return ::UtilInternal::VoidMemFun1<T, Handle<T>, A>(p);
}

template<class R, class K, class T>
inline ::UtilInternal::SecondMemFun<R, K, T, Handle<T> >
secondMemFun(R (T::*p)(void))
{
    return ::UtilInternal::SecondMemFun<R, K, T, Handle<T> >(p);
}

template<class R, class K, class T, class A>
inline ::UtilInternal::SecondMemFun1<R, K, T, Handle<T>, A>
secondMemFun1(R (T::*p)(A))
{
    return ::UtilInternal::SecondMemFun1<R, K, T, Handle<T>, A>(p);
}

template<class K, class T>
inline ::UtilInternal::SecondVoidMemFun<K, T, Handle<T> >
secondVoidMemFun(void (T::*p)(void))
{
    return ::UtilInternal::SecondVoidMemFun<K, T, Handle<T> >(p);
}

template<class K, class T, class A>
inline ::UtilInternal::SecondVoidMemFun1<K, T, Handle<T>, A>
secondVoidMemFun1(void (T::*p)(A))
{
    return ::UtilInternal::SecondVoidMemFun1<K, T, Handle<T>, A>(p);
}

template<class R, class T>
inline ::UtilInternal::ConstMemFun<R, T, Handle<T> >
constMemFun(R (T::*p)(void) const)
{
    return ::UtilInternal::ConstMemFun<R, T, Handle<T> >(p);
}

template<class R, class T, class A>
inline ::UtilInternal::ConstMemFun1<R, T, Handle<T>, A>
constMemFun1(R (T::*p)(A) const)
{
    return ::UtilInternal::ConstMemFun1<R, T, Handle<T>, A>(p);
}

template<class T>
inline ::UtilInternal::ConstVoidMemFun<T, Handle<T> >
constVoidMemFun(void (T::*p)(void) const)
{
    return ::UtilInternal::ConstVoidMemFun<T, Handle<T> >(p);
}

template<class T, class A>
inline ::UtilInternal::ConstVoidMemFun1<T, Handle<T>, A>
constVoidMemFun1(void (T::*p)(A) const)
{
    return ::UtilInternal::ConstVoidMemFun1<T, Handle<T>, A>(p);
}

template<class R, class K, class T>
inline ::UtilInternal::SecondConstMemFun<R, K, T, Handle<T> >
secondConstMemFun(R (T::*p)(void) const)
{
    return ::UtilInternal::SecondConstMemFun<R, K, T, Handle<T> >(p);
}

template<class R, class K, class T, class A>
inline ::UtilInternal::SecondConstMemFun1<R, K, T, Handle<T>, A>
secondConstMemFun1(R (T::*p)(A) const)
{
    return ::UtilInternal::SecondConstMemFun1<R, K, T, Handle<T>, A>(p);
}

template<class K, class T>
inline ::UtilInternal::SecondConstVoidMemFun<K, T, Handle<T> >
secondConstVoidMemFun(void (T::*p)(void) const)
{
    return ::UtilInternal::SecondConstVoidMemFun<K, T, Handle<T> >(p);
}

template<class K, class T, class A>
inline ::UtilInternal::SecondConstVoidMemFun1<K, T, Handle<T>, A>
secondConstVoidMemFun1(void (T::*p)(A) const)
{
    return ::UtilInternal::SecondConstVoidMemFun1<K, T, Handle<T>, A>(p);
}

}

#endif


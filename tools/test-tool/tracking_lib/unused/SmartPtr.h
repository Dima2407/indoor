#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <map>
#include <list>
#include <algorithm>
#include <iostream>
#include <cassert>
#ifndef _WIN32
#include <inttypes.h>
#endif

class SmartPtrProtho {
    private:
        void init();
        void release();

    protected:
        virtual ~SmartPtrProtho();

        bool decrease(void *ptr);
        bool increase(void *ptr);
        size_t count(void *ptr) const;

        //static std::map<void*, size_t> _refs_map;
        static std::map<void*, size_t> *_refs_map;
};

//extern std::map<void*, size_t> SmartPtrProtho::_refs_map;

template <typename ObjType/*, class PtrType (Shared | Copy)*/, class Allocator = std::allocator<ObjType> > class SmartPtr : private SmartPtrProtho {
    typedef void (*DeallocFuncPtr)(void*);
    public:
        SmartPtr(ObjType *ptr = 0) throw();
        SmartPtr(const SmartPtr &) throw();
        virtual ~SmartPtr() throw();
        ObjType& operator*  () const throw();
        ObjType* operator-> () const throw();
        SmartPtr& operator=  (const SmartPtr&) throw();
        //bool operator==  (const SmartPtr&) const throw();
        //bool operator==  (ObjType*) const throw();
        template <class T> bool operator==  (const SmartPtr<T>&) const throw();
        template <class T> bool operator==  (T*) const throw();
        template <class T> bool operator!=  (const SmartPtr<T>&) const throw();
        template <class T> bool operator!=  (T*) const throw();
        operator bool() const throw();
    // Commented by Oleksiy Grechnyev, didn't work with MinGW 32 bit
//#ifdef _WIN32
//        operator __int64 () const throw();
//#else
        operator int64_t () const throw();
//#endif

        operator ObjType*() const throw();
        operator const ObjType*() const throw();
        ObjType* ptr() throw();
        const ObjType* ptr() const throw();

        bool    isNull () const throw();
        bool    notNull () const throw();
        size_t  refsCount() const throw();

        void    clear() throw();

    private:
        ObjType *_ptr;
};

template <class ObjType, class Allocator> SmartPtr<ObjType, Allocator>::SmartPtr (ObjType *ptr) throw() : _ptr(0) {
    if (ptr == 0)
        return;
    _ptr = ptr;
    SmartPtrProtho::increase(_ptr);
}

template <class ObjType, class Allocator> SmartPtr<ObjType, Allocator>::SmartPtr(const SmartPtr<ObjType, Allocator> &rhs) throw() : _ptr(0) {
    if (rhs._ptr != 0) {
        _ptr = rhs._ptr;
        SmartPtrProtho::increase(_ptr);
    }
}

template <class ObjType, class Allocator> SmartPtr<ObjType, Allocator>& SmartPtr<ObjType, Allocator>::operator= (const SmartPtr<ObjType, Allocator> &rhs) throw() {
    if (_ptr != rhs._ptr) {
        clear();
        _ptr = rhs._ptr;
        if (_ptr != 0) {
            SmartPtrProtho::increase(_ptr);
        }
    }
    return *this;
}

template <class ObjType, class Allocator> void    SmartPtr<ObjType, Allocator>::clear() throw() {
    if (_ptr != 0) {
        SmartPtrProtho::decrease(_ptr);
        if (!SmartPtrProtho::count(_ptr)) {
            delete _ptr;
        }
    }
    _ptr = 0;
}

template <class ObjType, class Allocator> SmartPtr<ObjType, Allocator>::~SmartPtr () throw() {
    clear();
}

template <class ObjType, class Allocator> ObjType& SmartPtr<ObjType, Allocator>::operator*  () const throw() {
    assert(_ptr!=0);
    return *_ptr;
}

template <class ObjType, class Allocator> ObjType* SmartPtr<ObjType, Allocator>::operator-> () const throw() {
    return _ptr;
}

template <class ObjType, class Allocator>
    template <class OtherType>
    bool SmartPtr<ObjType, Allocator>::operator== (const SmartPtr<OtherType> &rhs) const throw() {
        return _ptr == rhs._ptr;
}

template <class ObjType, class Allocator>
    template <class OtherType>
    bool SmartPtr<ObjType, Allocator>::operator== (OtherType* ptr) const throw() {
        return _ptr == ptr;
}

template <class ObjType, class Allocator>
    template<class OtherType>
    bool SmartPtr<ObjType, Allocator>::operator!= (const SmartPtr<OtherType> &rhs) const throw() {
        return _ptr != rhs._ptr;
}

template <class ObjType, class Allocator>
    template<class OtherType>
    bool SmartPtr<ObjType, Allocator>::operator!= (OtherType* ptr) const throw() {
        return _ptr != ptr;
}

template <class ObjType, class Allocator> SmartPtr<ObjType, Allocator>::operator bool () const throw() {
    return (isNull());
}

// Commented by Oleksiy Grechnyev, didn't work with MinGW 32 bit
//#ifdef _WIN32
//template <class ObjType, class Allocator> SmartPtr<ObjType, Allocator>::operator __int64 () const throw() {
//        return (__int64(_ptr));
//}
//#else
template <class ObjType, class Allocator> SmartPtr<ObjType, Allocator>::operator int64_t () const throw() {
        return (int64_t(_ptr));
}
//#endif

template <class ObjType, class Allocator> SmartPtr<ObjType, Allocator>::operator ObjType* () const throw() {
    return (_ptr);
}

template <class ObjType, class Allocator> SmartPtr<ObjType, Allocator>::operator const ObjType* () const throw() {
    return (_ptr);
}

template <class ObjType, class Allocator> ObjType * SmartPtr<ObjType, Allocator>::ptr() throw() {
    return _ptr;
}

template <class ObjType, class Allocator> const ObjType* SmartPtr<ObjType, Allocator>::ptr() const throw() {
    return _ptr;
}

template <class ObjType, class Allocator> bool SmartPtr<ObjType, Allocator>::isNull () const throw() {
    return (_ptr == 0);
}

template <class ObjType, class Allocator> bool SmartPtr<ObjType, Allocator>::notNull () const throw() {
    return (_ptr != 0);
}

template <class ObjType, class Allocator> size_t SmartPtr<ObjType, Allocator>::refsCount() const throw() {
    // Расстояние между итератором и началом списка
    //return _refs_map.count(_ptr);
    return SmartPtrProtho::count(_ptr);
}

template <class To, class From, class All, template <class Data, class A> class SP> SmartPtr<To, All> sp_dynamic_cast (const SP<From, All> &rhs);

template <class To, class From, class All, template <class Data, class A> class SP> SmartPtr<To, All> sp_dynamic_cast (const SP<From, All> &rhs) {
    SP<From, All> tmp = rhs;
    return SmartPtr<To, All>(dynamic_cast<To*>(tmp.ptr()));
}

#endif // SMARTPTR_H

/* 
 * File:   Pool_alloc.h
 * Author: peter cf16.eu
 *
 * Created on January 26, 2014, 3:34 AM
 */

#ifndef POOL_ALLOC_H
#define	POOL_ALLOC_H

#include <cstddef>
#include "Pool.h"

template< class T>
class Pool_alloc {
    static Pool mem;   // pool of elements of sizeof(T)
public:
    // like the standard allocator
      typedef unsigned long     size_type;
      typedef ptrdiff_t  difference_type;
      typedef T*       pointer;
      typedef const T* const_pointer;
      typedef T&       reference;
      typedef const T& const_reference;
      typedef T        value_type;

      template<typename _Tp1>
        struct rebind
        { typedef Pool_alloc<_Tp1> other; };

      Pool_alloc() throw() { }

      Pool_alloc(const Pool_alloc&) throw() { }

      template<typename _Tp1>
        Pool_alloc(const Pool_alloc<_Tp1>&) throw() { }

      ~Pool_alloc() throw() { }

      pointer
      address(reference __x) const { return &__x; }

      const_pointer
      address(const_reference __x) const { return &__x; }

      /* instead of
      pointer
      allocate(size_type __n, const void* = 0)
      { 
	if (__builtin_expect(__n > this->max_size(), false))
	  std::__throw_bad_alloc();

	return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
      }
       * we define: */
      pointer allocate(size_type __n, const void* = 0);

      /* instead of
      void
      deallocate(pointer __p, size_type)
      { ::operator delete(__p); }
       we define: */
      void deallocate(pointer __p, size_type);
      
      size_type
      max_size() const throw() 
      { return size_t(-1) / sizeof(T); }

      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 402. wrong new expression in [some_] allocator::construct
      void 
      construct(pointer __p, const T& __val) 
      { ::new((void *)__p) T(__val); }  // copy constructor!

#ifdef __GXX_EXPERIMENTAL_CXX0X__
      template<typename... _Args>
        void
        construct(pointer __p, _Args&&... __args)
	{ ::new((void *)__p) _Tp(std::forward<_Args>(__args)...); }
#endif

      void 
      destroy(pointer __p) { __p->~T(); }
};

template<>
class Pool_alloc<void> {
public:
      typedef void*       pointer;
      typedef const void* const_pointer;
      // no reference !
      typedef void        value_type;
      template <class U>
      struct rebind { typedef Pool_alloc<U> other; }; // in effect: typedef Pool_alloc<U> other
};

#endif	/* POOL_ALLOC_H */


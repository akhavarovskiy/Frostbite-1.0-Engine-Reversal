///////////////////////////////////////////////////////////////////////////////
// EASTL/weak_ptr.h
//
// Copyright (c) 2005, Electronic Arts. All rights reserved.
// Created by Paul Pedriana, Maxis, Electronic Arts.
//
///////////////////////////////////////////////////////////////////////////////


#ifndef EASTL_WEAK_PTR_H
#define EASTL_WEAK_PTR_H



#include <EASTL/internal/config.h>
#include <EASTL/shared_ptr.h>
#include <EASTL/allocator.h>
#include <stddef.h>


namespace eastl
{

    /// EASTL_WEAK_PTR_DEFAULT_NAME
    ///
    /// Defines a default container name in the absence of a user-provided name.
    ///
    #ifndef EASTL_WEAK_PTR_DEFAULT_NAME
        #define EASTL_WEAK_PTR_DEFAULT_NAME EASTL_DEFAULT_NAME_PREFIX " weak_ptr" // Unless the user overrides something, this is "EASTL weak_ptr".
    #endif


    /// EASTL_WEAK_PTR_DEFAULT_ALLOCATOR
    ///
    #ifndef EASTL_WEAK_PTR_DEFAULT_ALLOCATOR
        #define EASTL_WEAK_PTR_DEFAULT_ALLOCATOR allocator_type(EASTL_WEAK_PTR_DEFAULT_NAME)
    #endif



    /// weak_ptr
    ///
    /// The weak_ptr class template stores a "weak reference" to an object 
    /// that's already managed by a shared_ptr. To access the object, a weak_ptr 
    /// can be converted to a shared_ptr using the shared_ptr constructor or 
    /// the lock() member function. When the last shared_ptr to the object goes 
    /// away and the object is deleted, the attempt to obtain a shared_ptr 
    /// from the weak_ptr instances that refer to the deleted object will fail via
    /// lock() returning an empty shared_ptr.
    ///
    /// The Allocator template argument manages the memory of the shared reference
    /// count and not the stored object. weak_ptr will not delete the stored object
    /// but instead can only delete the reference count on that object.
    ///
    template <typename T, typename Allocator = EASTLAllocatorType>
    class weak_ptr
    {
    #if (!defined(__GNUC__) || (__GNUC__ >= 3)) && !defined(__MWERKS__) // Required due to GCC 2.x and Metrowerks weaknesses.
        protected:
    #else
        public:
    #endif
        /// this_type
        /// This is an alias for our own type.
        typedef weak_ptr<T, Allocator> this_type;

        /// allocator_type
        typedef Allocator allocator_type;

        // Friend declarations
        #if (!defined(__GNUC__) || (__GNUC__ >= 3)) && !defined(__MWERKS__) // GCC 2.x and Metrowerks blow up on this.
            template <typename U, typename A, typename D> friend class shared_ptr;
            template <typename U, typename A>             friend class weak_ptr;
        #endif

        T*             mpValue;       /// The owned pointer.
        ref_count_sp*  mpRefCount;    /// Reference count for owned pointer.
        allocator_type mAllocator;    /// The allocator used to manage new/delete of mpRefCount.

    public:
        typedef T element_type;

        /// weak_ptr
        weak_ptr(const allocator_type& allocator = EASTL_WEAK_PTR_DEFAULT_ALLOCATOR)
            : mpValue(NULL),
              mpRefCount(NULL),
              mAllocator(allocator)
        {
        }


        /// weak_ptr
        /// Construction with self type.
        /// If we want a weak_ptr constructor that is templated on weak_ptr<U>,
        /// then we need to make it in addition to this function, as otherwise 
        /// the compiler will generate this function and things will go wrong.
        weak_ptr(const weak_ptr& weakPtr)
            : mpValue(weakPtr.mpValue),
              mpRefCount(weakPtr.mpRefCount),
              mAllocator(weakPtr.mAllocator)
        {
            if(mpRefCount)
                ++mpRefCount->mWeakRefCount;
        }


        /// weak_ptr
        /// Constructs a weak_ptr from another weak_ptr. If you look at the Boost implementation
        /// of weak_ptr, it says that copying a weak_ptr like this is unsafe. However, Boost attempts
        /// to build thread-safety into its smart pointers, which we don't do. We don't do this 
        /// because we believe that doing so is an over-engineered approach to smart pointers.
        template <typename U>
        weak_ptr(const weak_ptr<U, Allocator>& weakPtr)
            : mpValue(weakPtr.mpValue),
              mpRefCount(weakPtr.mpRefCount),
              mAllocator(weakPtr.mAllocator)
        {
            if(mpRefCount)
                ++mpRefCount->mWeakRefCount;
        }


        /// weak_ptr
        /// Constructs a weak_ptr from a shared_ptr.
        template <typename U, typename A, typename D>
        weak_ptr(const shared_ptr<U, A, D>& sharedPtr)
            : mpValue(sharedPtr.mpValue),
              mpRefCount(sharedPtr.mpRefCount),
              mAllocator(sharedPtr.mAllocator)
        {
            if(mpRefCount)
                ++mpRefCount->mWeakRefCount;
        }


        /// ~weak_ptr
        ~weak_ptr()
        {
            if(mpRefCount)
            {
                const int newWeakRefCount(--mpRefCount->mWeakRefCount);
                if(newWeakRefCount == 0)
                {
                    mpRefCount->~ref_count_sp();
                    EASTLFree(mAllocator, mpRefCount, (size_t)mpRefCount->mnSize);
                }
            }
        }


        /// operator=(weak_ptr)
        /// assignment to self type.
        /// If we want a weak_ptr operator= that is templated on weak_ptr<U>,
        /// then we need to make it in addition to this function, as otherwise 
        /// the compiler will generate this function and things will go wrong.
        weak_ptr& operator=(const weak_ptr& weakPtr)
        {
            assign(weakPtr);
            return *this;
        }


        /// operator=(weak_ptr)
        template <typename U, typename A>
        weak_ptr& operator=(const weak_ptr<U, A>& weakPtr)
        {
            assign(weakPtr);
            return *this;
        }


        /// operator=(shared_ptr)
        /// Assigns to a weak_ptr from a shared_ptr.
        template <typename U, typename A, typename D>
        weak_ptr& operator=(const shared_ptr<U, A, D>& sharedPtr)
        {
            if(mpRefCount != sharedPtr.mpRefCount) // This check encompasses assignment to self.
            {
                // Release old reference
                if(mpRefCount)
                {
                    const int newWeakRefCount(--mpRefCount->mWeakRefCount);
                    if(newWeakRefCount == 0)
                    {
                        mpRefCount->~ref_count_sp();
                        EASTLFree(mAllocator, mpRefCount, (size_t)mpRefCount->mnSize);
                    }
                }

                // Add new reference
                // We leave mAllocator and as-is.
                mpValue    = sharedPtr.mpValue;
                mpRefCount = sharedPtr.mpRefCount;
                if(mpRefCount)
                    ++mpRefCount->mWeakRefCount;
            }
            return *this;
        }

        shared_ptr<T, Allocator> lock() const // Note: We have a problem here because the Deleter template parameter of shared_ptr is not represented.
        {
            return (mpRefCount && mpRefCount->mRefCount) ? shared_ptr<T, Allocator>(*this) : shared_ptr<T, Allocator>();
        }

        int use_count() const
        {
            return mpRefCount ? mpRefCount->mRefCount : 0;
        }

        bool expired() const
        {
            return (!mpRefCount || (mpRefCount->mRefCount == 0));
        }

        void reset()
        {
            if(mpRefCount)
            {
                const int newWeakRefCount(--mpRefCount->mWeakRefCount);
                if(newWeakRefCount == 0)
                {
                    mpRefCount->~ref_count_sp();
                    EASTLFree(mAllocator, mpRefCount, (size_t)mpRefCount->mnSize);
                }
            }

            mpValue    = NULL;
            mpRefCount = NULL;
        }

        void swap(weak_ptr& weakPtr)
        {
            // We leave mAllocator and as-is.

            T* const pValue = weakPtr.mpValue;
            weakPtr.mpValue = mpValue;
            mpValue         = pValue;

            ref_count_sp* const pRefCount = weakPtr.mpRefCount;
            weakPtr.mpRefCount = mpRefCount;
            mpRefCount         = pRefCount;
        }


        /// assign
        ///
        /// Assignment via another weak_ptr. 
        ///
        template <typename U, typename A>
        void assign(const weak_ptr<U, A>& weakPtr)
        {
            if(mpRefCount != weakPtr.mpRefCount) // This check encompasses assignment to self.
            {
                // Release old reference
                if(mpRefCount)
                {
                    const int newWeakRefCount(--mpRefCount->mWeakRefCount);
                    if(newWeakRefCount == 0)
                    {
                        mpRefCount->~ref_count_sp();
                        EASTLFree(mAllocator, mpRefCount, (size_t)mpRefCount->mnSize);
                    }
                }

                // Add new reference
                mpValue    = weakPtr.mpValue;
                mpRefCount = weakPtr.mpRefCount;
                if(mpRefCount)
                    ++mpRefCount->mWeakRefCount;
            }
        }


        /// less_than
        ///
        /// Comparison function; it obeys C++ "strict weak ordering." 
        /// This is used by external utility functions.
        ///
        template <typename Y>
        bool less_than(weak_ptr<Y> const& weakPtr) const
        {
            return (mpRefCount < weakPtr.mpRefCount);
        }


        /// assign
        ///
        /// Assignment through a T/ref_count_sp pair. This is used by 
        /// external utility functions.
        ///
        void assign(T* pValue, ref_count_sp* pRefCount)
        {
            mpValue = pValue;

            if(pRefCount != mpRefCount)
            {
                if(mpRefCount)
                {
                    const int newWeakRefCount(--mpRefCount->mWeakRefCount);
                    if(newWeakRefCount == 0)
                    {
                        mpRefCount->~ref_count_sp();
                        EASTLFree(mAllocator, mpRefCount, (size_t)mpRefCount->mnSize);
                    }
                }

                mpRefCount = pRefCount;

                if(mpRefCount)
                    ++mpRefCount->mWeakRefCount;
            }
        }

    }; // class weak_ptr



    template <typename T, typename TA, typename U, typename UA>
    inline bool operator<(const weak_ptr<T, TA>& weakPtr1, const weak_ptr<U, UA>& weakPtr2)
    {
        return weakPtr1.less_than(weakPtr2);
    }


    template <typename T, typename TA>
    void swap(weak_ptr<T, TA>& weakPtr1, weak_ptr<T, TA>& weakPtr2)
    {
        weakPtr1.swap(weakPtr2);
    }


} // namespace eastl


// We have to either #include enable_shared.h here or we need to move the enable_shared source code to here.
#include <EASTL/internal/enable_shared.h>


#endif // Header include guard






















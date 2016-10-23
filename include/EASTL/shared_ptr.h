///////////////////////////////////////////////////////////////////////////////
// EASTL/shared_ptr.h
//
// Copyright (c) 2003, Electronic Arts. All rights reserved.
// Created by Paul Pedriana, Maxis, Electronic Arts.
//
// This class implements a shared_ptr template. A shared_ptr is like the C++
// Standard Library auto_ptr except that it allows sharing of pointers between
// instances of auto_ptr via reference counting. shared_ptr objects can safely
// be copied and can safely be used in C++ Standard Library containers such
// as std::vector or std::list.
//
// Important notice:
// As of this writing (9/2003), the implementation provided here has 
// limitations that you should be aware of. These limitations will be shortly
// rectified. Most significantly, this implementation has the following 
// weaknesses:
//    - It cannot safely deal with exceptions that occur during the 
//      construction of shared_ptr objects. 
//    - It cannot safely deal with recursive shared_ptr objects. 
//      If a shared_ptr<A> holds a pointer to an instance of A and 
//      class A owns an instance of shared_ptr<A> that refers to,
//      the original instance, the memory will leak.
//    - It doesn't safely handle multiple instances of shared_ptr
//      which own the same pointer accessed from multiple threads.
//      This weakness is by design, for performance reasons. There are 
//      thread-safe versions of shared_ptr (e.g. see the EAThread package).
//      Note also that this limitation is scheduled to be reconsidered
//      and indeed thread safety may have been added by the time you
//      are reading this.
//
// The rectification of the above issues are discussed in the C++ standardization
// documents for the next C++ standard (as of 2003):
//    http://std.dkuug.dk/jtc1/sc22/wg21/docs/papers/2003/n1450.html#Implementation-difficulty
// 
// This current implementation will be eventually (hopefully by 1/2004) rectified 
// to be in line with the second generation C++ standard proposal.
//
// The intended design of this class is based somewhat on the design of the Boost
// shared_ptr template. This design is also being considered for the next C++ 
// standard (as of 2003). The C++ standard update proposal is currently available at:
//    http://std.dkuug.dk/jtc1/sc22/wg21/docs/papers/2003/n1450.html
// Boost smart pointers, including shared_ptr are documented at:
//    http://www.boost.org/libs/smart_ptr/
//
// As of this writing (10/2003), this class has received approval from EA legal
// for use. The potential issue is the similarity of the class name and class 
// interface to existing open source code.
//
///////////////////////////////////////////////////////////////////////////////


#ifndef FOUNDATION_SHARED_PTR_H
#define FOUNDATION_SHARED_PTR_H



#include <EASTL/internal/config.h>
#include <EASTL/internal/smart_ptr.h>   // Defines smart_ptr_deleter
#include <EASTL/allocator.h>

#ifdef _MSC_VER
    #pragma warning(push, 0)
    #include <new>
    #include <stddef.h>
    #pragma warning(pop)
#else
    #include <new>
    #include <stddef.h>
#endif



namespace eastl
{

    /// EASTL_SHARED_PTR_DEFAULT_NAME
    ///
    /// Defines a default container name in the absence of a user-provided name.
    ///
    #ifndef EASTL_SHARED_PTR_DEFAULT_NAME
        #define EASTL_SHARED_PTR_DEFAULT_NAME EASTL_DEFAULT_NAME_PREFIX " shared_ptr" // Unless the user overrides something, this is "EASTL shared_ptr".
    #endif


    /// EASTL_SHARED_PTR_DEFAULT_ALLOCATOR
    ///
    #ifndef EASTL_SHARED_PTR_DEFAULT_ALLOCATOR
        #define EASTL_SHARED_PTR_DEFAULT_ALLOCATOR allocator_type(EASTL_SHARED_PTR_DEFAULT_NAME)
    #endif



    // Forward declarations
    template <typename T, typename Allocator> class weak_ptr;
    template <typename T> class enable_shared_from_this;



    /// ref_count_sp
    ///
    /// This is a small utility class used by shared_ptr and weak_ptr.
    ///
    /// To consider: Save some space by declaring this struct like so,
    /// with the result being sizeof(ref_count_sp) == 12 (including 
    /// the 4 byte vtable). It happens that GeneralAllocator can allocate 
    /// objects of size 12 at the same cost as objects of size 8 due to
    /// a trick it uses.
    ///     int mnRefCount      : 31; // (1 << 31) == 2147483648
    ///     int mbCustomDispose :  1; // (1 <<  1) == 2
    ///     int mnWeakRefCount  : 24; // (1 << 24) == 16777216
    ///     int mnSize          :  8; // (1 <<  8) == 256
    ///
    struct ref_count_sp
    {
        int mRefCount;            /// Reference count on the contained pointer
        int mWeakRefCount;        /// Reference count on contained pointer plus this ref_count_sp object itself.
        int mnSize          : 15; /// Size of the ref_count_sp object, so we know how much to pass to the memory free function.
        int mbCustomDispose :  1; /// True if we are using ref_count_sp_t instead of ref_count_sp. We are taking strong measures to attempt to avoid virtual function dispose calls.

        ref_count_sp(int refCount = 1, int weakRefCount = 1)
            : mRefCount(refCount), mWeakRefCount(weakRefCount) { mnSize = sizeof(*this); mbCustomDispose = 0; }

        virtual ~ref_count_sp() { }
        virtual void dispose() { EASTL_ASSERT(false);  } // This should never be called, but we don't want to declare it pure-virtual because we want to create instances of this class.
    };


    /// ref_count_sp_t
    ///
    /// This is a version of ref_count_sp which is used to delete types that aren't 
    /// the same as the shared_ptr type. A common example of this is where the shared_ptr
    /// contains void* pointers instead of pointers to any specific type.
    ///
    template<typename T, typename Deleter>
    class ref_count_sp_t : public ref_count_sp
    {
    public:
        typedef ref_count_sp_t<T, Deleter> this_type;
        typedef T                          value_type;

        value_type mValue; // This is expected to be a pointer.

        ref_count_sp_t(value_type value, int refCount = 1, int weakRefCount = 1)
            : ref_count_sp(refCount, weakRefCount), mValue(value) { mnSize = sizeof(*this); mbCustomDispose = 1; }

        void dispose()
        {
            Deleter del;
            del(mValue);
            mValue = NULL;
        }
    };


    /// do_enable_shared_from_this
    ///
    /// If a user calls this function, it sets up mWeakPtr member of 
    /// the enable_shared_from_this parameter to point to the ref_count_sp 
    /// object that's passed in. Normally, the user doesn't need to call 
    /// this function, as the shared_ptr constructor will do it for them.
    ///
    template <typename T, typename U>
    void do_enable_shared_from_this(const ref_count_sp* pRefCount, const enable_shared_from_this<T>* pEnableSharedFromThis, const U* pValue)
    {
        if(pEnableSharedFromThis)
            pEnableSharedFromThis->mWeakPtr.assign(const_cast<U*>(pValue), const_cast<ref_count_sp*>(pRefCount));
    }

    inline void do_enable_shared_from_this(const ref_count_sp*, ...)
        { } // Empty specialization. This no-op version is called by shared_ptr when shared_ptr's T type is anything but an enabled_shared_from_this class.



    /// shared_ptr_traits
    /// This exists for the sole purpose of creating a typedef called
    /// reference_type which is specialized for type void. The reason
    /// for this is that shared_ptr::operator*() returns a reference
    /// to T but if T is void, it needs to return void, not *void, 
    /// as the latter is not valid C++.
    template <class T> struct shared_ptr_traits
        { typedef T& reference_type; };

    template <> struct shared_ptr_traits<void>
        { typedef void reference_type; };

    template <> struct shared_ptr_traits<void const>
        { typedef void reference_type; };

    template <> struct shared_ptr_traits<void volatile>
        { typedef void reference_type; };

    template <> struct shared_ptr_traits<void const volatile>
        { typedef void reference_type; };



    /// shared_ptr
    ///
    /// This class implements a shared_ptr template. A shared_ptr is like the C++
    /// Standard Library auto_ptr except that it allows sharing of pointers between
    /// instances of auto_ptr via reference counting. shared_ptr objects can safely
    /// be copied and can safely be used in C++ Standard Library containers such
    /// as std::vector or std::list.
    ///
    /// Note that this is not the final version of the shared_ptr class to be produced.
    /// A more complex version which addresses weaknesses in the current version will
    /// eventually be produced. Most of these weaknesses are somewhat esoteric, so this
    /// class will suffice for many uses in the interim. See documentation at:
    ///     http://std.dkuug.dk/jtc1/sc22/wg21/docs/papers/2003/n1450.html#Implementation-difficulty
    /// for explanations of the difficulties in producing a solid version of this class.
    ///
    /// This class is not thread safe in that you cannot use an instance of it from 
    /// two threads at the same time and cannot use two separate instances of it, which 
    /// own the same pointer, at the same time. Use standard multithread mutex techniques
    /// to address the former problems and use shared_ptr_mt to address the latter.
    /// 
    /// The Allocator template parameter controls the allocator used to allocate the 
    /// shared reference count. It does not affect the value pointer, as that is allocated
    /// by the user and (as of this writing) is destroyed by either global or custom 
    /// operator delete for that object.
    ///
    template <typename T, typename Allocator = EASTLAllocatorType, typename Deleter = smart_ptr_deleter<T> >
    class shared_ptr
    {
    #if (!defined(__GNUC__) || (__GNUC__ >= 3)) && !defined(__MWERKS__) // Required due to GCC 2.x and Metrowerks weaknesses.
        protected:
    #else
        public:
    #endif
        /// this_type
        /// This is an alias for shared_ptr<T>, this class.
        typedef shared_ptr<T, Allocator, Deleter> this_type;

        /// reference_type
        /// This defines what a reference to a T is. It's always simply T&, 
        /// except for the case where T is void, whereby the reference is 
        /// also just void.
        typedef typename shared_ptr_traits<T>::reference_type reference_type;

        /// allocator_type
        typedef Allocator allocator_type;

        /// deleter_type
        typedef Deleter                      deleter_type;
        typedef typename Deleter::value_type deletion_type;

        // Friend declarations.
        #if (!defined(__GNUC__) || (__GNUC__ >= 3)) && !defined(__MWERKS__) // GCC 2.x and Metrowerks blow up on this.
            template <typename U, typename A, typename D> friend class shared_ptr;
            template <typename U, typename A>             friend class weak_ptr;
        #endif

        T*             mpValue;              /// The owned pointer.
        ref_count_sp*  mpRefCount;           /// Reference count for owned pointer.
        allocator_type mAllocator;           /// The allocator used to manage new/delete of mpRefCount.

    public:
        typedef T element_type;

        /// shared_ptr
        /// Default constructor.
        shared_ptr(const allocator_type& allocator = EASTL_SHARED_PTR_DEFAULT_ALLOCATOR)
            : mpValue(NULL),
              mpRefCount(NULL),
              mAllocator(allocator)
        {
            // Intentionally leave mpRefCount as NULL.
            // Allocate memory for the reference count.
            void* const pMemory = EASTLAlloc(mAllocator, sizeof(ref_count_sp));
            if(pMemory)
                mpRefCount = new(pMemory) ref_count_sp;
        }


        /// shared_ptr
        /// Takes ownership of the pointer and sets the reference count
        /// to the pointer to 1. It is OK if the input pointer is null.
        /// The shared reference count is allocated on the heap via operator new.
        /// If an exception occurs during the allocation of the shared 
        /// reference count, the owned pointer is deleted and the exception
        /// is rethrown. A null pointer is given a reference count of 1.
        /// To do: Make a version of this function which takes a Deleter.
        template <typename U>
        explicit shared_ptr(U* pValue) // allocator arg removed because VC7.1 fails on the default arg. To do: Make a second version of this function without a default arg.
            : mpValue(pValue),
              mpRefCount(NULL),
              mAllocator(EASTL_SHARED_PTR_DEFAULT_ALLOCATOR)
        {
            // Allocate memory for the reference count.
            typedef ref_count_sp_t<U*, smart_ptr_deleter<U> > ref_count_type;

            void* const pMemory = EASTLAlloc(mAllocator, sizeof(ref_count_type));
            if(pMemory)
                mpRefCount = new(pMemory) ref_count_type(pValue);

            // If pValue happes to be a class that has inherited from the enable_shared_from_this
            // mixin, then this call will set pValue's mWeakPtr (from enable_shared_from_this)
            // to point to this shared_ptr. If pValue happens to not inherit from enable_shared_from_this
            // then another templated implementaion of do_enables_shared_from_this does a no-op.
            do_enable_shared_from_this(mpRefCount, pValue, pValue);
        }


        /// shared_ptr
        /// construction with self type.
        /// If we want a shared_ptr constructor that is templated on shared_ptr<U>,
        /// then we need to make it in addition to this function, as otherwise 
        /// the compiler will generate this function and things will go wrong.
        shared_ptr(const shared_ptr& sharedPtr)
            : mpValue(sharedPtr.mpValue),
              mpRefCount(sharedPtr.mpRefCount),
              mAllocator(sharedPtr.mAllocator)
        {
            ++mpRefCount->mRefCount;
            ++mpRefCount->mWeakRefCount;
        }


        /// shared_ptr
        /// Shares ownership of a pointer with another instance of shared_ptr.
        /// This function increments the shared reference count on the pointer.
        template <typename U, typename A, typename D>
        shared_ptr(const shared_ptr<U, A, D>& sharedPtr)
            : mpValue(sharedPtr.mpValue),
              mpRefCount(sharedPtr.mpRefCount),
              mAllocator(sharedPtr.mAllocator)
        {
            ++mpRefCount->mRefCount;
            ++mpRefCount->mWeakRefCount;
        }


        /// shared_ptr
        /// Shares ownership of a pointer with an instance of weak_ptr.
        /// This function increments the shared reference count on the pointer.
        template <typename U, typename A>
        explicit shared_ptr(const weak_ptr<U, A>& weakPtr)
            : mpValue(weakPtr.mpValue),
              mpRefCount(weakPtr.mpRefCount),
              mAllocator(weakPtr.mAllocator)
        {
            if(mpRefCount)
            {
                ++mpRefCount->mRefCount;
                ++mpRefCount->mWeakRefCount;
            }
            else
            {
                // Question: Do we really need to do this or can we just leave our mpRefCount NULL?
                // Allocate memory for the reference count.
                typedef ref_count_sp_t<T*, smart_ptr_deleter<U> > ref_count_type;

                void* const pMemory = EASTLAlloc(mAllocator, sizeof(ref_count_type));
                if(pMemory)
                    mpRefCount = new(pMemory) ref_count_type(mpValue);
            }
        }


        /// shared_ptr
        /// Constructs a shared_ptr from another shared_ptr whose type is 
        /// converted to this type via static_cast<>.
        template <typename U, typename A, typename D>
        shared_ptr(const shared_ptr<U, A, D>& sharedPtr, static_cast_tag)
            : mpValue(static_cast<T*>(sharedPtr.mpValue)),
              mpRefCount(sharedPtr.mpRefCount),
              mAllocator(sharedPtr.mAllocator)
        {
            ++mpRefCount->mRefCount;
            ++mpRefCount->mWeakRefCount;
        }


        /// shared_ptr
        /// Constructs a shared_ptr from another shared_ptr whose type is 
        /// converted to this type via const_cast<>. Normally, this means that
        /// the source shared_ptr holds a const data type.
        template <typename U, typename A, typename D>
        shared_ptr(const shared_ptr<U, A, D>& sharedPtr, const_cast_tag)
            : mpValue(const_cast<T*>(sharedPtr.mpValue)),
              mpRefCount(sharedPtr.mpRefCount),
              mAllocator(sharedPtr.mAllocator)
        {
            ++mpRefCount->mRefCount;
            ++mpRefCount->mWeakRefCount;
        }


        #if EASTL_RTTI_ENABLED
            /// shared_ptr
            /// Constructs a shared_ptr from another shared_ptr whose type 
            /// is converted to this type via dynamic_cast<>.
            template <typename U, typename A, typename D>
            shared_ptr(const shared_ptr<U, A, D>& sharedPtr, dynamic_cast_tag)
                : mpValue(dynamic_cast<T*>(sharedPtr.mpValue)),
                  mpRefCount(sharedPtr.mpRefCount),
                  mAllocator(sharedPtr.mAllocator)
            {
                if(mpValue) // If the dynamic_cast succeeded...
                {
                    ++mpRefCount->mRefCount;
                    ++mpRefCount->mWeakRefCount;
                }
                else
                {
                    typedef ref_count_sp_t<U*, smart_ptr_deleter<U> > ref_count_type;

                    void* const pMemory = EASTLAlloc(mAllocator, sizeof(ref_count_type));
                    if(pMemory)
                        mpRefCount = new(pMemory) ref_count_type(mpValue);
                }
            }
        #endif


        /// ~shared_ptr
        /// Decrements the reference count for the owned pointer. If the 
        /// reference count goes to zero, the owned pointer is deleted and
        /// the shared reference count is deleted.
        ~shared_ptr()
        {
            const int newRefCount(--mpRefCount->mRefCount);

            if(newRefCount > 0)
                --mpRefCount->mWeakRefCount;
            else
            {
                if(mpRefCount->mbCustomDispose)
                    mpRefCount->dispose(); // mpRefCount is of type ref_count_sp_t and has a copy of mpValue but knows it as its original type.
                else
                {
                    deleter_type del;

                    #if defined(__GNUC__) && (__GNUC__ <= 2) // Having a hard time coming up with something all compilers like.
                        del(const_cast<deletion_type*>(static_cast<deletion_type*>(mpValue))); // GCC 3 fails on this line with an error that currently makes no sense to me (Paul Pedriana).
                    #else
                        del(static_cast<const deletion_type*>(mpValue));
                    #endif
                }

                if(--mpRefCount->mWeakRefCount == 0)
                {
                    // Note: We happen to know that mpRefCount refers to a subclass if 
                    // mbCustomDispose is true and that mpRefCount refers to a POD otherwise.
                    // Thus we can avoid a virtual destructor call if we check what type
                    // of mpRefCount object we have. In a debug build, always call the destructor. 
                    // This may appease code analysis tools or possibly prevent compiler warnings.

                    #if EASTL_DEBUG
                        mpRefCount->~ref_count_sp();
                    #else
                        if(mpRefCount->mbCustomDispose)
                            mpRefCount->~ref_count_sp();
                    #endif

                    EASTLFree(mAllocator, mpRefCount, (size_t)mpRefCount->mnSize);
                }
            }
        }


        /// operator=
        /// Assignment to self type.
        /// If we want a shared_ptr operator= that is templated on shared_ptr<U>,
        /// then we need to make it in addition to this function, as otherwise 
        /// the compiler will generate this function and things will go wrong.
        shared_ptr& operator=(const shared_ptr& sharedPtr)
        {
            if(mpValue != sharedPtr.mpValue)
            {
                // The easiest thing to do is to create a temporary and 
                // copy ourselves ourselves into it. This is a standard 
                // method for switching pointer ownership in systems like this.
                shared_ptr(sharedPtr).swap(*this);
            }
            return *this;
        }


        /// operator=
        /// Copies another shared_ptr to this object. Note that this object
        /// may already own a shared pointer with another different pointer
        /// (but still of the same type) before this call. In that case,
        /// this function releases the old pointer, decrementing its reference
        /// count and deleting it if zero, takes shared ownership of the new 
        /// pointer and increments its reference count.
        template <typename U, typename A, typename D>
        shared_ptr& operator=(const shared_ptr<U, A, D>& sharedPtr)
        {
            if(mpValue != sharedPtr.mpValue)
            {
                // The easiest thing to do is to create a temporary and 
                // copy ourselves ourselves into it. This is a standard 
                // method for switching pointer ownership in systems like this.
                shared_ptr(sharedPtr).swap(*this);
            }
            return *this;
        }


        /// operator=
        /// Assigns a new pointer, while decrementing the reference count on
        /// the current pointer. The new pointer can be NULL and the current
        /// pointer can NULL. If the new pointer is equivalent to the current
        /// pointer, then nothing is done.
        template <typename U>
        shared_ptr& operator=(U* pValue)
        {
            reset(pValue);
            return *this;
        }


        /// reset
        /// Releases the owned pointer and takes ownership of the 
        /// passed in pointer. If the passed in pointer is the same
        /// as the owned pointer, nothing is done. The passed in pointer
        /// can be null, in which case the use count is set to 1.
        /// To do: Make a version of this function which takes a Deleter.
        template <typename U>
        void reset(U* pValue)
        {
            if(pValue != mpValue)
            {
                // The easiest thing to do is to create a temporary and 
                // copy ourselves ourselves into it. This is a standard 
                // method for switching pointer ownership in systems like this.
                // We cannot simply set mpValue to pValue and reset the 
                // use count to zero unless the reference count is 1.
                shared_ptr(pValue).swap(*this);
            }
        }


        /// reset
        /// Resets the container with NULL.
        void reset()
        {
            reset((T*)NULL);
        }


        /// swap
        /// Exchanges the owned pointer beween two shared_ptr objects.
        void swap(this_type& sharedPtr)
        {
            // We leave mAllocator and as-is.

            T* const pValue   = sharedPtr.mpValue;
            sharedPtr.mpValue = mpValue;
            mpValue           = pValue;

            ref_count_sp* const pRefCount = sharedPtr.mpRefCount;
            sharedPtr.mpRefCount = mpRefCount;
            mpRefCount           = pRefCount;
        }


        /// operator*
        /// Returns the owner pointer dereferenced.
        /// Example usage:
        ///    shared_ptr<int> ptr = new int(3);
        ///    int x = *ptr;
        reference_type operator*() const
        {
            // assert(mpValue);
            return *mpValue;
        }

        /// operator->
        /// Allows access to the owned pointer via operator->()
        /// Example usage:
        ///    struct X{ void DoSomething(); }; 
        ///    shared_ptr<int> ptr = new X;
        ///    ptr->DoSomething();
        T* operator->() const
        {
            // assert(mpValue);
            return mpValue;
        }

        /// get
        /// Returns the owned pointer. Note that this class does 
        /// not provide an operator T() function. This is because such
        /// a thing (automatic conversion) is deemed unsafe.
        /// Example usage:
        ///    struct X{ void DoSomething(); }; 
        ///    shared_ptr<int> ptr = new X;
        ///    X* pX = ptr.get();
        ///    pX->DoSomething();
        T* get() const
        {
            return mpValue;
        }

        /// use_count
        /// Returns the reference count on the owned pointer.
        /// The return value is one if the owned pointer is null.
        int use_count() const
        {
            // assert(mpRefCount);
            return mpRefCount->mRefCount;
        }

        /// unique
        /// Returns true if the reference count on the owned pointer is one.
        /// The return value is true if the owned pointer is null.
        bool unique() const
        {
            // assert(mpRefCount);
            return (mpRefCount->mRefCount == 1);
        }

        /// Implicit operator bool
        /// Allows for using a scoped_ptr as a boolean. 
        /// Example usage:
        ///    shared_ptr<int> ptr = new int(3);
        ///    if(ptr)
        ///        ++*ptr;
        ///     
        /// Note that below we do not use operator bool(). The reason for this
        /// is that booleans automatically convert up to short, int, float, etc.
        /// The result is that this: if(sharedPtr == 1) would yield true (bad).
        typedef T* (this_type::*bool_)() const;
        operator bool_() const
        {
            if(mpValue)
                return &this_type::get;
            return NULL;
        }

        /// operator!
        /// This returns the opposite of operator bool; it returns true if 
        /// the owned pointer is null. Some compilers require this and some don't.
        ///    shared_ptr<int> ptr = new int(3);
        ///    if(!ptr)
        ///        assert(false);
        bool operator!() const
        {
            return (mpValue == NULL);
        }

        /// get_allocator
        /// Returns the memory allocator associated with this class.
        allocator_type& get_allocator()
        {
            return mAllocator;
        }

        /// set_allocator
        /// Sets the memory allocator associated with this class.
        void set_allocator(const allocator_type& allocator)
        {
            mAllocator = allocator;
        }

    }; // class shared_ptr


    /// get_pointer
    /// returns shared_ptr::get() via the input shared_ptr. 
    template <typename T, typename A, typename D>
    inline T* get_pointer(const shared_ptr<T, A, D>& sharedPtr)
    {
        return sharedPtr.get();
    }

    /// swap
    /// Exchanges the owned pointer beween two shared_ptr objects.
    /// This non-member version is useful for compatibility of shared_ptr
    /// objects with the C++ Standard Library and other libraries.
    template <typename T, typename A, typename D>
    inline void swap(shared_ptr<T, A, D>& sharedPtr1, shared_ptr<T, A, D>& sharedPtr2)
    {
        sharedPtr1.swap(sharedPtr2);
    }


    /// operator!=
    /// Compares two shared_ptr objects for equality. Equality is defined as 
    /// being true when the pointer shared between two shared_ptr objects is equal.
    /// It is debatable what the appropriate definition of equality is between two
    /// shared_ptr objects, but we follow the current 2nd generation C++ standard proposal.
    template <typename T, typename TA, typename TD, typename U, typename UA, typename UD> 
    inline bool operator==(const shared_ptr<T, TA, TD>& sharedPtr1, const shared_ptr<U, UA, UD>& sharedPtr2)
    {
        // assert((sharedPtr1.get() != sharedPtr2.get()) || (sharedPtr1.use_count() == sharedPtr2.use_count()));
        return (sharedPtr1.get() == sharedPtr2.get());
    }


    /// operator!=
    /// Compares two shared_ptr objects for inequality. Equality is defined as 
    /// being true when the pointer shared between two shared_ptr objects is equal.
    /// It is debatable what the appropriate definition of equality is between two
    /// shared_ptr objects, but we follow the current 2nd generation C++ standard proposal.
    template <typename T, typename TA, typename TD, typename U, typename UA, typename UD> 
    inline bool operator!=(const shared_ptr<T, TA, TD>& sharedPtr1, const shared_ptr<U, UA, UD>& sharedPtr2)
    {
        // assert((sharedPtr1.get() != sharedPtr2.get()) || (sharedPtr1.use_count() == sharedPtr2.use_count()));
        return (sharedPtr1.get() != sharedPtr2.get());
    }


    /// operator<
    /// Returns which shared_ptr is 'less' than the other. Useful when storing
    /// sorted containers of shared_ptr objects.
    template <typename T, typename TA, typename TD, typename U, typename UA, typename UD> 
    inline bool operator<(const shared_ptr<T, TA, TD>& sharedPtr1, const shared_ptr<U, UA, UD>& sharedPtr2)
    {
        return (sharedPtr1.get() < sharedPtr2.get()); // Alternatively use the functor: less<T*>(sharedPtr1.get(), sharedPtr2.get());
    }


    /// static_pointer_cast
    /// Returns a shared_ptr<T> static-casted from a shared_ptr<U>.
    template <typename T, typename TA, typename TD, typename U, typename UA, typename UD> 
    shared_ptr<T, TA, TD> static_shared_pointer_cast(const shared_ptr<U, UA, UD>& sharedPtr)
    {
        return shared_ptr<T, TA, TD>(sharedPtr, static_cast_tag());
    }

    /// static_pointer_cast
    /// Returns a shared_ptr<T> static-casted from a shared_ptr<U>.
    template <typename T, typename U> 
    shared_ptr<T, EASTLAllocatorType, smart_ptr_deleter<T> >
    static_pointer_cast(const shared_ptr<U>& sharedPtr)
    {
        return shared_ptr<T, EASTLAllocatorType, smart_ptr_deleter<T> >(sharedPtr, static_cast_tag());
    }


    /// const_pointer_cast
    /// Returns a shared_ptr<T> const-casted from a const shared_ptr<U>.
    template <typename T, typename TA, typename TD, typename U, typename UA, typename UD> 
    shared_ptr<T, TA, TD> const_shared_pointer_cast(const shared_ptr<U, UA, UD>& sharedPtr)
    {
        return shared_ptr<T, TA, TD>(sharedPtr, const_cast_tag());
    }

    /// const_pointer_cast
    /// Returns a shared_ptr<T> const-casted from a const shared_ptr<U>.
    template <typename T, typename U> 
    shared_ptr<T, EASTLAllocatorType, smart_ptr_deleter<T> >
    const_pointer_cast(const shared_ptr<U>& sharedPtr)
    {
        return shared_ptr<T, EASTLAllocatorType, smart_ptr_deleter<T> >(sharedPtr, const_cast_tag());
    }


    /// dynamic_pointer_cast
    /// Returns a shared_ptr<T> dynamic-casted from a const shared_ptr<U>.
    template <typename T, typename TA, typename TD, typename U, typename UA, typename UD> 
    shared_ptr<T, TA, TD> dynamic_shared_pointer_cast(const shared_ptr<U, UA, UD>& sharedPtr)
    {
        return shared_ptr<T, TA, TD>(sharedPtr, dynamic_cast_tag());
    }

    /// dynamic_pointer_cast
    /// Returns a shared_ptr<T> dynamic-casted from a const shared_ptr<U>.
    template <typename T, typename U> 
    shared_ptr<T, EASTLAllocatorType, smart_ptr_deleter<T> >
    dynamic_pointer_cast(const shared_ptr<U>& sharedPtr)
    {
        return shared_ptr<T, EASTLAllocatorType, smart_ptr_deleter<T> >(sharedPtr, dynamic_cast_tag());
    }


} // namespace eastl


// We have to either #include weak_ptr.h here or we need to move the weak_ptr source code to here.
#include <EASTL/weak_ptr.h>


#endif // Header include guard






















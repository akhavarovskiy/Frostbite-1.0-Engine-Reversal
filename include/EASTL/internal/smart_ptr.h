///////////////////////////////////////////////////////////////////////////////
// EASTL/internal/smart_ptr.h
//
// Copyright (c) 2005, Electronic Arts. All rights reserved.
// Written and maintained by Paul Pedriana.
///////////////////////////////////////////////////////////////////////////////



#ifndef EASTL_INTERNAL_SMART_PTR_H
#define EASTL_INTERNAL_SMART_PTR_H



namespace eastl
{

    /// static_cast_tag
    /// This is used like iterator tags are: to provide an unused function
    /// argument whose sole purpose is to differentiate itself from another
    /// similar function.
    struct static_cast_tag {};

    /// const_cast_tag
    /// See the comments for static_cast_tag.
    struct const_cast_tag {};

    /// dynamic_cast_tag
    /// See the comments for static_cast_tag.
    /// This is only used if exception handling is enabled.
    struct dynamic_cast_tag {};



    /// smart_ptr_deleter
    ///
    /// Provides a default way to delete an object. This default is
    /// simply to call delete on the object pointer. You can override 
    /// this on a class-by-class basis like this:
    ///
    /// template <>
    /// struct smart_ptr_deleter<MyClass>
    /// {
    ///     void operator()(MyClass* p) const
    ///        { SomeCustomFunction(p); }
    /// };
    ///
    template <typename T>
    struct smart_ptr_deleter
    {
        typedef T value_type;

        void operator()(const T* p) const
            { delete p; }
    };

    /// smart_ptr_deleter<void>
    ///
    /// This is the default deleter for void data. It knows how to free memory via operator delete
    /// but it doesn't know how to call the destructor of the object that is really being referred
    /// to. If you are using objects with non-trivial destructors, you need to template your shared_ptr
    /// on a custom deleter class. 
    ///
    template <>
    struct smart_ptr_deleter<void>
    {
        typedef void value_type;

        void operator()(const void* p) const
            { delete[] (char*)p; } // We don't seem to have much choice but to cast to a scalar type.
    };

    template <>
    struct smart_ptr_deleter<const void>
    {
        typedef void value_type;

        void operator()(const void* p) const
            { delete[] (char*)p; } // We don't seem to have much choice but to cast to a scalar type.
    };



    /// smart_array_deleter
    ///
    /// Provides a default way to delete an object array. This default 
    /// is simply to call delete[] on the pointer. You can override 
    /// this on a class-by-class basis like this:
    ///
    /// template <>
    /// struct smart_array_deleter<MyClass>
    /// {
    ///     void operator()(MyClass* p) const
    ///        { SomeCustomFunction(p); }
    /// };
    ///
    template <typename T>
    struct smart_array_deleter
    {
        void operator()(T* p) const
            { delete[] p; }
    };

    template <>
    struct smart_array_deleter<void>
    {
        void operator()(void* p) const
            { delete[] (char*)p; } // We don't seem to have much choice but to cast to a scalar type.
    };


} // namespace eastl


#endif // Header include guard

















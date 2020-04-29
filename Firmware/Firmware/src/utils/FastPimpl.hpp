#pragma once
#include <utility>
#include <type_traits>

// https://www.youtube.com/watch?v=_AkF8SpUV3k&t=994s

namespace Utils
{

template< typename TImplementation, size_t TypeSizeof, size_t Aligment>
class FastPimpl
{

public:

    template<typename... Args>
    explicit FastPimpl( Args&& ... _args )
    {
        new( Ptr() ) TImplementation( std::forward<Args>(_args )... );
    }

    FastPimpl& operator = ( FastPimpl&& _rhs )
    {
        *Ptr() = std::move(*_rhs);
        return *this;
    }

    ~FastPimpl() noexcept
    {
        validate<sizeof(TImplementation), alignof(TImplementation)>();
        Ptr()->~TImplementation();
    }

public:

    TImplementation* operator ->() noexcept{ return Ptr(); }

    const TImplementation* operator ->() const noexcept{ return Ptr(); }

    TImplementation& operator *() noexcept{ return *Ptr(); }

    const TImplementation& operator *() const noexcept{ return *Ptr(); }

private:

    TImplementation* Ptr() noexcept
    {
        return reinterpret_cast<TImplementation*>( &m_pAlignedStorage );
    }

    const TImplementation* Ptr()const noexcept
    {
        return reinterpret_cast<const TImplementation*>( &m_pAlignedStorage );
    }

    template< std::size_t ActualSize, std::size_t ActualAligment >
    static void validate() noexcept
    {
        static_assert( ActualSize == TypeSizeof ,"Size and sizeof(TImplementation) mismatch" );
        static_assert( Aligment == ActualAligment,"Aligment and alignof(ActualAligment) mismatch" );
    }

private:

    std::aligned_storage<TypeSizeof,Aligment> m_pAlignedStorage;
};


}
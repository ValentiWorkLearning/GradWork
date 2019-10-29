#pragma once

#include <array>
#include <utility>

namespace Meta
{

template<typename TArray, std::size_t... Index>
constexpr auto revreseImpl(const TArray& a, std::size_t _arraySize , std::index_sequence<Index...>)
{
    return std::array{a[_arraySize - Index - 1]...};
}
 
template<typename TItem, std::size_t N, typename Indexes = std::make_index_sequence<N>>
constexpr auto reverseArray( const std::array<TItem,N>& _array )
{
    return revreseImpl( _array,N,Indexes{} );
}

};
#pragma once

#include <array>
#include <utility>
#include <tuple>
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

template<typename Callable, typename Tuple, std::size_t... Is >
constexpr auto tupleApplyImpl( Callable&& _toCall, const Tuple& _tuple, std::index_sequence<Is...> )
{
    return (_toCall( std::get<Is>( _tuple ) ), ...);
}
template<typename Callable, typename ... ArgsList >
constexpr auto tupleApply( Callable&& _toCall , const std::tuple<ArgsList...>& _tuple )
{
    return tupleApplyImpl( std::forward<Callable>( _toCall ), _tuple, std::index_sequence_for<ArgsList...>{} );
}

};
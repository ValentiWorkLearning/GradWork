#pragma once

#include <array>
#include <utility>
#include <tuple>
#include <utility>
#include <memory>
#include <functional>

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

template <auto DeleterFunction>
using CustomDeleter = std::integral_constant<decltype(DeleterFunction), DeleterFunction>;

template <typename ManagedType, auto Functor>
using PointerWrapper = std::unique_ptr<ManagedType, CustomDeleter<Functor>>;

template<typename Unused>
constexpr void UnuseVar(Unused && _toUnuse)
{
    static_cast<void>( _toUnuse );
}

template <typename ... Types>
struct TypeList;

template<typename H, typename ... T>
struct TypeList<H,T ...>
{
    using Head = H;
    using Tail = TypeList<T...>;
};

template<>
struct TypeList<>
{
};

template<typename ToDetect, typename Args >
struct HasType
{
	static int const value = std::is_same_v<ToDetect,typename Args::Head> || HasType<ToDetect, typename Args::Tail >::value;
};

template<typename ToDetect>
struct HasType<ToDetect,TypeList<>>
{
    static const bool value = false;
};


template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...)->overload<Ts...>;

};

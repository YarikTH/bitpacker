#pragma once

#if !defined( BITPACKER_USE_STD_BIT )
#    define BITPACKER_USE_STD_BIT __has_include( <bit> ) && __cplusplus >= 202002L
#endif

#if BITPACKER_USE_STD_BIT
#    include <bit>
#endif

#define BITPACKER_VERSION_MAJOR 0
#define BITPACKER_VERSION_MINOR 1
#define BITPACKER_VERSION_PATCH 0
#define BITPACKER_VERSION_STR "0.1.0"

#define BITPACKER_VERSION                                                                          \
    ( BITPACKER_VERSION_MAJOR * 10000 + BITPACKER_VERSION_MINOR * 100 + BITPACKER_VERSION_PATCH )

namespace bitpacker
{

#if BITPACKER_USE_STD_BIT

using std::bit_width;

#else

template <class V, std::enable_if_t<std::is_unsigned_v<V>, int> = 0>
[[nodiscard]] constexpr V bit_width( const V value ) noexcept
{
    V result = 0u;
    V temp = value;
    while( temp != 0u )
    {
        ++result;
        temp >>= static_cast<V>( 1u );
    }
    return result;
}

#endif

/// Return unsigned difference between two integers
/// Left hand side value should be greater or equal than right hand side value
template <typename V, class UnsignedV = typename std::make_unsigned<V>::type>
[[nodiscard]] constexpr UnsignedV integral_unsigned_difference( const V lhs, const V rhs )
{
    return static_cast<UnsignedV>( lhs ) - static_cast<UnsignedV>( rhs );
}

/// Calculate delta for integral values with given range
template <typename V, class UnsignedV = typename std::make_unsigned<V>::type>
[[nodiscard]] constexpr UnsignedV integral_delta( const V min_value, const V max_value )
{
    return integral_unsigned_difference( max_value, min_value );
}

/// Calculate delta for integral values without limits
template <typename V, class UnsignedV = typename std::make_unsigned<V>::type>
[[nodiscard]] constexpr UnsignedV integral_delta()
{
    const auto min_value = std::numeric_limits<V>::min();
    const auto max_value = std::numeric_limits<V>::max();
    return integral_delta( min_value, max_value );
}

} // namespace bitpacker

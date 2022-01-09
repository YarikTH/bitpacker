#pragma once

#if !defined( BITPACKER_USE_STD_BIT )
#    define BITPACKER_USE_STD_BIT __has_include( <bit> )
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

template <class T, std::enable_if_t<std::is_unsigned_v<T>, int> = 0>
[[nodiscard]] constexpr T bit_width( const T value ) noexcept
{
    T result = 0u;
    T temp = value;
    while( temp != 0u )
    {
        ++result;
        temp >>= static_cast<T>( 1u );
    }
    return result;
}

#endif

} // namespace bitpacker

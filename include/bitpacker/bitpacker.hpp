#pragma once

#include <array>
#include <bitset>

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

template <class ContainerT>
class bit_ostream
{
public:
    constexpr explicit bit_ostream( ContainerT& data )
        : m_data( data )
    {}

    constexpr bit_ostream& operator<<( const bool value )
    {
        // TODO: add constexpr friendly check for this case
        //assert( m_offset < m_data.size() );
        m_data[m_offset++] = value;
        return *this;
    }

    [[nodiscard]] constexpr size_t offset() const
    {
        return m_offset;
    }

private:
    ContainerT& m_data;
    size_t m_offset = 0;
};

template <class ContainerT>
class bit_istream
{
public:
    constexpr explicit bit_istream( ContainerT& data )
        : m_data( data )
    {}

    constexpr bit_istream& operator>>( bool& value )
    {
        // TODO: add constexpr friendly check for this case
        //assert( m_offset < m_data.size() );
        value = m_data[m_offset++];
        return *this;
    }

    [[nodiscard]] constexpr size_t offset() const
    {
        return m_offset;
    }

private:
    ContainerT& m_data;
    size_t m_offset = 0;
};

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

// Pack normalized value in range from 0 to delta
template <typename V, typename OutputBitStreamT>
constexpr void pack_normalized_value( OutputBitStreamT& obstream, const V value, const V delta )
{
    static_assert( std::is_unsigned_v<V> );
    auto temp = value;
    constexpr auto ONE = static_cast<V>( 1 );
    for( size_t i = 0, ie = bit_width( delta ); i < ie; ++i )
    {
        const bool bit = temp & ONE;
        obstream << bit;
        temp >>= ONE;
    }
}

template <typename V, typename InputBitStreamT>
constexpr V unpack_normalized_value( InputBitStreamT& ibstream, const V delta )
{
    V value{};
    constexpr auto ONE = static_cast<V>( 1 );
    for( size_t i = 0, ie = bit_width( delta ); i < ie; ++i )
    {
        bool bit;
        ibstream >> bit;
        if( bit )
        {
            value |= ( ONE << i );
        }
    }
    return value;
}

} // namespace bitpacker

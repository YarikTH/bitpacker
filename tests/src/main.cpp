#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include "bitpacker/bitpacker.hpp"

static_assert( bitpacker::bit_width( 3u ) );
static_assert( bitpacker::bit_width( 4u ) );
static_assert( bitpacker::bit_width( std::numeric_limits<unsigned char>::max() )
               == std::numeric_limits<unsigned char>::digits );
static_assert( bitpacker::bit_width( std::numeric_limits<std::uint64_t>::max() )
               == std::numeric_limits<std::uint64_t>::digits );

TEST_CASE( "bit_width" )
{
    CHECK( bitpacker::bit_width( 3u ) == 2 );
    CHECK( bitpacker::bit_width( 4u ) == 3 );
    CHECK( bitpacker::bit_width( std::numeric_limits<unsigned char>::max() )
           == std::numeric_limits<unsigned char>::digits );
    CHECK( bitpacker::bit_width( std::numeric_limits<std::uint64_t>::max() )
           == std::numeric_limits<std::uint64_t>::digits );
}

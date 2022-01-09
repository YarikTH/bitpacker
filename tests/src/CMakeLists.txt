add_executable(bitpacker_test main.cpp)

target_include_directories(bitpacker_test PRIVATE include)

target_link_libraries(
    bitpacker_test
    PRIVATE bitpacker::bitpacker bitpacker::doctest
)

target_compile_options(bitpacker_test PRIVATE ${BITPACKER_WARNING_OPTION})

add_test(NAME bitpacker_test COMMAND bitpacker_test)

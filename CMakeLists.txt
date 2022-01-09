cmake_minimum_required(VERSION 3.8)

################################################################################
## BITPACKER
################################################################################

# Get version from bitpacker.hpp
file(
    READ
        ${CMAKE_CURRENT_SOURCE_DIR}/include/bitpacker/bitpacker.hpp
        bitpacker_hpp
)
if(
    NOT
        bitpacker_hpp
            MATCHES
            "BITPACKER_VERSION_STR \"([0-9]+).([0-9]+).([0-9]+)\""
)
    message(FATAL_ERROR "Cannot get BITPACKER_VERSION from bitpacker.hpp.")
endif()
# Use math to skip leading zeros if any.
math(EXPR BITPACKER_VERSION_MAJOR ${CMAKE_MATCH_1})
math(EXPR BITPACKER_VERSION_MINOR ${CMAKE_MATCH_2})
math(EXPR BITPACKER_VERSION_PATCH ${CMAKE_MATCH_3})
set(BITPACKER_VERSION
    ${BITPACKER_VERSION_MAJOR}.${BITPACKER_VERSION_MINOR}.${BITPACKER_VERSION_PATCH}
)

project(bitpacker VERSION ${BITPACKER_VERSION} LANGUAGES CXX)

# Determine if bitpacker is built as a subproject (using add_subdirectory)
# or if it is the master project.
if(NOT DEFINED BITPACKER_MASTER_PROJECT)
    set(BITPACKER_MASTER_PROJECT OFF)
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(BITPACKER_MASTER_PROJECT ON)
        message(STATUS "CMake version: ${CMAKE_VERSION}")
    endif()
endif()

# Options that control generation of various targets.
option(BITPACKER_PEDANTIC "Enable extra warnings and expensive tests." OFF)
option(
    BITPACKER_WERROR
    "Halt the compilation with an error on compiler warnings."
    OFF
)
option(BITPACKER_TEST "Generate the test target." ${BITPACKER_MASTER_PROJECT})
option(BITPACKER_СTEST "Generate the CTest targets for CI." n)

message(STATUS "bitpacker version: ${BITPACKER_VERSION}")

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/support/cmake")

include(set_warning_flags)

set(BITPACKER_WARNING_OPTION)

if(BITPACKER_PEDANTIC)
    set_warning_flags(BITPACKER_WARNING_OPTION)
endif()

if(BITPACKER_WERROR)
    set_werror_flag(BITPACKER_WARNING_OPTION)
endif()
message(
    STATUS
    "bitpacker compiler warning options: \"${BITPACKER_WARNING_OPTION}\""
)

### bitpacker
add_library(${PROJECT_NAME} INTERFACE)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
if(MSVC)
    # See https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/
    target_compile_options(${PROJECT_NAME} INTERFACE "/Zc:__cplusplus")
endif()

################################################################################
## TESTS/EXAMPLES/HELPERS
################################################################################

if(BITPACKER_TEST)
    if(BITPACKER_СTEST)
        include(CTest)
    else()
        enable_testing()
    endif()
    add_subdirectory(tests)
endif()

add_library(BitpackerDoctest INTERFACE)
target_include_directories(BitpackerDoctest SYSTEM INTERFACE include)
add_library(bitpacker::doctest ALIAS BitpackerDoctest)

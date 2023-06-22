cmake_minimum_required(VERSION 3.18)
project(clien_TCP LANGUAGES CXX C)

add_executable(client_TCP main.cpp)
add_library(lib STATIC client_TCP.cpp client_TCP.hpp)

set_source_files_properties(lib
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)

set_target_properties(client_TCP
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)

target_link_libraries(client_TCP lib)

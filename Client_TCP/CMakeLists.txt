cmake_minimum_required(VERSION 3.18)
project(clien_TCP LANGUAGES CXX C)

add_executable(client main.cpp)
add_library(lib STATIC client.cpp client.hpp transmitter.cpp transmitter.hpp)

set_source_files_properties(lib
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)

set_target_properties(client
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)

target_link_libraries(client lib)

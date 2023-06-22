cmake_minimum_required(VERSION 3.18)
project(Server_TCP LANGUAGES CXX C)

add_executable(Server_TCP main.cpp)

add_library(lib STATIC server_TCP.cpp user.cpp virtual_client.cpp server_TCP.hpp user.hpp virtual_client.hpp)

set_target_properties(lib
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)

set_target_properties(Server_TCP
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)

link_libraries(Server_TCP lib)
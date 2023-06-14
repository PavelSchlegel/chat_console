cmake_minimum_required(VERSION 3.18)
project(chat_console LANGUAGES CXX C)

add_executable(chat_console main.cpp client.cpp user.cpp functions.cpp)
set_target_properties(chat_console
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)         
#ifndef FUNCTIONS
#define FUNCTIONS
#include "include.hpp"
#include "server.hpp"

bool is_Up (char a);
bool is_Low (char a);
bool is_Digit(char a);
std::string get_nickname();
std::size_t get_new_pass();
std::size_t get_pass();

void control(Client* client);
#endif
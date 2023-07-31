#ifndef CLIENT
#define CLIENT

#include <iostream>
#include "transmitter.hpp"

class Client {

private:
    Transmitter  m_tr;

public:
    void test();
    void new_user();
    void login();
    void send_to();
    void quit();
};
#endif
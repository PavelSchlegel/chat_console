#ifndef CLIENT
#define CLIENT

#include <iostream>
#include "user.hpp"

class Server;

class Client {

private:

    Server *m_server;
    //ключт состояний
    std::size_t m_connect_key;
    std::size_t m_login_key;
    std::size_t m_gchat_key;
    
    void new_message();
    void message_accept(Message&& message);
    void message_accept(const Message& message);

public:

    Client();
    ~Client();
    void connect(Server* server);
    void disconnection();
    void control();
    friend class Server;
};
#endif
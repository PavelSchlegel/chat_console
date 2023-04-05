#ifndef CLIENT
#define CLIENT

#include <iostream>
#include "user.hpp"

class Server;

class Client {

private:

    User* m_user;
    Server *m_server;
    bool m_chat_pass;
    void new_message();
    void message_accept(Message&& message);
    void message_accept(const Message& message);

public:

    Client();
    ~Client();
    void connect(Server* server);
    void disconnection();
    void control();
    void new_privat_room();
    friend class Server;
    friend class User;
};
#endif
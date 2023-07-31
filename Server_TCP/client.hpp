#pragma once

#include <iostream>
#include "user.hpp"
#include <string.h>
#include <vector>


class Server;
class Receiver;

class Client {

private:

    Receiver* m_tx;
    User* m_user;
    Server *m_server;
    bool m_chat_pass;
    void new_message();
    void message_accept(Message&& message);
    void message_accept(const Message& message);

public:

    Client(Receiver *receiver);
    ~Client();
    void connect(Server* server);
    void disconnect();
    Server* get_s_ptr() noexcept;
    friend class Server;
    friend class User;
};
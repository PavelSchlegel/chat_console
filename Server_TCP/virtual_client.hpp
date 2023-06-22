#pragma once
/*
#ifndef CLIENT
#define CLIENT
*/

#include <iostream>
#include "user.hpp"
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>

#define NEW_USER 1
#define LOGIN 2
#define SEND_TO 3

#define BUF_LENGTH 1024
#define PORT 7777

class Server;

class Client {

private:
  
    struct sockaddr_in serveraddress;
    struct sockaddr_in client;
    socklen_t length;
    int sockert_file_descriptor;
    int connection;
    int bind_status;
    int connection_status;
    char buf[BUF_LENGTH];
    std::size_t buf_index;
    
    User* m_user;
    Server *m_server;
    bool m_chat_pass;
    void new_message();
    void message_accept(Message&& message);
    void message_accept(const Message& message);

public:

    Client();
    ~Client();
    void client_start();
    void data_constructor();
    void disconnect();
    void connect(Server* server);
    Server* get_s_ptr() noexcept;
    friend class Server;
    friend class User;
};
//#endif
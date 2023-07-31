#pragma once
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "client.hpp"

#define BUF_LENGTH 1024
#define PORT 7777

class Server;
enum Command_ID: unsigned char {
    NEW_USER = 0,
    LOGIN = 1,
    SEND_TO = 2,
    TEST = 3,
    EXIT = 4,
    END = 5,
    ERROR = 6
};

class Receiver {

private:

    struct sockaddr_in serveraddress;
    struct sockaddr_in client;
    socklen_t length;
    int sockert_file_descriptor;
    int connection;
    int bind_status;
    int connection_status;
    Client m_client;
    //char buf[BUF_LENGTH];
    //std::size_t buf_index;
    Command_ID read_command_id();
    void start();
    std::string buf_str_read();
    std::string s_read(std::string& str);

public:

    Receiver(Server *server);
    void send_to_client(std::string str);
    Command_ID data_constructor();
};
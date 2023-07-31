#ifndef TRANSMITTER
#define TRANSMITTER

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iomanip>

#define PORT 7777

enum Command_ID: unsigned char {
    NEW_USER = 0,
    LOGIN = 1,
    SEND_TO = 2,
    TEST = 3,
    EXIT = 4,
    END = 5,
    ERROR = 6
};

class Transmitter {
private:

    bool connect_to_server();
    int socket_file_descriptor;
    int connection;
    struct sockaddr_in serveraddress;
    struct sockaddr_in client;

public:
    Transmitter();
    ~Transmitter();
    bool status();
    void send_to_server(std::string send);
    void send_to_server(Command_ID id);
    std::string buf_str_read();
    void test();
};
#endif
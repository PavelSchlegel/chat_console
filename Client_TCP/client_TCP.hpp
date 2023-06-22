#ifndef CLIENT
#define CLIENT

#include <iostream>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <algorithm>
#include <iomanip>

#if defined(__linux__)
#include <sys/utsname.h>
#endif

#define BUF_LENGTH 1024
#define PORT 7777
#define NEW_USER 1
#define LOGIN 2
#define SEND_TO 3

void OS_version();

class Client {

private:

    struct sockaddr_in serveraddress;
    struct sockaddr_in client;
    socklen_t length;
    int socket_file_descriptor;
    int connection;
    int bind_status;
    int connection_status;
    char buf[BUF_LENGTH];
    int buf_index;

public:

    Client();
    ~Client();
    void client_start();
    void data_constructor(const std::string& A, const std::string& B, int caller_identifier);
    void disconnection() noexcept;
    void new_user();
    void login();
    void send_to();
};
#endif
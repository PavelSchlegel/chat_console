#include "transmitter.hpp"
#include <string.h>

Transmitter::Transmitter()
: socket_file_descriptor(-1)
, connection(-1)
{
    connect_to_server();
}

Transmitter::~Transmitter()
{
    send_to_server(END);
    shutdown(socket_file_descriptor, connection);
    close(socket_file_descriptor);
}

bool Transmitter::connect_to_server()
{
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_file_descriptor == -1){
        return false;
    }
 
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if(connection == -1){
        return false;
    }
    return true;
}

bool Transmitter::status() 
{
    if (socket_file_descriptor == -1) {
        std::cout << "soket_file_descriptor is -1." << std::endl;
        return false;
    }
    if (connection == -1) {
        std::cout << "connection is -1." << std::endl;
        return false;
    }
    return true;
}

std::string Transmitter::buf_str_read()
{
    std::string str;
    while(true) {
        char symbol;
        if (read(socket_file_descriptor, &symbol, 1) == 1) {
            if (symbol != '\0') {
                str.push_back(symbol);
            } else {
                break;
            }
        } else {
            break;
        }
    }
    return str;
}

void Transmitter::send_to_server(Command_ID id)
{
    if (status()) {
        ssize_t bytes = write(socket_file_descriptor, &id, 1);
        if(bytes >= 0) {
            if (id == TEST) {
                std::cout << "Command id: Done" << std::endl;
            }
        }
    }
}

void Transmitter::send_to_server(std::string send)
{
    if (status()) {
        send.push_back('\0');
        ssize_t bytes = write(socket_file_descriptor, send.data(), send.size());
        if (send == "Client_TEST\0") {
            if(bytes >= 0) {
                std::cout << "Message: Done" << std::endl;
            }
        }
    }
}

void Transmitter::test() 
{
    if (status()) {
        send_to_server(TEST);
        send_to_server("Client_TEST");
    }
}
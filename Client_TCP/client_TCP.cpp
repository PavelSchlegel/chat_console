#include "client_TCP.hpp"

void OS_version() {
    #if defined(__linux__)
        struct utsname utsname;
        uname(&utsname);
        std::cout << "OS name: " << utsname.sysname << std::endl;
        //std::cout << "OS version: " << utsname.version << std::endl;
    #endif
}

std::string get_nick() {
    std::cout << "Enter you nickname:" << std::endl;
    std::string nick;
    std::getline(std::cin, nick);
    return nick;
}

std::string get_pass() {
    std::cout << "Enter you password:" << std::endl;
    std::string pass;
    std::getline(std::cin, pass);
    std::size_t hash = std::hash<std::string>{}(pass);
    std::string hash_return = std::to_string(hash);
    return hash_return;
}

std::string get_message() {
    std::cout << "Enter you message:" << std::endl;
    std::string message;
    std::getline(std::cin, message);
    return message;
}

Client::Client()
: socket_file_descriptor(-1)
, connection(-1)
, bind_status(-1)
, connection_status(-1)
, buf_index(0) {

}

Client::~Client() {

}

void Client::client_start() {
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_file_descriptor == -1){
        throw std::runtime_error ("Creation of Socket failed!");
    }
 
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if(connection == -1){
        throw std::runtime_error ("Connection with the server failed!");
    }
}

void Client::data_constructor(const std::string &A, const std::string &B, int caller_identifier) {
    bzero(buf, sizeof(buf));
    buf_index = 0;
    std::vector<std::string> construnctor;
    if (caller_identifier == LOGIN) {
        construnctor.push_back({"SEND_TO"});
    }
    if (caller_identifier == LOGIN) {
        construnctor.push_back({"LOGIN"});
    }
    if (caller_identifier == NEW_USER) {
        construnctor.push_back({"NEW_USER"});
    }
        construnctor.push_back(A);
        construnctor.push_back(B);
        for (std::size_t i = 0; i < construnctor.size(); ++i) {
        for (std::size_t j = 0; j < construnctor[i].size(); ++j, ++buf_index) {
            buf[buf_index] = construnctor[i][j];
        }
        buf[buf_index] = 42;
        ++buf_index;
        }
        ssize_t bytes = write(socket_file_descriptor, buf, sizeof(buf));
        if(bytes >= 0){
        std::cout << "Data send to the server ok!" << std::endl;
        }
    /*
    bzero(message, sizeof(message));
    // Ждем ответа от сервера
    read(socket_file_descriptor, message, sizeof(message));
    std::cout << "Data received from server: " << message << std::endl;
    */
}

void Client::disconnection() noexcept {
    close(socket_file_descriptor);
}

void Client::new_user() {
    std::string nick {get_nick()};
    std::string pass {get_pass()};
    data_constructor(nick, pass, NEW_USER);
}

void Client::send_to() {
    std::string nick {get_nick()};
    std::string message {get_message()};
    data_constructor(nick, message, SEND_TO);
}

void Client::login() {
    std::string nick {get_nick()};
    std::string pass {get_pass()};
    data_constructor(nick, pass, LOGIN);
}
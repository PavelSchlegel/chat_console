#include "server_TCP.hpp"

Client::Client()
: m_user(nullptr)
, m_server(nullptr)
, m_chat_pass(false)
, sockert_file_descriptor(-1)
, connection(-1)
, bind_status(-1)
, connection_status(-1)
, buf_index(0)
{

}

Client::~Client() {

}

void Client::client_start() {
    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(sockert_file_descriptor == -1){
        throw std::runtime_error ("Socket creation failed.!");
    }
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;
    bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress,
    sizeof(serveraddress));
    if(bind_status == -1)  {
        throw std::runtime_error ("Socket binding failed.!");
    }
    connection_status = listen(sockert_file_descriptor, 5);
    if(connection_status == -1){
        throw std::runtime_error ("Socket is unable to listen for new connections.!");
    } else {
        std::cout << "Server is listening for new connection: " << std::endl;
    }

    length = sizeof(client);
    connection = accept(sockert_file_descriptor,(struct sockaddr*)&client, &length);
    if(connection == -1)  {
        throw std::runtime_error ("Server is unable to accept the data from client.!");
    }
}

void Client::data_constructor() {
    bzero(buf, BUF_LENGTH);
    buf_index = 0;
    read(connection, buf, sizeof(buf));
    std::vector<std::string> constructor;
    std::string command;
    for (std::size_t i = buf_index; i < BUF_LENGTH; ++i) {
        if (buf[i] == 42) {
            break;
        }
        command.push_back(buf[i]);
        ++buf_index;
    }
    if (command == "NEW_USER" || command == "LOGIN") {
        std::string nick;
        std::string pass_hash;
        for (std::size_t i = buf_index; i < BUF_LENGTH; ++i){
            if (buf[i] == 42) {
                break;
            }
            nick.push_back(buf[i]);
            ++buf_index;
        }
        for (std::size_t i = buf_index; i < BUF_LENGTH; ++i){
            if (buf[i] == 42) {
                break;
            }
            pass_hash.push_back(buf[i]);
            ++buf_index;
        }
        if (command == "NEW_USER") {
            try {
                std::size_t hash = std::stoi(pass_hash);
                m_server->new_user(this, nick, hash);
            } catch (std::runtime_error error) {
                bzero(buf, BUF_LENGTH);
                buf_index = 0;
                std::string fail {error.what()};
                for (std::size_t i = 0; i < fail.size(); ++i) {
                    buf[i] = fail[i];
                    ++buf_index;
                }
                buf[buf_index] = 42;
                ssize_t bytes = write(connection, buf, sizeof(buf));
            }
        }
        if (command == "LOGIN") {
            try {
                std::size_t hash = std::stoi(pass_hash);
                m_server->login(this, nick, hash);
            } catch (std::runtime_error error) {
                bzero(buf, BUF_LENGTH);
                buf_index = 0;
                std::string fail {error.what()};
                for (std::size_t i = 0; i < fail.size(); ++i) {
                    buf[i] = fail[i];
                    ++buf_index;
                }
                buf[buf_index] = 42;
                ssize_t bytes = write(connection, buf, sizeof(buf));
            }
            
        }
    }
    if (command == "SEND_TO") {
        
    }
    if (command == "TEST") {
        std::cout << "Connect from Client is ok!" << std::endl;
        bzero(buf, BUF_LENGTH);
        buf_index = 0;
        std::string test {"TEST_FROM_SERVER"};
        for (std::size_t i = 0; i < test.size(); ++i) {
            buf[i] = test[i];
            ++buf_index;
        }
        buf[buf_index] = 42;
        ssize_t bytes = write(connection, buf, sizeof(buf));
    }
    /*
        if (strncmp("end", buf, 3) == 0) {
            std::cout << "Client Exited." << std::endl;
            cout << "Server is Exiting..!" << endl;
            break;
        }
    std::cout << "Data received from client: " <<  buf << std::endl;
    bzero(buf, BUF_LENGTH);
    std::cout << "Enter the buf you want to send to the client: " << std::endl;
    std::cin >> buf;
    ssize_t bytes = write(connection, buf, sizeof(buf));
    // Если передали >= 0  байт, значит пересылка прошла успешно
    if(bytes >= 0)  {
        std::cout << "Data successfully sent to the client.!" << std::endl;
    }
    */
}


void Client::connect(Server* server) {
    m_server = server;
    m_server->connect(this);
}

void Client::disconnect() {
    m_server->disconnection(this);
}

void Client::new_message() {
    std::cout << "\033[31mYou have new message!\033[37m" << std::endl;
}

void Client::message_accept(Message&& message) {
    std::cout << message.who << ":" << std::endl;
    std::cout << message.message << std::endl;
}

void Client::message_accept(const Message& message) {
    std::cout << "\033[31mGeneral:\033[37m" << std::endl;
    std::cout << message.who << ":" << std::endl;
    std::cout << message.message << std::endl;
}

Server* Client::get_s_ptr() noexcept {
    return m_server;
}
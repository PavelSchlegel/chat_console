#include "headers/server.hpp"

Client::Client()
: m_user(nullptr)
, m_server(nullptr)
, m_chat_pass(false)
{

}

Client::~Client() {

}

void Client::connect(Server* server) {
    m_server = server;
    m_server->connect(this);
}

void Client::disconnection() {
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
void Client::login(const std::string& nick, std::size_t hash) {
    m_server->login(this, nick, hash);
}
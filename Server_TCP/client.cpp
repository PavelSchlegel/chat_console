#include "server_TCP.hpp"
#include "receiver.hpp"

Client::Client(Receiver* receiver)
: m_user(nullptr)
, m_server(nullptr)
, m_chat_pass(false)
, m_tx(receiver)
{

}

Client::~Client() {
    disconnect();
}

void Client::connect(Server* server) {
    m_server = server;
    m_server->connect(this);
}

void Client::disconnect() {
    m_server->disconnection(this);
}

void Client::new_message() {
    m_tx->send_to_client("\033[31mYou have new message!\033[37m");
}


void Client::message_accept(Message&& message) {
    m_tx->send_to_client(message.who);
    m_tx->send_to_client(message.message);
    /*
    std::cout << message.who << ":" << std::endl;
    std::cout << message.message << std::endl;
    */
}

void Client::message_accept(const Message& message) {
    m_tx->send_to_client("\033[31mGeneral:\033[37m");
    m_tx->send_to_client(message.who);
    m_tx->send_to_client(message.message);
    /*
    std::cout << "\033[31mGeneral:\033[37m" << std::endl;
    std::cout << message.who << ":" << std::endl;
    std::cout << message.message << std::endl;
    */
}

Server* Client::get_s_ptr() noexcept {
    return m_server;
}
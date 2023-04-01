#include "client.hpp"
#include "server.hpp"


Client::Client()
: m_server(nullptr)
{

}

Client::~Client() {

}

void Client::connect(Server* server) {
    m_server = server;
    server->connect(this);
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
    std::cout << message.who << ":" << std::endl;
    std::cout << message.message << std::endl;
}

void Client::control() {
    while (true) {
        Text quest(TEXT_COMMAND);
        if(quest.get_text() == "login") {
            try {
                m_server->login(this);
            } catch (std::exception& exception) {
                std::cout << exception.what() << std::endl;
            }
        }

        if(quest.get_text() == "new-user") {
            try {
                m_server->new_user(this);
            } catch (std::exception& exception) {
                std::cout << exception.what() << std::endl;
            }
        }

        if(quest.get_text() == "size-user") {
            std::cout << m_server->get_user_size() << std::endl;
        }

        if(quest.get_text() == "send-to") {
            try {
                m_server->message_to(this);
            } catch (std::exception& excep) {
                std::cout << excep.what() << std::endl;
            }
        }

        if(quest.get_text() == "chat-connect") {
            try {
                m_server->chat_connect(this);
            } catch (std::exception& excep) {
                std::cout << excep.what() << std::endl;
            }
        }

        if(quest.get_text() == "server-exit") {
            m_server->server_exit(this);
        }

        if(quest.get_text() == "send-chat") {
            m_server->chat_message(this);
        }

        if(quest.get_text() == "exit") {
            break;
        }

        if(quest.get_text() == "online") {
            m_server->who_online(this);
        }
    }
}
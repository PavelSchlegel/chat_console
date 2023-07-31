#include "server_TCP.hpp"
#include "client.hpp"

Server::Server() {

}

Server::~Server() {

}
/*
bool Server::chat_password() {
    std::cout << "year of foundation of St. Petersburg?" << std::endl;
    Text pass;
    if (pass.get_text() == "1703") {
        return true;
    }
    return false;
}
*/
User* Server::nickname_check(const std::string& nick) noexcept {
    return m_users.find(nick);
}

Client* Server::client_search(Client* client) noexcept {
    auto it = m_clPtr.find(client);
    if (it != m_clPtr.end()) {
        return *it;
    }
    return nullptr;
}

void Server::push_message(Client* client) noexcept {
    for (auto& record : client->m_user->m_message) {
        client->message_accept(std::move(record));
    }
    client->message_accept(Message{"END", "END"});
    client->m_user->m_message.clear();
}
/*
void Server::chat_read(Client* client) noexcept {
    for(auto it = m_chat.begin(); it != m_chat.end(); ++it) {
        client->message_accept(*it);
    }
}
*/

void Server::welcome(std::string_view nickname) noexcept {
    std::cout << "\033[31mWelcome :\033[37m" << nickname << std::endl;
}
/*
const std::size_t Server::get_user_size() noexcept {
    return m_users.size();
}

void Server::user_print(Client* client) noexcept {
    for (auto& record : m_users) {
        std::cout << record.second.get_nick() << std::endl;
    }
}

std::ostream& Server::get_user(std::ostream& out, Client* client) noexcept {
    for (auto& record : m_users) {
        out << record.second.get_nick() << ", ";
    }
    return out;
}
*/

void Server::connect(Client* client) noexcept {
    m_clPtr.insert(client);
}

void Server::disconnection(Client* client) noexcept {
    client->m_user = nullptr;
    client->m_chat_pass = false;
    //client->m_server = nullptr;
    m_clPtr.erase(client);
}

void Server::server_exit(Client* client) noexcept {
    client->m_user = nullptr;
    client->m_chat_pass = false;
}

void Server::new_user(Client* client, std::string& nick, std::size_t& hash) {
    if (!client->m_user) {
        if (!nickname_check(nick)) {
            client->m_user = m_users.insert(nick, hash);
            welcome(nick);
        } else {
            throw std::runtime_error("Nickname is used!");
        }
    } else {
        server_exit(client);
        new_user(client, nick, hash);
    }
}

void Server::login(Client* client, const std::string& nick, const std::size_t& hash) {
    if (client_search(client)) {
        if (!(client->m_user)) {
            if (auto ptr = nickname_check(nick)) {
                if (ptr->m_pass_hash == hash) {
                    client->m_user = ptr;
                    if (!ptr->m_message.empty()) {
                        client->new_message();
                        push_message(client);
                    }
                }
            } else {
                throw std::runtime_error("User was not fund!");
            }
        } else {
            server_exit(client);
            login(client, nick, hash);
        }
    } else {
        connect(client);
        login(client, nick, hash);
    }
}
/*
void Server::who_online_print(Client* client) {
    if (client->m_user) {
        for (auto record : m_clPtr) {
            if (record->m_server && record->m_user) {
                if (client->m_user->m_nick != record->m_user->get_nick()) {
                    std::cout << record->m_user->get_nick() << '\n';
                }
            }
        }
    } else {
        throw std::runtime_error("You are not login!");
    }
}
*/
void Server::send_to(Client* client, const std::string& nick_to, const std::string& message) {
    if (client->m_user) {
        //Text search(SEARCH_NICK);
        if (auto ptr = nickname_check(nick_to)) {
            //search.set_text(MESSAGE);
            ptr->m_message.push_back(Message{/*std::chrono::system_clock::now(), search.get_text(),*/message, client->m_user->get_nick()});
        } else {
            throw std::runtime_error("User was not fund");
        }
    } else {
        throw std::runtime_error("You are not login!");
    }
}
/*

void Server::chat_connect(Client* client) noexcept {
    if (client->m_user) {
        if (chat_password()) {
            client->m_chat_pass = true;
            if (m_chat.size()) {
                chat_read(client);
            }
        }
    }
}

void Server::send_to_chat(Client* client) {
    if (client->m_user) {
        if (client->m_chat_pass) {
            Text message(MESSAGE);
            m_chat.push_back(Message{std::chrono::system_clock::now(),message.get_text(), client->m_user->get_nick()});
        } else {
            chat_connect(client);
            send_to_chat(client);
        }
    } else {
        throw std::runtime_error("You are not login!");
    }
}
*/
#pragma once
/*
#ifndef SERVER
#define SERVER
*/

#include "virtual_client.hpp"
#include <string>
#include <string_view>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <list>

class Server {

private:

    std::set<Client*> m_clPtr;
    std::unordered_map<std::string, User> m_users;
    std::list<Message> m_chat;
    bool chat_password();

protected:

    User* nickname_check(const std::string& nick) noexcept;
    Client* client_search(Client* client) noexcept;
    void push_message(Client* client) noexcept;
    //void chat_read(Client* client) noexcept;
    void welcome(std::string_view nickname) noexcept;

public:

    Server();
    ~Server();
    const std::size_t get_user_size() noexcept;
    void user_print(Client* client) noexcept;
    std::ostream& get_user(std::ostream& out, Client* client) noexcept;
    void connect(Client* client) noexcept;
    void disconnection(Client* client) noexcept;
    void server_exit(Client* client) noexcept;
    void new_user(Client* client, std::string& nick, std::size_t& hash);
    void login(Client* client, const std::string& nick, const std::size_t& hash);
    void who_online_print(Client* client);
    void send_to(Client* client);
    void chat_connect(Client* client) noexcept;
    void send_to_chat(Client* client);
    friend class User;
};
//#endif
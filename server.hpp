#ifndef SERVER
#define SERVER

#include "user.hpp"
#include "client.hpp"
#include "client_user.hpp"
#include <list>
#include "text.hpp"
#include <time.h>

#define SERVER_KEY 3
#define CONNECT_KEY 0
#define LOGIN_KEY 1
#define CHAT_KEY 2

class Server {

private:

    std::size_t m_key[SERVER_KEY];
    //m_key[0] = connect
    //m_key[1] = login
    //m_key[2] = connect_chat
    std::list<User> m_users;
    std::list<Client_User> m_cl_us_map;
    std::list<Message> m_chat;

    void show_key() {
        for(std::size_t count = 0; count < SERVER_KEY; ++count) {
            std::cout << m_key[count] << std::endl;
        } 
    }

    bool nickname_check(std::string_view nick) {
        for(auto& record : m_users) {
            if(record.m_nick == nick) {
                return false;
            }
        }
        return true;
    }

    Client_User* client_user_map(Client* client) {
        for(Client_User& search : m_cl_us_map) {
            if(search.get_cptr() == client) {
                return &search;
            }
        }
        return nullptr;
    }

    void push_message(Client* client) {
        for(auto& search : m_cl_us_map) {
            if(search.get_cptr() == client) {
                auto user = search.get_uptr();
                for(auto& record : user->m_message) {
                    client->message_accept(std::move(record));
                }
                user->m_message.clear();
            }
        }
    }

    void chat_read(Client* client) {
        for(auto it = m_chat.begin(); it != m_chat.end(); ++it) {
            client->message_accept(*it);
        }
    }

    void welcome(std::string_view nickname) {
        std::cout << "\033[31mWelcome :\033[37m" << nickname << std::endl;
    }

public:

    Server() {
        srand(static_cast<std::size_t>(time(0)));
        for (std::size_t count = 0; count < SERVER_KEY; ++count) {
            m_key[count] = rand();
        }
    }

    ~Server() = default;

    const std::size_t get_user_size() noexcept {
        return m_users.size();
    }

    void connect(Client* client) {
        m_cl_us_map.push_back(client);
        client->m_connect_key = m_key[0];
    }

    void disconnection(Client* client) {
        for(auto it = m_cl_us_map.begin(); it != m_cl_us_map.end(); ++it) {
            if(it->get_cptr() == client) {
                client->m_gchat_key = 0;
                client->m_login_key = 0;
                client->m_connect_key = 0;
                m_cl_us_map.erase(it);
                return;
            }
        }
    }

    void server_exit(Client* client) noexcept {
        for(auto it = m_cl_us_map.begin(); it != m_cl_us_map.end(); ++it) {
            if(it->m_client_ptr == client) {
                client->m_gchat_key = 0;
                client->m_login_key = 0;
                it->m_user_ptr = nullptr;
                return;
            }
        }
    }

    void new_user(Client* client) {
        if (client->m_connect_key == m_key[CONNECT_KEY]) {
            Text nickname(TEXT_NICKNAME);
            if (nickname_check(nickname.get_text())) {
                auto record = client_user_map(client);
                m_users.push_back(User(nickname.get_text()));
                record->m_user_ptr = &m_users.back();
                client->m_login_key = m_key[LOGIN_KEY];
                welcome(record->m_user_ptr->get_user_nick());
            } else {
                throw std::runtime_error("Nickname is used!");
            }
        } else {
            throw std::runtime_error("Connect error: client was not connected/attested!");
        }
    }

    void who_online(Client* client) noexcept {
        std::cout << "Online is :" << std::endl;
        for(auto& search : m_cl_us_map) {
            if(search.m_client_ptr && search.m_user_ptr) {
                std::cout << search.m_user_ptr->get_user_nick() << std::endl;
            }
        }
    }

    void login(Client* client) {
        if(client->m_connect_key == m_key[CONNECT_KEY]) {
            if(!(client->m_login_key == m_key[LOGIN_KEY])) {
                auto record = client_user_map(client);
                Text request(TEXT_NICKNAME);
                for(User& user : m_users) {
                    if(user.m_nick == request.get_text()) {
                        request.set_text(TEXT_PASSWORD);
                        if(user.m_password == request.get_text()) {
                            record->m_user_ptr = &user;
                            client->m_login_key = m_key[LOGIN_KEY];
                            welcome(record->m_user_ptr->get_user_nick());
                            if(user.m_message.size()) {
                                client->new_message();
                                push_message(client);
                                return;
                            }
                        } else {
                            throw std::runtime_error("Invalid password!");
                        }
                    }
                }
                throw std::runtime_error("\033[34mUser was not fund!\033[37m");
            } else {
                throw std::runtime_error("You have already entered a password/account certified!");
            }
        } else {
            throw std::runtime_error("Client was not connected/attested!");
        }
    }

    void message_to(Client* client) {
        if(client->m_login_key == m_key[LOGIN_KEY]) {
            Text search_user(TEXT_NICKNAME);
            for(auto& record : m_users) {
                if(record.m_nick == search_user.get_text()) {
                    record.m_message.push_back(Message{Text(TEXT_MESSAGE).get_text(), client_user_map(client)->m_user_ptr->get_user_nick()});
                    return;
                }
            }
            throw std::runtime_error("Nick/user was not fund!");
        } else {
            throw std::runtime_error("Please log in!");
        }
    }

    void chat_connect(Client* client) {
        if(client->m_login_key == m_key[LOGIN_KEY]) {
            auto record = client_user_map(client);
            if(record->m_user_ptr->m_password == Text(TEXT_PASSWORD).get_text()) {
                client->m_gchat_key = m_key[CHAT_KEY];
                if(m_chat.size()) {
                    chat_read(client);
                }
            } else {
                throw std::runtime_error("Invalid password");
            }
        }
    }

    void chat_message(Client* client) noexcept {
        if(client->m_gchat_key == m_key[CHAT_KEY]) {
            auto record = client_user_map(client);
            m_chat.push_back(Message{Text(TEXT_MESSAGE).get_text(), record->m_user_ptr->get_user_nick()});
        } else {
            chat_connect(client);
            chat_message(client);
        }
    }
};
#endif
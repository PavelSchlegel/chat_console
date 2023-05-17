#ifndef SERVER
#define SERVER

#include "include.hpp"

class Server {

private:

    std::set<Client*> m_clPtr;
    std::unordered_map<std::string, User> m_users;
    std::list<Message> m_chat;

    
    bool chat_password() {
        std::cout << "year of foundation of St. Petersburg?" << std::endl;
        Text pass;
        if (pass.get_text() == "1703") {
            return true;
        }
        return false;
    }

protected:

    User* nickname_check(const std::string& nick) noexcept {
        auto it = m_users.find(nick);
        if (it == m_users.end()) {
            return nullptr;
        }
        return it->second.g_ptr();
    }

    Client* client_search(Client* client) noexcept {
        auto it = m_clPtr.find(client);
        if (it != m_clPtr.end()) {
            return *it;
        }
        return nullptr;
    }

    void push_message(Client* client) noexcept {
        for (auto& record : client->m_user->m_message) {
            client->message_accept(std::move(record));
        }
        client->m_user->m_message.clear();
    }

    void chat_read(Client* client) noexcept {
        for(auto it = m_chat.begin(); it != m_chat.end(); ++it) {
            client->message_accept(*it);
        }
    }

    void welcome(std::string_view nickname) noexcept {
        std::cout << "\033[31mWelcome :\033[37m" << nickname << std::endl;
    }

public:

    Server() {

    }

    ~Server() = default;

    const std::size_t get_user_size() noexcept {
        return m_users.size();
    }

    void user_print(Client* client) noexcept {
        for (auto& record : m_users) {
            std::cout << record.second.get_nick() << std::endl;
        }
    }

    std::ostream& get_user(std::ostream& out, Client* client) noexcept {
        for (auto& record : m_users) {
            out << record.second.get_nick() << ", ";
        }
        return out;
    }

    void connect(Client* client) noexcept {
        m_clPtr.insert(client);
    }

    void disconnection(Client* client) noexcept {
        client->m_user = nullptr;
        client->m_chat_pass = false;
        client->m_server = nullptr;
        m_clPtr.erase(client);
    }

    void server_exit(Client* client) noexcept {
        client->m_user = nullptr;
        client->m_chat_pass = false;
    }

    void new_user(Client* client, const std::string& nick, const std::size_t hash) {
        if (!client->m_user) {
            if (!nickname_check(nick)) {
                m_users.emplace(User(nick, hash));
                auto it = m_users.find(nick);
                client->m_user = it->second.g_ptr();
                welcome(nick);
            }
        } else {
            server_exit(client);
            new_user(client, nick, hash);
        }
    }

    void login(Client* client, const std::string& nick, const std::size_t hash) {
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

    void who_online_print(Client* client) {
        if (client->m_user) {
            for (auto record : m_clPtr) {
                if (record->m_server && record->m_user) {
                    if (client->m_user->m_nick != record->m_user->get_nick()) {
                        std::cout << record->m_user->get_nick() << '\n';
                    }
                }
            }
        } else {
            std::runtime_error("You are not login!");
        }
    }

    void send_to(Client* client) {
        if (client->m_user) {
            Text search(SEARCH_NICK);
            if (auto ptr = nickname_check(search.get_text())) {
                search.set_text(MESSAGE);
                ptr->m_message.push_back(Message{search.get_text(), client->m_user->get_nick()});
            } else {
                throw std::runtime_error("User was not fund");
            }
        } else {
            std::runtime_error("You are not login!");
        }
    }

    void chat_connect(Client* client) noexcept {
        if (client->m_user) {
            if (chat_password()) {
                client->m_chat_pass = true;
                if (m_chat.size()) {
                    chat_read(client);
                }
            }
        }
    }

    void send_to_chat(Client* client) noexcept {
        if (client->m_user) {
            if (client->m_chat_pass) {
                Text message(MESSAGE);
                m_chat.push_back(Message{message.get_text(), client->m_user->get_nick()});
            } else {
                chat_connect(client);
                send_to_chat(client);
            }
        } else {
            std::runtime_error("You are not login!");
        }
    }

    friend class User;
};
#endif
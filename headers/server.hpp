#ifndef SERVER
#define SERVER

#include "include.hpp"

class Server {

private:

    std::set<Client*> m_clPtr;
    //std::list<Client*> m_clients;
    //unorderer_map<std::string, User> m_users;
    std::list<User> m_users;
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

    User* nickname_check(std::string& nick) noexcept {
        for (auto it = m_users.begin(); it != m_users.cend(); ++it) {
            if (it->m_nick == nick) {
                return it->g_ptr();
            }
        }
        return nullptr;
    }

    /*
    Client* client_search(Client* client) noexcept {
        for (auto record : m_clients) {
            if (record == client) {
                return record;
            }
        }
        return nullptr;
    }
    */

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
            std::cout << record.get_nick() << std::endl;
        }
    }

    std::ostream& get_user(std::ostream& out, Client* client) noexcept {
        for (auto& record : m_users) {
            out << record.get_nick() << ", ";
        }
        return out;
    }

    void connect(Client* client) noexcept {
        //m_clients.push_back(client);
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

    void new_user(Client* client) {
        if (!(client->m_user)) {
            Text nickname(NICKNAME);
            if (!(nickname_check(nickname.get_text()))) {
                m_users.push_back(User(nickname.get_text()));
                client->m_user = &m_users.back();
                welcome(nickname.get_text());
            } else {
                throw std::runtime_error("Nickname is used!");
            }
        } else {
            server_exit(client);
            new_user(client);
        }
    }

    void login(Client* client) {
        if (client_search(client)) {
            if (!(client->m_user)) {
                Text quest(NICKNAME);
                if (auto ptr = nickname_check(quest.get_text())) {
                    quest.set_text(PASSWORD);
                    if (quest.get_text() == ptr->m_password) {
                        client->m_user = ptr;
                        welcome(ptr->get_nick());
                        if (ptr->m_message.size()) {
                            client->new_message();
                            push_message(client);
                        }
                    }
                } else {
                    throw std::runtime_error("User was not fund!");
                }
            } else {
                server_exit(client);
                login(client);
            }
        } else {
            connect(client);
            login(client);
        }
    }

    void who_online_print(Client* client) noexcept {
        if (client->m_user) {
            for (auto record : m_clPtr) {
                if (record->m_server && record->m_user) {
                    if (client->m_user->m_nick != record->m_user->get_nick()) {
                        std::cout << record->m_user->get_nick() << '\n';
                    }
                }
            }
        } else {
            login(client);
        }
    }

    std::ostream& get_user_online(std::ostream& out, Client* client) {
        if (client->m_user) {
            for (auto& record : m_clPtr) {
                if ((client->m_user->m_nick != record->m_user->get_nick())) {
                    if (record->m_server && record->m_user) {
                        out << record->m_user->get_nick() << ", ";
                    }
                }
            }
            return out;
        } else {
            login(client);
            get_user_online(out, client);
            return out;
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
            login(client);
            send_to(client);
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
            login(client);
            send_to_chat(client);
        }
    }

    friend class User;
};
#endif
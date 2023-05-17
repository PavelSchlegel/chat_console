#ifndef USER
#define USER

#include "text.hpp"
#include <vector>

class Client;

struct Message {

    std::string message;
    std::string who;
};

class User {

public:
    
    std::string m_nick;
    std::size_t m_pass_hash;
    std::vector<Message> m_message;
    User(std::string& nick);
    User(const std::string& nick, const std::size_t hash);
    ~User();
    User* g_ptr();
    void re_nick(Client* client, const std::string& nick);
    bool re_pass(Client* client, const std::size_t& old, const std::size_t& hash);
    const std::string& get_nick() noexcept;

private:

    void pass();
};
#endif
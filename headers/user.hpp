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
    //пароль в открытом виде...на hash
    std::size_t m_pass_hash;
    //std::string m_password;
    std::vector<Message> m_message;
    User(std::string& nick);
    ~User();
    User* g_ptr();
    void re_nick(Client* client);
    void re_pass(Client* client);
    const std::string& get_nick() noexcept;

private:

    void pass();
};
#endif
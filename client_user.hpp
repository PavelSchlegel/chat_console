#ifndef CLIENT_USER
#define CLIENT_USER

#include "client.hpp"
#include "user.hpp"

//для привязки клиента к юзеру
class Client_User {

private:

public:

    User* m_user_ptr;
    Client* m_client_ptr;

    Client_User(Client* client)
    : m_client_ptr(client)
    , m_user_ptr(nullptr)
    {

    }

    ~Client_User() {

    }

    void set_uptr(User* user) {
        m_user_ptr = user;
    }

    std::string_view get_who() {
        return m_user_ptr->m_nick;
    }

    Client* get_cptr() {
        return m_client_ptr;
    }

    User* get_uptr() {
        return m_user_ptr;
    }
};
#endif
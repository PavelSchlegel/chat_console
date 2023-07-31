
#include "user.hpp"
#include <iostream>
#include "client.hpp"

User::User(const std::string& nick, const std::size_t hash)
:m_nick(nick)
,m_pass_hash(hash) {

}

User::~User() {
}

User* User::g_ptr() {
    return this;
}
/*
void User::re_nick(Client* client, const std::string& nick) {
    if (!(client->m_server->nickname_check(nick))) {
        m_nick = nick;
    } else {
        throw std::runtime_error("Nick is used!");
    }
}
*/

bool User::re_pass(Client* client, const std::size_t& old, const std::size_t& hash) {
    if (m_pass_hash == old) {
        m_pass_hash = hash;
    }
    return false;    
}

const std::string& User::get_nick() noexcept {
    return m_nick;
}
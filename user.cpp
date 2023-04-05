#include "user.hpp"
#include "server.hpp"

User::User(std::string& nick)
: m_nick(nick)
{
    pass();
}

User::~User() {
}

User* User::g_ptr() {
    return this;
}

void User::pass() {
    while(true) {
        Text pass(PASSWORD);
        std::cout << "\033[31mEnter the password again\033[37m" << std::endl;
        Text pass_request;
        if(!(pass.get_text() == pass_request.get_text())) {
            std::cout << "\033[31mError, please re-enter\033[37m" << std::endl;
        } else {
            m_password = pass_request.get_text();
            break;
        }
    }
}

void User::re_nick(Client* client) {
    Text request(NEW_NICK);
    if (!(client->m_server->nickname_check(request.get_text()))) {
        m_nick = request.get_text();
    } else {
        throw std::runtime_error("Nick is used!");
    }
}

void User::re_pass(Client* client) {
    Text actual_pass(PASSWORD);
    if (m_password == actual_pass.get_text()) {
        std::cout << "\033[31mEnter your new password:\033[37m" << std::endl;
        Text new_pass;
        std::cout << "\033[31mEnter your new password again:\033[37m" << std::endl;
        std::cin >> actual_pass;
        if (new_pass.get_text() == actual_pass.get_text()) {
            m_password = new_pass.get_text();
        } else {
            std::cout << "\033[31mInvalid password, please try later!" << std::endl;
        }
    }
}

const std::string& User::get_nick() noexcept {
    return m_nick;
}
#ifndef USER
#define USER

#include <iostream>
#include <string>
#include <vector>
#include "text.hpp"

struct Message {

    std::string message;
    std::string who;
};

class User {

public:
    
    std::string m_nick;
    std::string m_password;
    std::vector<Message> m_message;

    User(std::string& nick)
    : m_nick(nick)
    {
        while(true) {
            Text pass(TEXT_PASSWORD);
            std::cout << "Enter the password again" << std::endl;
            Text pass_request;
            if(!(pass.get_text() == pass_request.get_text())) {
                std::cout << "Error, please re-enter" << std::endl;
            } else {
                m_password = pass_request.get_text();
                break;
            }
        }
    }

    ~User() {
    }

    const std::string& get_user_nick() {
        return m_nick;
    }
};

#endif
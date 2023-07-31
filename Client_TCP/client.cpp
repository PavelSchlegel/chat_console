#include "client.hpp"

std::string get_nickname(Command_ID id)
{
    std::string str;
    switch (id) {
        case Command_ID::SEND_TO: {
            std::cout << "Who is recipient?" << std::endl;
            std::getline(std::cin, str);
            return str;
        } 
        case Command_ID::NEW_USER: {
            std::cout << "Enter your nickname:" << std::endl;
            std::getline(std::cin, str);
            return str;
        }
        default: return str = "Alien";
    }

}

std::string get_pass()
{
    std::cout << "Enter you password:" << std::endl;
    std::string pass;
    std::getline(std::cin, pass);
    std::size_t hash = std::hash<std::string>{}(pass);
    std::string hash_return = std::to_string(hash);
    return hash_return;
}

std::string get_message()
{
    std::cout << "Enter you message:" << std::endl;
    std::string message;
    std::getline(std::cin, message);
    return message;
}

void Client::new_user()
{
    if (m_tr.status()) {
        m_tr.send_to_server(NEW_USER);
        m_tr.send_to_server(get_nickname(NEW_USER));
        m_tr.send_to_server(get_pass());
        auto str = m_tr.buf_str_read();
        std::cout << str << std::endl;
    }
}
//ошибка при логине - получение оставленых сообщений(алгоритм парсинга)
void Client::login()
{
    if (m_tr.status()) {
        m_tr.send_to_server(LOGIN);
        m_tr.send_to_server(get_nickname(NEW_USER));
        m_tr.send_to_server(get_pass());
        while (true) {
            std::string str = m_tr.buf_str_read();
            if (str != "END") {
                std::cout << str << std::endl;
                continue;
            }
            return;
        }
    }
}

void Client::send_to()
{
    if (m_tr.status()) {
        m_tr.send_to_server(SEND_TO);
        m_tr.send_to_server(get_nickname(SEND_TO));
        m_tr.send_to_server(get_message());
        auto str = m_tr.buf_str_read();
        std::cout << str << std::endl;
    }
}

void Client::test()
{
    if (m_tr.status()) {
        m_tr.test();
    }
}

void Client::quit()
{
    if (m_tr.status()) {
        m_tr.send_to_server(EXIT);
        auto str = m_tr.buf_str_read();
        if (str == "Done") {
            std::cout << "Client exit." << std::endl;
        } else {
            std::cout << str << std::endl;
        }
    }
}
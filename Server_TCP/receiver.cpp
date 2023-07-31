#include "receiver.hpp"
#include "server_TCP.hpp"

Receiver::Receiver(Server *server)
: sockert_file_descriptor(-1)
, connection(-1)
, bind_status(-1)
, connection_status(-1)
, m_client(this)
//, buf_index(0)
{
    m_client.connect(server);
    start();
}

void Receiver::send_to_client(std::string str)
{
    std::cout << "Server respons:" << str << std::endl;
    str.push_back('\0');
    ssize_t bytes = write(connection, str.data(), str.size());
}

Command_ID Receiver::read_command_id()
{
    Command_ID id;
    while (true) {
        if (read(connection, &id, 1) == 1) {
            char s = id;
            if (id >= NEW_USER && id <= ERROR) {
                return id;
            }
        } else {
            break;
        }
    }
    return ERROR;
}

std::string Receiver::buf_str_read()
{
    std::string str;
    while(true) {
        char symbol;
        if (read(connection, &symbol, 1) == 1) {
            if (symbol != '\0') {
                str.push_back(symbol);
            } else {
                break;
            }
        } else {
            break;
        }
    }
    return str;
}

void Receiver::start()
{
    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;
    bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress,
    sizeof(serveraddress));
    connection_status = listen(sockert_file_descriptor, 5);
    length = sizeof(client);
    connection = accept(sockert_file_descriptor,(struct sockaddr*)&client, &length);
}

Command_ID Receiver::data_constructor() {
    try {
        auto id = read_command_id();
        switch(id) {
            case Command_ID::NEW_USER: {
                auto nick = buf_str_read();
                std::size_t hash = std::stoull(buf_str_read());
                try {
                    m_client.get_s_ptr()->new_user(&m_client, nick, hash);
                    send_to_client("Done");
                } catch (const std::exception& error) {
                    std::string str = error.what();
                    send_to_client(str);
                }
                return NEW_USER;
            }
            case Command_ID::LOGIN: {
                auto nick = buf_str_read();
                std::size_t hash = std::stoull(buf_str_read());
                try {
                    m_client.get_s_ptr()->login(&m_client, nick, hash);
                    send_to_client("Done");
                } catch (const std::exception& error) {
                    std::string str = error.what();
                    send_to_client(str);
                }
                return NEW_USER;
            }
            case Command_ID::SEND_TO: {
                auto nick_to = buf_str_read();
                auto message = buf_str_read();
                try {
                    m_client.get_s_ptr()->send_to(&m_client, nick_to, message);
                    send_to_client("Done");
                } catch (std::exception error) {
                    send_to_client(error.what());
                }
                return NEW_USER;
            }
            case Command_ID::EXIT: {
                m_client.disconnect();
                send_to_client("Done");
                return NEW_USER;
            }
            case Command_ID::TEST: {
                auto str = buf_str_read();
                if (str == "Client_TEST") {
                    std::cout << "Testing done:" << std::endl;
                    std::cout << "Client RX:" << std::endl;
                    std::cout << "Command id: ok" << std::endl;
                    std::cout << "Message: ok" << std::endl;
                    return NEW_USER;
                }
            }
            case Command_ID::END: {
                return LOGIN;
            }
            default: std::cout << "ERROR!" << std::endl;
                return LOGIN;
            
        }

    } catch (std::exception error) {
        std::cout << error.what() << std::endl;
        return LOGIN;
    }
}
#include "headers/functions.hpp"

void OS_Version() {
    #if defined(__linux__)
        struct utsname utsname;
        uname(&utsname);
        std::cout << "OS name: " << utsname.sysname << std::endl;
        std::cout << "OS version: " << utsname.version << std::endl;
    #endif
}

bool is_Up (char a) {
    return a >= 65 || a <= 90;
}

bool is_Low (char a) {
    return a >= 97 || a <= 122;
}

bool is_Digit(char a) {
    switch (a) {
    case '@' :
    case '!' :
    case '&' :
    case '%' :
    case '_' :
    case '#' :
    case '?' :
    case '$' :
        return true;
    default:
        return false;
    }
}

std::string get_nick() {
    std::cout << "Enter you nickname:" << std::endl;
    std::string nick;
    std::getline(std::cin, nick);
    return nick;
}

std::size_t get_pass() {
    std::cout << "Enter you password:" << std::endl;
    std::string pass;
    std::getline(std::cin, pass);
    return std::hash<std::string>{}(pass);
}

std::size_t get_new_pass() {
    using namespace std;
    string P_in;
    cout << "Please use 8 upper and lower register and special characters:" <<
        " " << '@' << " "<<  '!' << " " << '&' << " " << '%' << " " << '_' << '#' << " " << '?' << " " << '$' << endl;
    while (1) {
        cout << "Enter you password:" << endl;
        getline(cin, P_in);
        while (1) {
            if (P_in.size() > 7) {
                bool up = any_of(P_in.begin(), P_in.end(), is_Up);
                bool low = any_of(P_in.begin(), P_in.end(), is_Low);
                bool special = any_of(P_in.begin(), P_in.end(), is_Digit);
                if (up && low && special) {
                    while (1) {
                        cin.clear();
                        string again;
                        cout << "Please enter you password again:" << endl;
                        getline(cin, again);
                        if (P_in == again) {
                            size_t pass_hash = hash<string>{}(P_in);
                            return pass_hash;
                        } else {
                            cout << "Password repetition is not correct!" << endl;
                            cout << "Please try again:" << endl;
                            cin.clear();
                        }
                    }
                }
            } else { 
                cout << "Password must be at least 8 characters!" << endl;
                cin.clear();
            }
        }
    }
}

void control(Client* client) {
    while (true) {
        Text quest(COMMAND);
        if(quest.get_text() == "login") {
            try {
                std::string nick = get_nick();
                std::size_t hash = get_pass();
                client->get_s_ptr()->login(client, nick, hash);
            } catch (std::exception& exception) {
                std::cout << exception.what() << std::endl;
            }
        }

        if(quest.get_text() == "new-user") {
            try {
                std::string nick = get_nick();
                std::size_t hash = get_new_pass();
                client->get_s_ptr()->new_user(client, nick, hash);
            } catch (std::exception& exception) {
                std::cout << exception.what() << std::endl;
            }
        }

        if(quest.get_text() == "size-user") {
            std::cout << client->get_s_ptr()->get_user_size() << std::endl;
        }

        if(quest.get_text() == "send-to") {
            try {
                client->get_s_ptr()->send_to(client);
            } catch (std::exception& excep) {
                std::cout << excep.what() << std::endl;
            }
        }

        if(quest.get_text() == "server-exit") {
            client->get_s_ptr()->server_exit(client);
        }

        if(quest.get_text() == "chat") {
            client->get_s_ptr()->send_to_chat(client);
        }

        if(quest.get_text() == "exit") {
            break;
        }

        if(quest.get_text() == "online-p(") {
            client->get_s_ptr()->who_online_print(client);
        }
    }
}
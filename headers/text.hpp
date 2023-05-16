#ifndef TEXT
#define TEXT

#include <iostream>
#include <string>

//для обьектов текст
#define NICKNAME 0
#define PASSWORD 1
#define MESSAGE 2
#define COMMAND 3
#define SEARCH_NICK 4
#define NEW_NICK 5

class Text {
private:

    std::string m_str_Buf;

    void text_out(short macros) {
        if(macros == 0) {
            std::cout << "\033[31mEnter your nickname:\033[37m" << std::endl;
        }
        if(macros == 1) {
            std::cout << "\033[31mEnter your password:\033[37m" << std::endl;
        }
        if(macros == 2) {
            std::cout << "\033[31mEnter your message:\033[37m" << std::endl;
        }
        if(macros == 3) {
            std::cout << "\033[31mSet your command:\033[37m" << std::endl;
        }
        if(macros == 4) {
            std::cout << "\033[31mRecipient:\033[37m" << std::endl;
        }
        if(macros == 5) {
            std::cout << "\033[31mSet your new nikname:\033[37m" << std::endl;
        }
    }

public:
    Text() {
        std::getline(std::cin, m_str_Buf);
    }

    Text(short macros) {
        text_out(macros);
        std::getline(std::cin, m_str_Buf);
    }

    ~Text() = default;

    std::string& get_text() noexcept {
        return m_str_Buf;
    }

    void set_text(short macros) {
        text_out(macros);
        m_str_Buf.clear();
        std::getline(std::cin, m_str_Buf);
    }

    friend std::ostream& operator<<(std::ostream& out, const Text& text) {
        return out << text.m_str_Buf;
    }

    friend std::istream& operator>>(std::istream& in, Text& text) {
        if (!text.m_str_Buf.empty()) {
            text.m_str_Buf.clear();
        }
        std::getline(in, text.m_str_Buf);
        return in;
    }
};
#endif
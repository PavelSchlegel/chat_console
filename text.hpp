#ifndef TEXT
#define TEXT

#include <iostream>
#include <string>

//для обьектов текст
#define TEXT_NICKNAME 0
#define TEXT_PASSWORD 1
#define TEXT_MESSAGE 2
#define TEXT_COMMAND 3

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

};
#endif
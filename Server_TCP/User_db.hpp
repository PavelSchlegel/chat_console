#pragma once
#include <mysql.h>
#include <iostream>
#include "user.hpp"
#include <string.h>
#include <vector>
#include <unordered_map>

class User_db {

    private:
        MYSQL mysql;
        std::unordered_map<std::string, User> m_users;
    public:
        User_db();
        ~User_db();
        User* find(const std::string& nick);
        User* insert(const std::string& nick, std::size_t hash)
        {
            //insert 
            mysql_query(&mysql, "INSERT * FROM моя таб");
            m_users.insert({nick, User(nick, hash)});
            auto it = m_users.find(nick);
            return it->second.g_ptr();
        }
};

User_db::User_db() 
{
    // Получаем дескриптор соединения
	mysql_init(&mysql);
	if (&mysql == nullptr) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		std::cout << "Error: can't create MySQL-descriptor" << std::endl;
	}
 
	// Подключаемся к серверу
	if (!mysql_real_connect(&mysql, "localhost", "root", "root", "моя таб", NULL, NULL, 0)) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
	}
	else {
		// Если соединение успешно установлено выводим фразу — "Success!"
		std::cout << "Success!" << std::endl;
	}
 
	mysql_set_character_set(&mysql, "utf8");
	//Смотрим изменилась ли кодировка на нужную, по умолчанию идёт latin1
	std::cout << "connection characterset: " << mysql_character_set_name(&mysql) << std::endl;

    //запрос и заполнение мап select
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res)) {
        m_users.insert({nick, User(nick, hash)});

    }

}

User_db::~User_db()
{
    mysql_close(&mysql);
}

User* User_db::find(const std::string &nick)
{
    auto it = m_users.find(nick);
    if (it == m_users.end()) {
        return nullptr;
    }
    return it->second.g_ptr();
}
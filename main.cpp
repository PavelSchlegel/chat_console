#include "headers/server.hpp"

int main() {
    Server server;
    Client client;
    client.connect(&server);
    client.control();
    client.disconnection();
/*
    std::size_t a = std::hash<Client*>{}(&client);
    std::cout << a << std::endl;
*/
    return 0;
}
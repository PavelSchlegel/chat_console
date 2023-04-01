#include "server.hpp"

int main() {

    Server server;
    Client client;
    client.connect(&server);
    client.control();
    client.disconnection();
    
    return 0;
}
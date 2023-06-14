#include "headers/functions.hpp"

int main() {
    OS_Version();
    Server server;
    Client client;
    client.connect(&server);
    control(&client);
    client.disconnection();

    return 0;
}
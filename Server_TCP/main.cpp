#include "server_TCP.hpp"

int main() {

    Server server;
    Client client; //virtual
    try {
        client.client_start();
    } catch (std::runtime_error error) {
        std::cout << "Error:" << error.what() << std::endl;
    }
    return 0;
}
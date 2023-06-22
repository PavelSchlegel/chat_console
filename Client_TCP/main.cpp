#include "client_TCP.hpp"

int main() {
    OS_version();
    Client client;
    try {
        client.client_start();
        client.new_user();
        client.disconnection();
    } catch (std::runtime_error error) {
        std::cout << "ERROR:" << error.what() << std::endl;
    }
    return 0;
}
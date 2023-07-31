#include "server_TCP.hpp"
#include "receiver.hpp"

int main() {

    Server server;
    Receiver receiver(&server);
    while (1) {
        if (receiver.data_constructor()) {
            break;
        }
    }
    return 0;
}
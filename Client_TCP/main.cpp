#include "client.hpp"

int main() 
{
    Client client;
    client.test();
    client.new_user();
    client.quit();
    client.new_user();
    client.send_to();
    client.quit();
    client.login();
    client.quit();

    return 0;
}
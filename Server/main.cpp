#include <iostream>
using namespace std;

#include "Server.h"

int main(){
    Server* server = new Server(2024);
    server->startServer();

    return 0;
}


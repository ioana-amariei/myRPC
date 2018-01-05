#include <iostream>
using namespace std;

#include "Server.h"

int main(){
    Server server = Server();
    int socketDescriptor = server.createSocket();

    server.bindSocket(socketDescriptor);
    server.listenConnections(socketDescriptor);
    server.serveClients(socketDescriptor);

    return 0;
}


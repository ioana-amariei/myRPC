#include <iostream>
#include "rapidxml/rapidxml.hpp"
using namespace std;
using namespace rapidxml;


#include "Client.h"

int main(){
    Client client = Client();
    int socketDescriptor = client.createSocket();

    client.connectToServer(socketDescriptor);
    client.readMessageFromTerminal();
    client.sendMessageToServer(socketDescriptor);
    client.readBufferFromServer(socketDescriptor);
    client.readMessageFromServer(socketDescriptor);
    client.printMessage();

    client.closeConnection(socketDescriptor);

    return 0;
}





#include <iostream>
using namespace std;


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





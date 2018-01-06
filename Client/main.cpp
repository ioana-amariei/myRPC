#include <iostream>
using namespace std;

#include "Client.h"
#include "UI.h"

int main(int argc, char* argv[]){
//   Client* client = Client();
//
//    int socketDescriptor = client.createSocket();
//
//    client.connectToServer(socketDescriptor);
//    client.readMessageFromTerminal();
//    client.sendMessageToServer(socketDescriptor);
//    client.readBufferFromServer(socketDescriptor);
//    client.readMessageFromServer(socketDescriptor);
//
//    client.printMessage();
//
//    client.closeConnection(socketDescriptor);

    // afisare lista operatii
    // preluare comanda
    // afisare rezultate


//    Client* client = new Client("127.0.0.1", 2024);

    UI* ui = new UI(nullptr);
    ui->startUserInteraction();

    return 0;
}





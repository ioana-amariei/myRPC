//
// Created by ioana on 05.01.2018.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <netinet/in.h>
#include "GUI.h"

class Client {
private:
    int socketDescriptor;
    struct sockaddr_in server;
    char message[100];
    char* buffer;
    GUI* gui;

    sockaddr_in &initializeStructure();

public:
    Client();

    int createSocket();
    void connectToServer(int socketDescriptor);
    void readMessageFromTerminal();
    void sendMessageToServer(int socketDescriptor);
    void readMessageFromServer(int socketDescriptor);
    void readBufferFromServer(int socketDescriptor);
    void printMessage();
    void closeConnection(int socketDescriptor);
};


#endif //CLIENT_CLIENT_H

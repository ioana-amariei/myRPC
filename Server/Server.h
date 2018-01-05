//
// Created by ioana on 05.01.2018.
//

#ifndef MYRPC_SERVER_H
#define MYRPC_SERVER_H


#include <netinet/in.h>
#include "Helpers.h"


class Server {
private:
    struct sockaddr_in server;
    struct sockaddr_in from;
    char receivedMessage[100];
    char responseMessage[100] = " ";
    int status;
    int pid;


    void prepareDataStructures();
    sockaddr_in &initializeStructure();
    void prepareResponseMessage();

public:
    Server();

    int createSocket();
    void bindSocket(int socketDescriptor);
    void listenConnections(int socketDescriptor);
    void serveClients(int socketDescriptor);
};


#endif //MYRPC_SERVER_H

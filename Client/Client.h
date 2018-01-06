//
// Created by ioana on 05.01.2018.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <netinet/in.h>
#include <string>
#include "UI.h"

using namespace std;

class Client {
private:
    string *ip;
    int port;

    int socketDescriptor;
    struct sockaddr_in server;
    char message[100];

    void initializeConnectionInfo();
    void createSocket();
    void connectToServer();

public:
    Client(const char ipAddress[], int port);
    ~Client();
    string getOperationListFromServer();
    void readMessageFromTerminal();
    void sendMessageToServer();
    string readMessageFromServer();
    string readBufferFromServer();
    void printMessage();
    string makeOperationRequest(string request);

    string getOperationListResponseFromServer() const;

    void sendOperationListRequestToServer();
};


#endif //CLIENT_CLIENT_H
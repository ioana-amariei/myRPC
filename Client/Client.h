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

    void initializeConnectionInfo();

    void createSocket();

    void connectToServer();

public:
    Client(const char ipAddress[], int port);

    ~Client();

    string getOperationListFromServer();

    string makeOperationRequest(string request);

    string getOperationListResponseFromServer();

    void sendOperationListRequestToServer();
};


#endif //CLIENT_CLIENT_H
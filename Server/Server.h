//
// Created by ioana on 05.01.2018.
//

#ifndef MYRPC_SERVER_H
#define MYRPC_SERVER_H


#include <netinet/in.h>
#include <string>
#include "Helpers.h"

#include "pugixml/src/pugixml.hpp"
//#include "pugixml/src/pugixml.cpp"
#include "pugixml/src/pugiconfig.hpp"

using namespace pugi;
using namespace std;


class Server {
private:
    struct sockaddr_in server;
    struct sockaddr_in from;
    int status;
    int pid;
    int socketDescriptor;
    int port;

    void prepareDataStructures();
    sockaddr_in &initializeStructure();
    void sendFile(int socketDescriptor);

public:
    Server(int port);

    void createSocket();
    void bindSocket();
    void listenConnections();
    void startServer();

    void sendResponse(int sd, string message);

    void handleOperationCall(int sd, xml_document& doc);

    void handleAdd(int sd, xml_document &document);
};


#endif //MYRPC_SERVER_H

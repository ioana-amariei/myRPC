//
// Created by ioana on 05.01.2018.
//

#include "Server.h"

#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <iostream>
#include <string>
#include "pugixml/src/pugixml.hpp"
#include "pugixml/src/pugixml.cpp"
#include "pugixml/src/pugiconfig.hpp"

using namespace pugi;


using namespace std;


Server::Server(int port) {
    this->port = port;

    prepareDataStructures();
    initializeStructure();

    createSocket();
    bindSocket();
    listenConnections();
}

void Server::prepareDataStructures() {
    bzero(&this->server, sizeof(this->server));
    bzero(&this->from, sizeof(this->from));
}

sockaddr_in &Server::initializeStructure() {
    /* establishing the family of sockets */
    this->server.sin_family = AF_INET;
    /* accept any address */
    this->server.sin_addr.s_addr = htonl(INADDR_ANY);
    /* use a user port */
    this->server.sin_port = htons(port);

    return this->server;
}

void Server::createSocket() {
    if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("[server]Error at socket().\n");
    }
}

void Server::bindSocket() {
    if (bind(socketDescriptor, (struct sockaddr *) &this->server, sizeof(struct sockaddr)) == -1) {
        printf("[server]Error at bind().\n");
    }
}

void Server::listenConnections() {
    if (listen(socketDescriptor, 5) == -1) {
        printf("[server]Error at listen().\n");
    }
}

/* serve clients in a concurrent way*/
void Server::startServer() {
    while (1) {
        socklen_t length = sizeof(this->from);

        printf("[server]Waiting at port %d...\n", port);
        fflush(stdout);

        int clientSocketDescriptor = accept(socketDescriptor, (struct sockaddr *) &this->from, &length);

        if (clientSocketDescriptor < 0) {
            perror("[server] Error at accept().\n");
            continue;
        }

        this->pid = fork();

        if (this->pid < 0) {
            perror("Error at fork(). \n");
            continue;
        }

        if (this->pid == 0) {
            int size = readInt(clientSocketDescriptor);
            char *requestBuffer = readBuffer(clientSocketDescriptor, size);

            printf("[server]Message received...%s\n", requestBuffer);

            string request(requestBuffer);

            xml_document doc;
            xml_parse_result result = doc.load_string(request.c_str());

            string requestType = doc.document_element().attribute("type").value();
            cout << requestType << endl;

            if (!result) {
                cout << "Parsed with errors" << endl;
                cout << result.description() << endl;
                const char *buffer = "The request is not valid. The XML document could not be parsed.";
                sendResponse(clientSocketDescriptor, buffer);
            } else if (requestType.compare("operationList") == 0) {
                cout << "operationList called" << endl;
                sendFile(clientSocketDescriptor);
            } else if (requestType.compare("operationCall") == 0) {
                cout << "operationCall called" << endl;
                handleOperationCall(clientSocketDescriptor, doc);
            } else {
                cout << "Received an invalid request: " << request << endl;
                const char *buffer = "The request is not valid. No such operation.";
                sendResponse(clientSocketDescriptor, buffer);
            }

            close(clientSocketDescriptor);
        } else {
            waitpid(clientSocketDescriptor, &this->status, WNOHANG);
        }
    }
}

void Server::handleOperationCall(int sd, xml_document &doc) {
    cout << "handleOpertionCall" << endl;
    string name = doc.document_element().child("operation").child("name").child_value();

    cout << name << endl;

    if (name.compare("add") == 0) {
        handleAdd(sd, doc);
    } else if (name.compare("sub") == 0) {

    } else if (name.compare("mul") == 0) {

    } else if (name.compare("div") == 0) {

    } else {
        sendResponse(sd, "<response>The operation is not defined.</response>");
    }
}


void Server::handleAdd(int sd, xml_document &doc) {
    xml_node argument = doc.document_element().child("operation").child("arguments").child("argument");
    int a = stoi(argument.child_value());
    int b = stoi(argument.next_sibling().child_value());

    string result = "<response>" + to_string(a + b) + "</response>";
    sendResponse(sd, result);
}

void Server::sendResponse(int sd, string message) {
    writeInt(sd, message.length());
    writeBuffer(sd, message.c_str());
}

// http://www.cplusplus.com/reference/cstdio/fread/
void Server::sendFile(int socketDescriptor) {
    FILE *file = fopen("/home/ioana/facultate/PROIECT-MY-RPC/myRPC/Server/procedures.xml", "r");

    if (file == NULL) {
        printf("[server]Cannot open file\n");
        exit(1);
    }

    // obtain file size
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    rewind(file);

    // allocate memory to contain the whole file
    char *buffer = (char *) calloc(length + 1, sizeof(char));
    if (buffer == NULL) {
        printf("Memory error\n");
        exit(1);
    }

    // copy the file into the buffer
    size_t result = fread(buffer, 1, length, file);
    if (result != length) {
        printf("Reading error\n");
        exit(1);
    }

    // the whole file is now loaded in the memory buffer
    // send file to client
    sendResponse(socketDescriptor, buffer);

    fclose(file);
    free(buffer);
}








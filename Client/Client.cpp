//
// Created by ioana on 05.01.2018.
//

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "Client.h"
#include "Helpers.h"

using namespace std;

Client::Client(const char ip[], int port) {
    this->ip = new string(ip);
    this->port = port;

    initializeConnectionInfo();
    createSocket();
    connectToServer();
}

void Client::createSocket() {
    if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Error at socket().\n");
        exit(1);
    }
}

void Client::initializeConnectionInfo() {
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip->c_str());
    server.sin_port = htons(port);
}

void Client::connectToServer() {
    if (connect(socketDescriptor, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        printf("[client]Eroare la connect().\n");
        exit(1);
    }
}

void Client::readMessageFromTerminal() {
    // TODO: update
    bzero(this->message, 100);
    printf("[client]Type a name: ");
    fflush(stdout);
    read(0, this->message, 100);
}

void Client::sendMessageToServer() {
    if (write(socketDescriptor, this->message, 100) <= 0) {
        printf("[client]Eroare la write() spre server.\n");
    }
}


string Client::readMessageFromServer() {
    // TODO: update to return message
    if (read(socketDescriptor, this->message, 100) < 0) {
        printf("[client]Error at read()from server.\n");
    }
}

void Client::printMessage() {
    printf("[Client] Received the following message: %s\n", this->message);
}

string Client::getOperationListFromServer() {
    sendOperationListRequestToServer();
    return getOperationListResponseFromServer();

}

string Client::getOperationListResponseFromServer() const {
    int length = readInt(socketDescriptor);
    char *buffer = readBuffer(socketDescriptor, length);

    return string(buffer);
}

void Client::sendOperationListRequestToServer() {
    string request = "<request type=\"operationList\" />";
    writeInt(socketDescriptor, request.length());
    writeBuffer(socketDescriptor, request);
}

string Client::makeOperationRequest(string request) {
    writeInt(socketDescriptor, request.length());
    writeBuffer(socketDescriptor, request);

    int size = readInt(socketDescriptor);
    char* buffer = readBuffer(socketDescriptor, size);

    return string(buffer);
}

Client::~Client() {
    close(socketDescriptor);

}



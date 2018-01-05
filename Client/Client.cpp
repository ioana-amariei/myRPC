//
// Created by ioana on 05.01.2018.
//

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "Client.h"
#include "Helpers.h"


//#include "rapidxml/rapidxml.hpp"
//#include "rapidxml/rapidxml_print.hpp"

using namespace std;
//using namespace rapidxml;


#include "pugixml/src/pugixml.hpp"
#include "pugixml/src/pugixml.cpp"
#include "pugixml/src/pugiconfig.hpp"

using namespace pugi;

#define PORT 2024
char*  HOST_ID = "127.0.0.1";


Client::Client() {
    initializeStructure();
}

int Client::createSocket() {
    int socketDescriptor;

    if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Error at socket().\n");
    }

    return socketDescriptor;
}

sockaddr_in &Client::initializeStructure() {
    server.sin_family = AF_INET;
    /* server IP address (localhost) */
    server.sin_addr.s_addr = inet_addr(HOST_ID);
    /* connection port */
    server.sin_port = htons (PORT);

    return this->server;
}

void Client::connectToServer(int socketDescriptor) {
    if (connect (socketDescriptor, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1) {
        printf("[client]Eroare la connect().\n");
    }
}

void Client::readMessageFromTerminal() {
    bzero(this->message, 100);
    printf ("[client]Type a name: ");
    fflush (stdout);
    read (0, this->message, 100);
}


void Client::sendMessageToServer(int socketDescriptor) {
    if (write (socketDescriptor, this->message, 100) <= 0) {
        printf("[client]Eroare la write() spre server.\n");
    }
}

void Client::readMessageFromServer(int socketDescriptor) {
    if (read(socketDescriptor, this->message, 100) < 0) {
        printf("[client]Error at read()from server.\n");
    }
}

void Client::readBufferFromServer(int socketDescriptor) {
    int length = readInt(socketDescriptor);
    this->buffer = (char*) calloc (length, sizeof(char));
    this->buffer = readBuffer(socketDescriptor, length);
//    printf(buffer);
//
//    xml_document<> doc;
//    doc.parse<parse_non_destructive>(buffer);
//
//    cout << "Name of my first node is: " << doc.first_node()->name() << "\n";
//    xml_node<> *node = doc.first_node();
//    cout << "Node operation has value " << node << "\n";
//    node = node->first_node("operation");
//
//    xml_node<>* sib = 0;
//    while ((sib = node->next_sibling()) != 0) {
//        cout << sib;
//    }

    cout << buffer << endl;

    xml_document doc;
    xml_parse_result result = doc.load_string(buffer);

    if (!result) {
        cout << "parsed with errors" << endl;
        cout << result.description() << endl;
    }

    xml_node operations = doc.document_element();
    for (xml_node operation : operations.children()) {
        cout << "detalii" << endl;
        cout << operation.child("name").child_value() << endl;
        cout << operation.child("resultType").child_value() << endl;
        cout << endl;
    }


}

void Client::printMessage() {
    printf ("[client]Message received is: %s\n", this->message);
}

void Client::closeConnection(int socketDescriptor){
    close(socketDescriptor);
}
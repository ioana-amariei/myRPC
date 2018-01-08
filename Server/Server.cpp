/**
* @author Amariei Ioana
* @date 05.01.2017
* @https://profs.info.uaic.ro/~computernetworks/files/NetEx/S5/servTcpIt.c
*/

#include "Server.h"

#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <iostream>
#include <string>

// https://pugixml.org/docs/quickstart.html#introduction
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

void Server::initializeStructure() {
    /* establishing the family of sockets */
    this->server.sin_family = AF_INET;
    /* accept any address */
    this->server.sin_addr.s_addr = htonl(INADDR_ANY);
    /* use a user port */
    this->server.sin_port = htons(port);
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
            perror("Error at fork().\n");
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

            if (!result) {
                cout << "Parsed with errors" << endl;
                cout << result.description() << endl;
                const char *buffer = "The request is not valid. The XML document could not be parsed.";
                sendResponse(clientSocketDescriptor, buffer);
            } else if (requestType.compare("operationList") == 0) {
                sendFile(clientSocketDescriptor);
            } else if (requestType.compare("operationCall") == 0) {
                handleOperationCall(clientSocketDescriptor, doc);
            } else {
                cout << "Received an invalid request: " << request << endl;
                const char *buffer = "The request is not valid. No such operation.";
                sendResponse(clientSocketDescriptor, buffer);
            }

            close(clientSocketDescriptor);
        } else {
            /**
             * @https://profs.info.uaic.ro/~eonica/rc/lab07e.html
             */
            waitpid(pid, &this->status, WNOHANG);
        }
    }
}

void Server::handleOperationCall(int sd, xml_document &doc) {
    string name = doc.document_element().child("operation").child("name").child_value();

    if (name.compare("add") == 0) {
        handleAdd(sd, doc);
    } else if (name.compare("sub") == 0) {
        handleSub(sd, doc);
    } else if (name.compare("mul") == 0) {
        handleMul(sd, doc);
    } else if (name.compare("div") == 0) {
        handleDiv(sd, doc);
    } else if (name.compare("sum") == 0) {
        handleSum(sd, doc);
    } else if (name.compare("to_uppercase") == 0) {
        handleToUppercase(sd, doc);
    } else {
        sendResponse(sd, "<response>The operation is not defined.</response>");
    }
}

void Server::handleSum(int sd, xml_document &doc) {
    xml_node arguments = doc.document_element().child("operation").child("arguments");

    if (countArguments(arguments) < 1) {
        sendResponse(sd, "<response>The operation must have at least one argument.</response>");
    }


    int sum = 0;
    for (xml_node argument : arguments.children()) {
        int value = stoi(argument.child_value());
        sum += value;
    }


    string result = "<response>" + to_string(sum) + "</response>";
    sendResponse(sd, result);
}

int Server::countArguments(xml_node node) {
    int count = 0;
    for (xml_node arg : node.children()) {
        count++;
    }

    return count;
}

void Server::getArguments(int sd, const xml_document &doc, int &a, int &b) {
    xml_node arguments = doc.document_element().child("operation").child("arguments");
    if (countArguments(arguments) != 2) {
        sendResponse(sd, "<response>The operation must have two arguments.</response>");
    }

    xml_node argument = arguments.child("argument");
    a = stoi(argument.child_value());
    b = stoi(argument.next_sibling().child_value());
}

void Server::handleAdd(int sd, xml_document &doc) {
    int a;
    int b;
    getArguments(sd, doc, a, b);
    string result = "<response>" + to_string(a + b) + "</response>";
    sendResponse(sd, result);
}

void Server::handleSub(int sd, xml_document &doc) {
    int a;
    int b;
    getArguments(sd, doc, a, b);
    string result = "<response>" + to_string(a - b) + "</response>";
    sendResponse(sd, result);
}


void Server::handleMul(int sd, xml_document &doc) {
    int a;
    int b;
    getArguments(sd, doc, a, b);
    string result = "<response>" + to_string(a * b) + "</response>";
    sendResponse(sd, result);
}

void Server::handleDiv(int sd, xml_document &doc) {
    int a;
    int b;
    getArguments(sd, doc, a, b);
    string result = "<response>" + to_string(a / b) + "</response>";
    sendResponse(sd, result);
}

void Server::handleToUppercase(int sd, xml_document &doc) {
    xml_node arguments = doc.document_element().child("operation").child("arguments");
    if (countArguments(arguments) != 1) {
        sendResponse(sd, "<response>The operation must have one argument.</response>");
    }

    string arg = arguments.child("argument").child_value();

    for (char &c : arg) {
        c = toupper(c);
    }

    string result = "<response>" + arg + "</response>";
    sendResponse(sd, result);
}

/**
 * @http://www.cplusplus.com/reference/cstdio/fread/
 */
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

void Server::sendResponse(int sd, string message) {
    writeInt(sd, message.length());
    writeBuffer(sd, message.c_str());
}








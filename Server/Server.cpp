//
// Created by ioana on 05.01.2018.
//

#include "Server.h"

#include <unistd.h>
#include <string.h>
#include <wait.h>


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

void Server::prepareResponseMessage() {
    bzero(this->responseMessage, 100);
    strcat(this->responseMessage, "Hello ");
    strcat(this->responseMessage, this->receivedMessage);
}

/* serve clients in a concurrent way*/
void Server::startServer() {
    while (1) {
        socklen_t length = sizeof(this->from);

        printf("[server]Waiting at port %d...\n", port);
        fflush(stdout);

        int clientSocketDescriptor = accept(socketDescriptor, (struct sockaddr *) &this->from, &length);

        /* eroare la acceptarea conexiunii de la un client */
        if (clientSocketDescriptor < 0) {
            perror("[server]Error at accept().\n");
            continue;
        }

        this->pid = fork();

        if (this->pid < 0) {
            perror("Error at fork(). \n");
            continue;
        }

        if (this->pid == 0) {
            bzero(this->receivedMessage, 100);
            printf("[server]Waiting the message...\n");
            fflush(stdout);

            /* read message */
            if (read(clientSocketDescriptor, this->receivedMessage, 100) <= 0) {
                perror("[server]Error at read() from client.\n");
                /* close this connexion */
                close(clientSocketDescriptor);
                /* keep listening */
                continue;
            }

            printf("[server]Message received...%s\n", this->receivedMessage);

            prepareResponseMessage();

            printf("[server]Send message back...%s\n", this->responseMessage);

            sendFile(clientSocketDescriptor);

            /* return the client's message */
            if (write(clientSocketDescriptor, this->responseMessage, 100) <= 0) {
                perror("[server]Error at write() to the client.\n");
                /* keep listening */
                continue;
            } else {
                printf("[server]The message was successfully passed.\n");
            }
            /* close this connexion */
            close(clientSocketDescriptor);
        } else {
            waitpid(clientSocketDescriptor, &this->status, WNOHANG);
        }
    }
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
    writeInt(socketDescriptor, length);
    writeBuffer(socketDescriptor, buffer);

    // terminate
    fclose(file);
    free(buffer);
}






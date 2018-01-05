//
// Created by ioana on 05.01.2018.
//

#include "Server.h"
//
// Created by ioana on 10.12.2017.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>

#include "Server.h"
#include "Helpers.h"


/* used port */
#define PORT 2024

Server::Server() {
    prepareDataStructures();
    initializeStructure();
}

void Server::prepareDataStructures() {
    bzero(&this->server, sizeof(this->server));
    bzero(&this->from, sizeof(this->from));
}

sockaddr_in &Server::initializeStructure() {
    /* establishing the family of sockets */
    this->server.sin_family = AF_INET;
    /* accept any address */
    this-> server.sin_addr.s_addr = htonl(INADDR_ANY);
    /* use a user port */
    this->server.sin_port = htons(PORT);

    return this->server;
}



int Server::createSocket() {
    int socketDescriptor;
    if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("[server]Error at socket().\n");
    }
    return socketDescriptor;
}

void Server::bindSocket(int socketDescriptor) {
    if (bind(socketDescriptor, (struct sockaddr *) &this->server, sizeof(struct sockaddr)) == -1) {
        printf("[server]Error at bind().\n");
    }
}

void Server::listenConnections(int socketDescriptor) {
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
void Server::serveClients(int socketDescriptor) {
    while (1) {
        int client;
        socklen_t length = sizeof(this->from);

        printf("[server]Waiting at port %d...\n", PORT);
        fflush(stdout);

        client = accept(socketDescriptor, (struct sockaddr *) &this->from, &length);

        /* eroare la acceptarea conexiunii de la un client */
        if (client < 0) {
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
            if (read(client, this->receivedMessage, 100) <= 0) {
                perror("[server]Error at read() from client.\n");
                /* close this connexion */
                close(client);
                /* keep listening */
                continue;
            }

            printf("[server]Message received...%s\n", this->receivedMessage);

            prepareResponseMessage();

            printf("[server]Send message back...%s\n", this->responseMessage);


            /* return the client's message */
            if (write(client, this->responseMessage, 100) <= 0) {
                perror("[server]Error at write() to the client.\n");
                /* keep listening */
                continue;
            } else {
                printf("[server]The message was successfully passed.\n");
            }
            /* close this connexion */
            close(client);
        } else {
            waitpid(client, &this->status, WNOHANG);
        }
    }
}




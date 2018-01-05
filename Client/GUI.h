//
// Created by ioana on 05.01.2018.
//

#ifndef CLIENT_GUI_H
#define CLIENT_GUI_H

#include "Client.h"

class Client;

class GUI {

private:
    Client* client;

public:
    GUI(Client* client);

    void createMainWindow();

    void populateWindowWithOperations(char* operationsBuffer);
};


#endif //CLIENT_GUI_H

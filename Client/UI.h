//
// Created by ioana on 05.01.2018.
//

#ifndef CLIENT_GUI_H
#define CLIENT_GUI_H

#include "Client.h"
#include "pugixml/src/pugixml.hpp"
#include <string>
using namespace std;

class Client;


class UI {
private:
    Client *client;

public:
    UI();

    void startUserInteraction();

private:
    Client newClient();

    void displayAvailableOperations(string string1);

    string obtainRequestFromUser();

    void printResult(string basic_string);

    string encloseTypeIdentifier(string typeIdentifier);
};


#endif //CLIENT_GUI_H

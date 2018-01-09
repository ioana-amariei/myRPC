/**
* @author Amariei Ioana
* @date 05.01.2017
*/

#ifndef CLIENT_GUI_H
#define CLIENT_GUI_H

#include "Client.h"
#include "pugixml/src/pugixml.hpp"
#include <string>
using namespace std;

class Client;


class UI {
private:
    /**
     * client instance
     */
    Client *client;

public:
    UI();

    /**
     * Starts the CLI user interaction.
     */
    void startUserInteraction();

private:
    Client newClient();

    /**
     * Display available procedures.
     * @param string the list of procedures
     */
    void displayAvailableOperations(string string);

    /**
     * Obtain the request from user.
     * @return the string that contains the request
     */
    string obtainRequestFromUser();

    /**
     * Print the result.
     * @param string the result
     */
    void printResult(string result);

    /**
     * Enclose a string identified by typeIdentifier between "<>"
     * @param typeIdentifier the string to be enclosed
     * @return the string enclosed by "<>"
     */
    string encloseTypeIdentifier(string typeIdentifier);
};


#endif //CLIENT_GUI_H

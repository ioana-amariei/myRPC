/**
* @author Amariei Ioana
* @date 05.01.2017
*/

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

    /**
     * the structure used by server
     */
    struct sockaddr_in server;

    struct sockaddr_in from;
    int status;

    /**
     * process id
     */
    int pid;
    /**
     * socket descriptor
     */

    int socketDescriptor;

    /**
     * port used
     */
    int port;

    /**
     * Prepare data structures.
     */
    void prepareDataStructures();

    /**
     * Fill the structure used by the server.
     */
    void initializeStructure();

    /**
     * Fill the structure used by the server.
     * @param socketDescriptor socket descriptor
     */
    void sendFile(int socketDescriptor);

public:
    /**
     * Constructor
     * @param port used port
     */
    Server(int port);

    /**
     * Destructor
     */
    ~Server();

    /**
     * Start server.
     */
    void startServer();

private:

    /**
     * Create socket.
     */
    void createSocket();

    /**
     * Associate the socket with an address.
     */
    void bindSocket();

    /**
     * Passive waiting of connections.
     */
    void listenConnections();

    /**
     * Send response to client.
     * @param sd the socket descriptor
     * @param message the message to be sent
     */
    void sendResponse(int sd, string message);

    /**
     * Handle the operation call.
     * @param sd the socket descriptor
     * @param doc xml document send by client
     */
    void handleOperationCall(int sd, xml_document &document);

    /**
     * Handle add operation.
     * @param sd the socket descriptor
     * @param document the xml document send by client
     */
    void handleAdd(int sd, xml_document &document);

    /**
     * Handle sum operation.
     * @param sd the socket descriptor
     * @param document the xml document send by client
     */
    void handleSum(int sd, xml_document &document);

    /**
     * Handle substract operation.
     * @param sd the socket descriptor
     * @param document the xml document send by client
     */
    void handleSub(int sd, xml_document &document);

    /**
     * Handle multiply operation.
     * @param sd the socket descriptor
     * @param document the xml document send by client
     */
    void handleMul(int sd, xml_document &document);

    /**
     * Handle divide operation.
     * @param sd the socket descriptor
     * @param document the xml document send by client
     */
    void handleDiv(int sd, xml_document &document);

    /**
     * Handle to_uppercase operation.
     * @param sd the socket descriptor
     * @param document the xml document send by client
     */
    void handleToUppercase(int sd, xml_document &document);

    /**
     * Count number of arguments.
     * @param node xml_node for arguments in the xml document
     * @return the number of arguments
     */
    int countArguments(xml_node node);

    /**
     * Obtain arguments.
     * @param sd the socket descriptor
     * @param document the xml document used to obtain the arguments
     * @param a first argument
     * @param b second argument
     */
    void getArguments(int sd, const xml_document &document, int &a, int &b);
};


#endif //MYRPC_SERVER_H

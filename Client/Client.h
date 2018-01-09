/**
* @author Amariei Ioana
* @date 05.01.2017
*/

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <netinet/in.h>
#include <string>
#include "UI.h"

using namespace std;

class Client {
private:
    /**
     * IP address of the server
     */
    string *ip;
    /**
     * server login port
     */
    int port;

    /**
     * the socket descriptor
     */
    int socketDescriptor;
    /**
     * the structure used to connect
     */
    struct sockaddr_in server;

    /**
     * Fill the structure used by the server.
     */
    void initializeConnectionInfo();

    /**
     * Create socket
     */
    void createSocket();

    /**
     * Initiating the connection to the server.
     */
    void connectToServer();

    /**
     * Send procedure list request to server.
     */
    void sendOperationListRequestToServer();

    /**
     * Obtain procedure list from server.
     * @return procedure list
     */
    string getOperationListResponseFromServer();

public:

    /**
     * Constructor.
     * @param ipAddress the IP address of the host
     * @param port port where the service is offered
     */
    Client(const char ipAddress[], int port);

    /**
     * Destructor
     */
    ~Client();

    /**
     * Obtain procedure list from server.
     * @return procedure list
     */
    string getOperationListFromServer();

    /**
     * Make operation request.
     * @param request user request
     * @return string containing the result of the operation
     */
    string makeOperationRequest(string request);
};


#endif //CLIENT_CLIENT_H
# myRPC

### Introduction
Client-server application that simulates the RPC protocol. The server exposes a list of predefined procedures using XML documents, while the client is able to retrieve the list, parse it, send requests to the server, and display the results of the invocations. The communication between the client and the server was done using the Socket API. 

**Tech: C++, pugixml**

### Compile

In terminal run command: cmake .
CMake 3.8 or higher is required. 

### How to use
1. start Server in terminal using command: ./Server
2. start Client in a separate terminal window using command: ./Client
3. in the terminal for Client make request for an operation from the next list:

The list of available operations: 
1. `add <int> <int>`
2. `sub <int> <int>` 
3. `mul <int> <int>` 
4. `div <int> <int>` 
5. `sum <int+>` 
6. `to_uppercase <string>` 

### Libraries
[pugixml](https://pugixml.org/docs/quickstart.html)

### Bibliography
- [https://profs.info.uaic.ro/~computernetworks/cursullaboratorul.php](https://profs.info.uaic.ro/~computernetworks/cursullaboratorul.php)
- [https://profs.info.uaic.ro/~computernetworks/files/NetEx/S5/servTcpIt.c](https://profs.info.uaic.ro/~computernetworks/files/NetEx/S5/servTcpIt.c)
- [https://profs.info.uaic.ro/~computernetworks/files/NetEx/S5/cliTcpIt.c](https://profs.info.uaic.ro/~computernetworks/files/NetEx/S5/cliTcpIt.c)
- [http://www.cplusplus.com/reference/cstdio/fread/](http://www.cplusplus.com/reference/cstdio/fread/)
- [http://csapp.cs.cmu.edu/2e/ch12-preview.pdf](http://csapp.cs.cmu.edu/2e/ch12-preview.pdf)
- [http://www.tenouk.com/Module39.html](http://www.tenouk.com/Module39.html)
- [https://pugixml.org/docs/quickstart.html#access](https://pugixml.org/docs/quickstart.html#access)
- [https://profs.info.uaic.ro/~eonica/rc/lab07e.html](https://profs.info.uaic.ro/~eonica/rc/lab07e.html)
- [http://perso.ensta-paristech.fr/~kielbasi/tikzuml/var/files/html/web-tikz-uml-userguide.html](http://perso.ensta-paristech.fr/~kielbasi/tikzuml/var/files/html/web-tikz-uml-userguide.html)
- [https://en.wikipedia.org/wiki/Client%E2%80%93server_model](https://en.wikipedia.org/wiki/Client%E2%80%93server_model)

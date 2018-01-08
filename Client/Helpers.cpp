//
// Created by ioana on 05.01.2018.
//

//
// Created by ioana on 05.01.2018.
//

#include "Helpers.h"

#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <list>
#include <string>
using namespace std;


int readInt(int socketDescriptor) {
    int value = 0;
    if(read(socketDescriptor, &value, sizeof(value)) == -1){
        printf("Error at reading an integer! \n");
        exit(1);
    }

    return value;
}

void writeInt(int socketDescriptor, int value){
    if(write(socketDescriptor, &value, sizeof(value)) == -1){
        printf("Error at writing integer: %d.\n", value);
        exit(1);
    }
}

char readChar(int socketDescriptor){
    char value = 0;
    if(read(socketDescriptor, &value, sizeof(value)) == -1){
        printf("Error at reading a char! \n");
        exit(1);
    }

    return value;
}

void writeChar(int socketDescriptor, char value){
    if(write(socketDescriptor, &value, sizeof(value)) == -1){
        printf("Error at writing char: %s.\n", value);
        exit(1);
    }
}

char* readBuffer(int socketDescriptor, int length){
    char* buffer = (char*)calloc(length + 1, sizeof(char));

    if(read(socketDescriptor, buffer, length) == -1){
        printf("Error at reading a string! \n");
        exit(1);
    }

    buffer[length] = '\0';

    return buffer;
}

void writeBuffer(int socketDescriptor, const char* buffer){
    int length = strlen(buffer);
    if(write(socketDescriptor, buffer, length) == -1){
        printf("Error at writing string: %d.\n", buffer);
        exit(1);
    }
}

void writeBuffer(int socketDescriptor, string buffer){
    writeBuffer(socketDescriptor, buffer.c_str());
}

// http://www.cplusplus.com/reference/cstring/strtok/
list<string> split(char *str, char* delimiters) {
    list<string> tokens;

    char *token = NULL;

    token = strtok(str, delimiters);
    if(token != NULL){
        tokens.push_back(string(token));
    }

    while (token != NULL) {
        token = strtok(NULL, delimiters);
        if(token != NULL){
            tokens.push_back(string(token));
        }
    }

    return  tokens;
}

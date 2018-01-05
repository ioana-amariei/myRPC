//
// Created by ioana on 05.01.2018.
//

#ifndef CLIENT_HELPERS_H
#define CLIENT_HELPERS_H


#include <string>
using namespace std;

int readInt(int socketDescriptor);

void writeInt(int socketDescriptor, int value);

char readChar(int socketDescriptor);

void writeChar(int socketDescriptor, char value);

char* readBuffer(int socketDescriptor, int length);

void writeBuffer(int socketDescriptor, char *buffer);

#endif //CLIENT_HELPERS_H

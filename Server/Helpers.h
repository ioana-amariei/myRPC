//
// Created by ioana on 05.01.2018.
//

#ifndef MYRPC_HELPERS_H
#define MYRPC_HELPERS_H


#include <string>
using namespace std;

int readInt(int socketDescriptor);

void writeInt(int socketDescriptor, int value);

char readChar(int socketDescriptor);

void writeChar(int socketDescriptor, char value);

char* readBuffer(int socketDescriptor, int length);

void writeBuffer(int socketDescriptor, const char *buffer);


#endif //MYRPC_HELPERS_H



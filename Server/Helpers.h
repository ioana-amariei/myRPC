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

string readBuffer(int socketDescriptor, int length);

void writeBuffer(int socketDescriptor, char *buffer);


#endif //MYRPC_HELPERS_H



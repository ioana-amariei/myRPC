/**
* @author Amariei Ioana
* @date 05.01.2017
*/

#ifndef MYRPC_HELPERS_H
#define MYRPC_HELPERS_H


#include <string>
using namespace std;

/**
 * Read an integer from a the socket identified by the socket descriptor.
 * @param socketDescriptor the socket descriptor from where to read
 * @return the integer value that was read
 */
int readInt(int socketDescriptor);

/**
 * Write an integer to the socket identified by socket descriptor.
 * @param socketDescriptor the socket descriptor where to write
 * @param value the integer value to be written
 */
void writeInt(int socketDescriptor, int value);

/**
 * Read a char from a the socket identified by the socket descriptor.
 * @param socketDescriptor the socket descriptor from where to read
 * @return the char value that was read
 */
char readChar(int socketDescriptor);

/**
 * Write a char to the socket identified by socket descriptor.
 * @param socketDescriptor the socket descriptor where to write
 * @param value the char value to be written
 */
void writeChar(int socketDescriptor, char value);

/**
 * Read a buffer from a the socket identified by the socket descriptor.
 * @param socketDescriptor the socket descriptor from where to read
 * @return the char value that was read
 */
char* readBuffer(int socketDescriptor, int length);

/**
 * Write a buffer to the socket identified by socket descriptor.
 * @param socketDescriptor the socket descriptor where to write
 * @param value the buffer to be written
 */
void writeBuffer(int socketDescriptor, const char *buffer);


#endif //MYRPC_HELPERS_H



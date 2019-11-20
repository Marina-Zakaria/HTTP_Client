#ifndef SENDER_H_INCLUDED
#define SENDER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 100
#define MAX_HEADER_ 500
#define MAX_FILE_SIZE_ 1000

#include "utiles.h"
int formRequest (command_struct* command,char *request);
void bufferFile(char *filePath,char *buffer,int size);

#endif // SENDER_H_INCLUDED

#ifndef UTILES_H
#define UTILES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 100
#define MAX_COMMAND_ 400
#define MAX_FILE_SIZE_ 1000

typedef struct command {
    unsigned char type ;//0for get , 1 for post
    char *filePath ;
    char *hostName;
    char *fileName;
    unsigned short portNumber;
}command_struct;
void DieWithError(char *errorMessage);
int readCommands (char **commands );
command_struct* parseCommand (char *cmd);
int spliter ( char *str, char c, char ***arr);


#endif // UTILES_H

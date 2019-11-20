#ifndef RECIEVER_H_INCLUDED
#define RECIEVER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "utiles.h"
#define MAX_HEADER_ 500


char *getCode(char *httpResponse);
void recieveGetResponse(int socket,FILE* body,FILE* response);
int getContentParam(int *contentStart,char *httpResponse);
void recievePostResponse(int socket,FILE* response);

#endif // RECIEVER_H_INCLUDED

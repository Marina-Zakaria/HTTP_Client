#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <unistd.h>
#include <stdio.h> /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
 #include <arpa/inet.h> /* for sockaddr_in and inet_addr() */
 #include <stdlib.h> /* for atoi() */
 #include <string.h> /* for memset() */
 #include <unistd.h> /* for close() */

#define IPADDRESS_SIZE 32
#include "utiles.h"
#include "sender.h"
#include "reciever.h"



#endif // MAIN_H_INCLUDED

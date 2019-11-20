#include "main.h"




int main(int argc,char *argv[])
{
    printf("Hello world!\n");



    char *serverIP =malloc(IPADDRESS_SIZE);
    serverIP=argv[1];
    unsigned short ServerPortNumber = atoi(argv[2]);
    int sock; /* Socket descriptor */
    struct sockaddr_in ServAddr; /*  server address (IP + PortNumber + Address Family )*/

    /* Create a reliable, stream socket using TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError(" socket () failed") ;

    /* Construct the server address structure */
    memset(&ServAddr, 0, sizeof(ServAddr)); /* Zero out structure */
    ServAddr.sin_family = AF_INET; /* Internet address family */
    ServAddr.sin_addr.s_addr = inet_addr(serverIP); /* Server IP address */
    ServAddr.sin_port = htons(ServerPortNumber); /* Server port */
    printf("from inside client socket id is : %d\n",sock);

    /* Establish the connection to the server */
   if (connect(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) < 0){
        DieWithError(" connect () failed      ") ;

   }
    char **commands=(char**)malloc(sizeof(char)*MAX_COMMAND_*MAX_FILE_SIZE_);
    int count = readCommands(commands);

    int i;
    for(i=0;i<count;i++){
        char *cmd = malloc(MAX_COMMAND_);
        strcpy(cmd,commands[i]);
        command_struct* command = parseCommand(cmd);
        char* request ;
        request=malloc(MAX_HEADER_+MAX_FILE_SIZE_);
        int requestLen = formRequest(command,request);
        printf("\n the request is :%s",request);
        if (send(sock, request, requestLen, 0) != requestLen){
            DieWithError("send() sent a different number of bytes than expected");
        }
        if(command->type=='0'){
            FILE* bodyp,*responsep;
            char * responseFileName=malloc(MAXCHAR);
            strcat(responseFileName,"server response for file :");
            strcat(responseFileName,command->fileName);
            bodyp = fopen(command->fileName, "wb");
            responsep = fopen(responseFileName, "wb");
            recieveGetResponse(sock,bodyp,responsep);
            fclose(bodyp);
            fclose(responsep);
        }else if(command->type=='1'){
            FILE* responsep;
            char * responseFileName=malloc(MAXCHAR);
            strcat(responseFileName,"server response for file : ");
            strcat(responseFileName,command->fileName);
            responsep = fopen(responseFileName, "wb");
            recievePostResponse(sock,responsep);
            fclose(responsep);

        }
    }

    printf("%s   ",serverIP);
    printf("%d",ServerPortNumber);


    return 0;
}


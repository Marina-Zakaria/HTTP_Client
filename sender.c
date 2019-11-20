#include "sender.h"


int formRequest (command_struct* command,char *request){
   //request=malloc(MAX_HEADER_+MAX_FILE_SIZE_);
    if(command->type=='0'){
        strcat(request,"GET ");
        strcat(request,command->filePath);
        strcat(request," HTTP/1.1\n");
        strcat(request,"Host: ");
        strcat(request,command->hostName);
        strcat(request,"\r\n\r\n");

    }else if (command->type=='1'){
    strcat(request,"POST ");
    strcat(request,command->filePath);
    strcat(request," HTTP/1.1\n");
    strcat(request,"Host: ");
    strcat(request,command->hostName);
    strcat(request,"\n");
    FILE * fp;
    fp = fopen(command->filePath, "r");
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    strcat(request,"Content-Length: ");
    char* fileSize=malloc(5) ;
     sprintf( fileSize, "%d",sz);
    strcat(request,fileSize);
    strcat(request,"\r\n\r\n");
    char *buffer=malloc(sz);
    bufferFile(command->filePath,buffer,sz);
    strcat(request,buffer);
    }
    printf("%s,%d\n",request,strlen(request));
    return  strlen(request);

}
void bufferFile(char *filePath,char *buffer,int size){
FILE *fp;
    printf("\n file unopened");
    fp = fopen(filePath, "r");
    printf("\n file opened");

    if (!fp){
        printf("Could not open file %s","test");
        return;
    }
    int count=0;
    while (count<size&&!feof(fp)){
        buffer[count++]=fgetc(fp);
}
    fclose(fp);
}

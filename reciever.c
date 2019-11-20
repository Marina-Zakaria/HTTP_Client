#include "reciever.h"

void recievePostResponse(int socket,FILE* response){
    char* httpResponse = malloc(MAX_HEADER_);

    int totalBufferSize = recv(socket, httpResponse, MAX_HEADER_, 0);
    if(totalBufferSize < 0){
        perror("error receiving packages");
        free(httpResponse);
        return;
    }
    fwrite ( httpResponse , 1 , totalBufferSize , response );
}


void recieveGetResponse(int socket,FILE* body,FILE* response){

char* httpResponse = malloc(MAX_HEADER_+MAX_FILE_SIZE_);
/*httpResponse="HTTP/1.1 200 OK\r\n"
"Date: Thu, 19 Feb 2009 12:27:04 GMT\r\n"
"Content-Length: 18\r\n"
"\r\n"
"sdfkjsdnbfkjbsflll";*/

int totalBufferSize = recv(socket, httpResponse, MAX_HEADER_+MAX_FILE_SIZE_, 0);

if(totalBufferSize <= 0){
        perror("error receiving packages");
        free(httpResponse);
        return;
    }

    fwrite ( httpResponse , 1 , totalBufferSize , response );

char *responseCode=getCode(httpResponse);
    if(strcmp(responseCode,"200")!=0){
        return;
    }
    int contentStart;

   int contentLength=getContentParam(&contentStart,httpResponse);

    if(contentLength <= 0){
        perror("Invalid GET RESPONSE As no content exist in the response");
        return;
    }
    int status=totalBufferSize;
    //int status = recv(socket, httpResponse, contentStart + contentLength, MSG_PEEK);
     char * content=malloc(contentLength+1);
     int current_index=0;

      // we may not receive all the data content completely if the data content is large.
    for(; current_index < status - contentStart; current_index++){
        content[current_index] = httpResponse[current_index + contentStart];
    }
    // continue reading until we finish reading all the content
    while(contentLength - current_index > 1){
        status = recv(socket, (char *)(content + current_index), contentLength - current_index, 0);
        printf("%d\n", status);
        current_index += status;
    }

    fwrite ( content , 1 , contentLength , body );

}
int getContentParam(int *contentStart,char *httpResponse){
char *dest = strstr(httpResponse, "Content-Length");
int pos= dest - httpResponse;
printf("%d\n",pos);
while(httpResponse[pos]<'0'||httpResponse[pos]>'9'){
    pos++;
}
char* contentLength = malloc(10);
int j=0;
while(httpResponse[pos]>='0'&&httpResponse[pos]<='9'){
        contentLength[j++]=httpResponse[pos++];
    }
char *dest1 = strstr(httpResponse, "\r\n\r\n");
pos= dest1 - httpResponse+4;
*contentStart=pos;
return atoi (contentLength);

}
char *getCode(char *httpResponse){
    int i=0;
    char* line1=malloc(MAXCHAR);
    //get first line of response
    while(httpResponse[i]!='\r'&&httpResponse[i]!='\n'){
        line1[i]=httpResponse[i];
        i++;
    }
    i=0;
    //get cursor i to space after protocol version
    while(line1[i]!=' '){
        i++;
    }
    while(line1[i]==' '){
        i++;
    }//get cursor i to first char in response code
    char* code = malloc(4);
    int j=0;
    while(line1[i]>='0'&&line1[i]<='9'){
        code[j++]=line1[i++];
    }
    code[j]='\0';
    return code;
}

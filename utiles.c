#include "utiles.h"

void DieWithError(char *errorMessage)
 {
 perror (errorMessage) ;
 exit(1);
 }


 int readCommands (char **commands ){
    FILE *fp;
    char *str=malloc(MAXCHAR);
    int count=0;
    fp = fopen("command.txt", "r");

    if (!fp){
        printf("Could not open file %s","command");
        return;
    }
        printf("\n file opened\n");
        commands[0]=malloc(MAXCHAR);
    while (fgets(commands[count], MAXCHAR, fp) != NULL){
        count++;
        commands[count]=malloc(MAXCHAR);

    }
    fclose(fp);
    return count;
}



command_struct* parseCommand (char *command){
command_struct* out=malloc(sizeof(command_struct)) ;

int i=0,j=0;
char* cmd=malloc(MAX_COMMAND_*sizeof(char));
strcpy(cmd,command);
char ** split=(char**)malloc(MAX_COMMAND_);
for(i=0;i<4;i++){
    split[i]=(char*)malloc(MAXCHAR);

}
i=0;
while(cmd[i]!='\0'){
    int count =0;
    if(cmd[i]==' '){
        i++;
        continue;
    }

    while(cmd[i]!=' '&&cmd[i]!='\0'){

        split[j][count++]=cmd[i++];

    }
    split[j++][count]='\0';
    printf("%s \n",split[j-1]);
}
if(strcmp(split[0],"client_get")==0){
    out->type='0';


}else if(strcmp(split[0],"client_post")==0){
out->type='1';}
out->filePath=split[1];
char **arr = malloc(MAXCHAR);
int  c = spliter(split[1],'/',&arr);
out->fileName=arr[c-1];
printf("%s\n",out->fileName);
out->hostName=split[2];
out->portNumber=strcmp(split[3],"")==0 ? 0 : atoi(split[3]);
return out;
}

int spliter ( char *str, char c, char ***arr){
    int count = 1;
    int token_len = 1;
    int i = 0;
    char *p;
    char *t;

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
            count++;
        p++;
    }

    *arr = (char**) malloc(sizeof(char*) * count);
    if (*arr == NULL)
        exit(1);

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
        {
            (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
            if ((*arr)[i] == NULL)
                exit(1);

            token_len = 0;
            i++;
        }
        p++;
        token_len++;
    }
    (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
    if ((*arr)[i] == NULL)
        exit(1);

    i = 0;
    p = str;
    t = ((*arr)[i]);
    while (*p != '\0')
    {
        if (*p != c && *p != '\0')
        {
            *t = *p;
            t++;
        }
        else
        {
            *t = '\0';
            i++;
            t = ((*arr)[i]);
        }
        p++;
    }

    return count;
}

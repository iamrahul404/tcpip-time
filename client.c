

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXBUFFER 1024

int main(){
    int clntSock;
    struct sockaddr_in servAddr;
    char *servip = "127.0.0.1";
    char str;
    int stringLen;
    if((clntSock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
        printf("Error at socket creation\n");

    memset(&servAddr,0,sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(7788);
    servAddr.sin_addr.s_addr = inet_addr(servip);

    if (bind(clntSock,(struct sockaddr*)&servAddr, sizeof(servAddr))<0)
        printf("error in binding");

    if (connect(clntSock,(struct sockaddr *)&servAddr,sizeof(servAddr))<0)
        printf("Error in connect\n");

    str = "Hello";
    stringLen = strlen(str);

    if(send(clntSock,str,stringLen,0) != stringLen)
        printf("Error in send\n");


        int n=0;
        int len=0,maxlen=100;
        char buffer[maxlen];
        char* pbuffer = buffer;

        while((n = recv(clntSock,pbuffer,maxlen,0))>0){
            pbuffer += n;
            maxlen -= n;
            len += n;

            buffer[len] = '\0';

            printf("Received %s\n",buffer);
        }

            close(clntSock);

    return 0;
}


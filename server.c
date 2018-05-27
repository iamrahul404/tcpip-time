
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#define MAXPENDING 5


int main(){
    int servSock,clntSock,clntLen;
    struct sockaddr_in servaddr;
    struct sockaddr_in clntaddr;
    char *servIP = "127.0.0.1";

    if((servSock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
        printf("Error in socket creation\n");

    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(7788);
    servaddr.sin_addr.s_addr = inet_addr(servIP);

    if (bind(servSock,(struct sockaddr*)&servaddr, sizeof(servaddr))<0)
        printf("error in binding");

    if(listen(servSock,MAXPENDING)<0)
        printf("Error at listen\n");

    for(;;){
        clntLen = 0;
        if((clntSock = accept(servSock,(struct sockaddr *)&clntaddr ,&clntLen))<0)
            printf("Error at accept\n");
        else
            printf("Connection accepted\n");

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

            send(clntSock,localtime(time(NULL)),maxlen , 0);
        }
        close(clntSock);

    }
    close(servSock);

    return 0;

}
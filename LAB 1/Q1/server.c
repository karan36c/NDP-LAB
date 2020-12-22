#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <stdlib.h>
#include<netinet/in.h>
#define MAX 90

int main(){
    int sockfd, client_sockfd, retval;
    socklen_t socklen;
    int recvdbytes, sentbytes;

    struct sockaddr_in serveraddr, clientaddr;

    char buff[MAX];

    int a = 0;
    
    if((sockfd = socket(AF_INET, SOCK_STREAM,0)) == -1){
        printf("Socket create failed.\n");
        exit(1);
    }
    printf("Socket created successfully.\n");
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(4000);
    serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
    if((retval = bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)))==-1){ 
        printf("Socket binding failed\n");
        exit(1);
    }
    printf("Socket binded successfully.\n");
    socklen=sizeof(clientaddr);
    
    if((retval=listen(sockfd,5))==-1){
        printf("Socket could not listen.\n");
        exit(1);
        close(sockfd);
    }
    printf("Socket listening....\n");
    
    if((client_sockfd = accept(sockfd, (struct sockaddr *)&clientaddr,&socklen)) == -1){
        printf("Could not accept client.\n");
        close(sockfd);
        exit(1);
    }
    printf("Client accepted.\n");
    
    while(1) {
        if((recvdbytes=recv(client_sockfd,buff,sizeof(buff),0)) == -1){
            close(client_sockfd);
            close(sockfd);
        }

        puts(buff);
        printf("\n");
        printf("Enter your message: ");
        scanf("%s", buff);

            if((sentbytes=send(client_sockfd, buff, sizeof(buff),0)) == -1){
                close(client_sockfd);
                close(sockfd);
            }

    }
    

    close(client_sockfd);
    close(sockfd);






}
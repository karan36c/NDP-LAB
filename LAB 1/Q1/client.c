#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include <stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAX 50

int main() { 
    int sockfd, retval;
    int recvdbytes, sentbytes;
    struct sockaddr_in serveraddr;
    char buff[MAX];

    if((sockfd = socket(AF_INET, SOCK_STREAM,0)) == -1 ) {
        printf("Socket creation failed\n");
        exit(1);
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4000);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if((retval = connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) ==-1) {
        printf("\nCould not connect to the server.\n");
        exit(1);
    }
    printf("\nConnected successfully!\n");

    while(1) {
        int choice = 4;
        printf("Enter 5 numbers: ");
        scanf("%s",buff);
        printf("1. Search a number\n");
        printf("2. Sort \n");
        printf("3. Split \n");
        printf("4. Exit \n");
        scanf("%d", &choice);
        int search_num;
        int sort_order=1;
        switch (choice)
        {
        case 1:
            printf("Number: ");
            scanf("%d", &search_num);
            buff[6] = choice;
            buff[7] = search_num;
            if((sentbytes=send(sockfd, buff,sizeof(buff),0)) == -1) {
                printf("Could not send the data.\n");
                exit(1);
            }

            recvdbytes=recv(sockfd,buff,sizeof(buff),0);
            puts(buff);
            printf("\n");
            close(sockfd);
            break;
        case 2:
            printf("Ascending(1) or Descending(2)?: ");
            scanf("%d", &sort_order);
            buff[6] = choice;
            buff[7] = sort_order;
            if((sentbytes=send(sockfd, buff,sizeof(buff),0)) == -1) {
                printf("Could not send the data.\n");
                exit(1);
            }

            recvdbytes=recv(sockfd,buff,sizeof(buff),0);
            puts(buff);
            printf("\n");
            close(sockfd);
            break;
        case 3:
            buff[6] = choice;
            if((sentbytes=send(sockfd, buff,sizeof(buff),0)) == -1) {
                printf("Could not send the data.\n");
                exit(1);
            }

            recvdbytes=recv(sockfd,buff,sizeof(buff),0);
            puts(buff);
            printf("\n");
            close(sockfd);
            break;
        case 4: 
            printf("Exiting...\n");
            close(sockfd);
            exit(0);
        default:
            break;
        }
    }

    
}
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>

int main()
{
	int sockfd,retval,recvdbytes,sentbytes,PORT;
	int sa;
	socklen_t socklen;
	printf("PORT: ");
	scanf("%d", &PORT);

	struct sockaddr_in server,client;
	char buff[50];

	// socket creation and initialization
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		printf("\nSocket creation failed.");
		exit(0);
	}
	printf("\nSocket created successfully.");
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	sa=sizeof(server);
	socklen=sizeof(server);

while(1){
	
	printf("\n\n");
	printf("String: ");
	scanf("%s", buff);
	if(!strcmp(buff,"halt"))
		break;
	// send string
	if((sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&server, socklen))==-1)
	{
		close(sockfd);
		printf("\nFailed to send");
		exit(0);
	}

	// receive string
	if((recvdbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&server,&sa))==-1)
	{
		printf("\nFailed to receive");	
		close(sockfd);
		exit(0);
	}
	// check the received buffer for palindrome
	if(buff[0]==1)
	printf("\nString is PALINDROME\n Length:  %d \n Vowels:  %d ",buff[1],buff[2]);
	else
		printf("\nString is NOT PALINDROME\n Length: %d \n Vowels: %d ",buff[1],buff[2]);

	}
	close(sockfd);

}
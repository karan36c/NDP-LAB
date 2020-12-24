#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
	int sockfd,retval,recvdbytes,sentbytes,PORT;
	int ca;
	printf("PORT: ");
	scanf("%d", &PORT);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50];

	
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		printf("\nSocket creation failed.");
		exit(0);
	}
	printf("\nSocket created successfully.");

	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	len=sizeof(client);
	ca=sizeof(client);

	
	if((retval=bind(sockfd,(struct sockaddr*)&server,sizeof(server)))==-1)
		{
		printf("\nSocket binding failed..");
		exit(0);
	}
	printf("\nSocket binding successful.");

while(1){

	recvdbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
	if(recvdbytes==-1)
	{
		printf("\nFailed to receive message from client");		
		close(sockfd);
		exit(0);
	}	
	
	printf("\nMessage: ");
	printf("%s", buff);

	if(!strcmp(buff,"halt"))
		break;

	printf("\n\n");
	printf("Message: ");
	scanf("%s", buff);
	
	sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
	if(sentbytes==-1)
	{
		printf("\nFailed to send the message");
		close(sockfd);
		exit(0);
	}
	
	if(!strcmp(buff,"halt"))
		break;

}
	close(sockfd);
}
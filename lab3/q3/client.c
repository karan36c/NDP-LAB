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
	printf("PORT: ");
	scanf("%d", &PORT);
	struct sockaddr_in server;
	char buff[50];
	// socket creation
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	retval=connect(sockfd,(struct sockaddr*)&server,sizeof(server));
	if(retval==-1)
	{
		printf("\nConnection error.");
		exit(0);
	}
	printf("\nSocket connected.\n");
	printf("\n\n");
	strcpy(buff,"");
	printf("Enter alphanumeric string: ");
	scanf("%s", buff);

	sentbytes=send(sockfd,buff,sizeof(buff),0);
	if(sentbytes==-1)
	{
		close(sockfd);
		printf("\nMessage Sending Failed");
		exit(0);
	}
	close(sockfd);

}
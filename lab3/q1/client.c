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
	char buff[50],buff2[50];
	// socket creation
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	// server creation
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

// 	connect
	retval=connect(sockfd,(struct sockaddr*)&server,sizeof(server));
	if(retval==-1)
	{
		printf("\nConnection error.");
		exit(0);
	}
	printf("\nSocket connected.");
	
	printf("\n\n");
	int pid=fork();
	// get pid
	while(1){
		// check parent or child
		if(pid>0) {
			//server
			recvdbytes=recv(sockfd,buff,sizeof(buff),0);
			if(recvdbytes==-1)
			{
			printf("\nFailed to receive");	
			close(sockfd);
			exit(0);
			}
			if(strcmp(buff,"exit")==0)
				break;
			printf("\nServer: ");
			printf("%s\n", buff);
		} else {
			//client
			printf("\nClient: ");
			scanf("%s", buff2);

			sentbytes=send(sockfd,buff2,sizeof(buff2),0);
			if(sentbytes==-1)
			{
				close(sockfd);
				printf("\nFailed to send");
				exit(0);
			}
			if(strcmp(buff2,"exit")==0)
				break;
		}
	}

	close(sockfd);

}
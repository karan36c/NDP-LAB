#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
	int sockfd,retval,recvdbytes,sentbytes,PORT,client_sockfd,a=0;
	printf("PORT: ");
	scanf("%d", &PORT);
	socklen_t socklen;
	struct sockaddr_in server,client;
	char buff[50],buff2[50];

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
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	retval=bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	if(retval==-1)
	{
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.");

	retval=listen(sockfd,1);
	if(retval==-1)
	{
		close(sockfd);
		exit(0);
	}
	printf("\nSocket listening.");

	socklen=sizeof(client);

	client_sockfd=accept(sockfd,(struct sockaddr*)&client, &socklen);
	if(client_sockfd==-1)
	{
		close(sockfd);
		exit(0);
	}
	printf("\nSocket accepting.\n");
	int pid=fork();

	// Chat start
	while(1) {
	if(pid>0) {
		//parent
		printf("\nServer: ");
		scanf("%s", buff2);
	// send message
		sentbytes=send(client_sockfd,buff2,sizeof(buff2),0);
		if(sentbytes==-1)
		{
			printf("\nFailed to send");
			close(sockfd);
			close(client_sockfd);
			exit(0);
		}
		if(strcmp(buff2,"exit")==0)
			break;
		} else {
		//receive from client
			recvdbytes=recv(client_sockfd,buff,sizeof(buff),0);
			if(recvdbytes==-1) {
				printf("\nFailed to receive");		
				close(sockfd);
				close(client_sockfd);
				exit(0);
			}	
			if(strcmp(buff,"exit")==0)
				break;
			printf("\nClient: ");
			printf("%s\n", buff);

		}
	}
	
	close(client_sockfd);
	close(sockfd);
}
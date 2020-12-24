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
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	sa=sizeof(server);
	socklen=sizeof(server);

while(1){
	
	printf("\n\n");
	printf("Message: ");
	scanf("%s", buff);

	sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&server, socklen);
	if(sentbytes==-1)
	{
		close(sockfd);
		printf("\nMessage sending Failed");
		exit(0);
	}
	if(!strcmp(buff,"stop"))
		break;
	}
	close(sockfd);

}
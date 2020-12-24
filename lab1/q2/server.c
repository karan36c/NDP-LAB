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
	socklen_t socklen;
	struct sockaddr_in server,client;
	char buff[50];

	// socket creation and configuration
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created successfully.");

	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	socklen=sizeof(client);
	ca=sizeof(client);

// socket binding
	retval=bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	if(retval==-1)
		{
		printf("\nBinding failed.");
		exit(0);
	}
	printf("\nSocket binding successful.");
while(1){
// receive the string
	recvdbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
	if(recvdbytes==-1)
	{
		printf("\nFailed to receive");		
		close(sockfd);
		exit(0);
	}	
	// check if it is halt
	printf("\nMessage: ");
	printf("%s\n", buff);
	if(!strcmp(buff,"halt"))
		break;
	

	char buff2[50];
	strcpy(buff2,buff);
	buff[1]=strlen(buff2);
	int count=0;

	// vowel count
	for(int i=0;i<buff[1];i++)
		if(buff2[i]=='a'||buff2[i]=='e'||buff2[i]=='o'||buff2[i]=='i'||buff2[i]=='u')
			count++;
	buff[2]=count;
	buff[0]=1;
	// check for palindrome by comparing the original string
	for(int i=0;i<buff[1]/2;i++)
	{
		if(buff2[i]!=buff2[buff[1]-i-1])
		{
			buff[0]=0;
			break;
		}
	}
	// send the result
	sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,socklen);
	if(sentbytes==-1)
	{
		printf("\nFailed to receive");
		close(sockfd);
		exit(0);
	}
	
	if(!strcmp(buff,"halt"))
		break;

}
	close(sockfd);
}
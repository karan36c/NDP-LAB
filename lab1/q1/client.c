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
	
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		printf("\nSocket creation failed.");
		exit(0);
	}
	printf("\nSocket created successfully.");

	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	
	if((retval=connect(sockfd,(struct sockaddr*)&server,sizeof(server)))==-1)
	{
		printf("\nConnection error.");
		exit(0);
	}
	printf("\nSocket connected.");
	
	int choice=1;
	int numset[50];
	char char_numset[50];
	int n;
	int search_num=0;
	printf("\nSize: ");
	scanf("%d",&n);

	printf("\nEnter numbers: ");
	for(int i=0;i<n;i++)
		scanf("%d",&numset[i]);
	for(int i=0;i<n;i++)
		char_numset[i]=numset[i];
	

	if((sentbytes=send(sockfd,char_numset,sizeof(char_numset),0))==-1)
	{
		close(sockfd);
		printf("\nMessage Sending Failed");
		exit(0);
	}
	while(choice!=5)
	{
	printf("\n1.Search number\n2.Sort in ascending order\n3.Sort in descending order\n4.Split into odd and even arrays\n5.EXIT");
	printf("\nChoice: ");
	scanf("%d", &choice);
	switch(choice)
	{
		case 1: printf("\nNumber to be searched: ");
				scanf("%d",&search_num);
				buff[0]=n;
				buff[1]=choice;
				buff[2]=search_num;
				if((sentbytes=send(sockfd,buff,sizeof(buff),0))==-1)
				{
					close(sockfd);
					printf("\nMessage could not be sent.");
					exit(0);
				}
				break;
		case 2: buff[0]=n;
				buff[1]=choice;
				if((sentbytes=send(sockfd,buff,sizeof(buff),0))==-1)
				{
					printf("\nMessage could not be sent.");
					close(sockfd);
					exit(0);
				}
				break;
		case 3: buff[0]=n;
				buff[1]=choice;
				if((sentbytes=send(sockfd,buff,sizeof(buff),0))==-1)
				{
					printf("\nMessage could not be sent.");
					close(sockfd);
					exit(0);
				}
				break;
		case 4: buff[0]=n;
				buff[1]=choice;
				if((sentbytes=send(sockfd,buff,sizeof(buff),0))==-1)
				{
					printf("\nMessage could not be sent.");
					close(sockfd);
					exit(0);
				}
				break;
		case 5: buff[0]=n;
				buff[1]=choice;
				if((sentbytes=send(sockfd,buff,sizeof(buff),0))==-1)
				{
					printf("\nMessage could not be sent.");
					close(sockfd);
					exit(0);
				}
				break;
		default: printf("\n Invalid choice\n");

	}
}
	close(sockfd);

}
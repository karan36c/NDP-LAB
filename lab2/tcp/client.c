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
		printf("\nSocket creation failed.");
		exit(0);
	}
	printf("\nSocket created successfully.");
	// server creation
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	// connect
	if((retval=connect(sockfd,(struct sockaddr*)&server,sizeof(server)))==-1)
	{
		printf("\nConnection failed.");
		exit(0);
	}
	printf("\nSocket connected.");
	
	printf("\n\n");
	printf("File Name: ");
	scanf("%s", buff);

	sentbytes=send(sockfd,buff,sizeof(buff),0);
	if(sentbytes==-1)
	{
		close(sockfd);
		printf("\nFailed to send.");
		exit(0);
	}
	recvdbytes=recv(sockfd,buff,sizeof(buff),0);
	if(recvdbytes==-1)
	{
		printf("\nFailed to receive.");	
		close(sockfd);
		exit(0);
	}
	
	printf("\n");
	printf("%s", buff);
	printf("\n\n");
	if(strcmp(buff,"File NOT found.")==0)
	{
		close(sockfd);
		exit(0);
	}
	int choice=0;
	while(choice!=4)
	{
		printf("\n1.Search\n2.Replace\n3.Reorder\n4.Exit\n");
		printf("\nChoice: ");
		scanf("%d",&choice);
		buff[0]=choice;

		char str1[50],str2[50];
		int n,i,j;
		switch(choice)
		{
			case 1:printf("\nString to be searched: ");
			scanf("%s",str1);
			n=strlen(str1);
			buff[1]=n;
			for(i=0;i<n;i++)
				buff[i+2]=str1[i];
			buff[i+2]='\0';

			
			if((sentbytes=send(sockfd,buff,sizeof(buff),0))==-1)
			{
				close(sockfd);
				printf("\nFailed to send.");
				exit(0);
			}
			
			if((recvdbytes=recv(sockfd,buff,sizeof(buff),0))==-1)
			{
				printf("\nFailed to receive\n");	
				close(sockfd);
				exit(0);
			}
			n=buff[0];
			printf("\nWord count: %d\n",n);
			break;
			
			case 2:printf("\nString to be searched and replaced: ");
			scanf("%s",str1);
			n=strlen(str1);
			buff[1]=n;

			for(i=0;i<n;i++)
				buff[i+2]=str1[i];
			buff[i+2]='\0';

			sentbytes=send(sockfd,buff,sizeof(buff),0);
			if(sentbytes==-1)
			{
				close(sockfd);
				printf("\nFailed to send.");
				exit(0);
			}
			printf("\nNew string: ");
			scanf("%s",str2);
			n=strlen(str2);

			buff[1]=n;
			i=2;
			for(j=0;j<n;j++)
			{
				buff[i]=str2[j];
				i++;
			}
			buff[i]='\0';
			
			if((sentbytes=send(sockfd,buff,sizeof(buff),0))==-1)
			{
			close(sockfd);
			printf("\nFailed to send.");
			exit(0);
			}
			
			if((recvdbytes=recv(sockfd,buff,sizeof(buff),0))==-1)
			{
			printf("\nFailed to receive\n");	
			close(sockfd);
			exit(0);
			}
			printf("%s\n",buff);
			break;
			case 3:
			
					if((sentbytes=send(sockfd,buff,sizeof(buff),0))==-1)
					{
						close(sockfd);
						printf("\nFailed to send.");
						exit(0);
					}
					recvdbytes=recv(sockfd,buff,sizeof(buff),0);
			if(recvdbytes==-1)
			{
			printf("\nFailed to receive\n");	
			close(sockfd);
			exit(0);
			}
			printf("%s\n",buff);
			break;
			case 4:
			
					if((sentbytes=send(sockfd,buff,sizeof(buff),0))==-1)
					{
						close(sockfd);
						printf("\nFailed to send.");
						exit(0);
					}
			break;
			default:
			printf("\n Try Again!\n");
		}
	}
	close(sockfd);

}
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
	char buff[50];

	
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		printf("\nSocket creation failed.");
		exit(0);
	}
	printf("\nSocket created successfully.");

	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	retval=bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	if(retval==-1)
	{
		printf("\nSocket could not be binded.");
		exit(0);
	}

	printf("\nSocket bind successful.");

	retval=listen(sockfd,1);
	if(retval==-1)
	{
		close(sockfd);
		exit(0);
	}
	printf("\nSocket listening...");

	socklen=sizeof(client);

	client_sockfd=accept(sockfd,(struct sockaddr*)&client, &socklen);
	if(client_sockfd==-1)
	{
		close(sockfd);
		exit(0);
	}
	printf("\nClient accepted.");

	char char_numset[50];

    
	if((recvdbytes=recv(client_sockfd,char_numset,sizeof(char_numset),0))==-1)
	{
		printf("\nFailed to receive message from client.");	
		close(sockfd);
		close(client_sockfd);
		exit(0);
	}	
	printf("\nNumber set received\n");
	int choice=1,n,search_number=1;
	while(choice!=5)
	{
		
		if((recvdbytes=recv(client_sockfd,buff,sizeof(buff),0))==-1)
		{
		printf("\nFailed to receive message from client.");		
		close(sockfd);
		close(client_sockfd);
		exit(0);
		}	
		n=buff[0];
		choice=buff[1];
		int l=0,k=0;
		switch(choice)
		{
			case 1: search_number=buff[2];
					for(int i=0;i<n;i++)
					{
						if(char_numset[i]==search_number) {
							int pos = i + 1;
							printf("\nNumber found at position: %d",pos);
							break;
						}
					}
					printf("\nNumber NOT found.");
					break;
					// ASCENDING ORDER
			case 2: for(int i=0;i<n-1;i++)
					{
						for(int j=0;j<n-i-1;j++)
							{
								if(char_numset[j]>char_numset[j+1])
								{
									int temp=char_numset[j];
									char_numset[j]=char_numset[j+1];
									char_numset[j+1]=temp;
								}
							}
					}
					printf("\nSorted array is: \n");
					for(int i=0;i<n;i++)
						printf("%d  ",char_numset[i]);
					printf("\n\n");
					break;
				// DESCENDING ORDER
			case 3: for(int i=0;i<n-1;i++)
					{
						for(int j=0;j<n-i-1;j++)
							{
								if(char_numset[j]<char_numset[j+1])
								{
									int temp=char_numset[j];
									char_numset[j]=char_numset[j+1];
									char_numset[j+1]=temp;
								}
							}
					}
					printf("\nSorted array is: \n");
					for(int i=0;i<n;i++)
						printf("%d  ",char_numset[i]);
					printf("\n\n");
					break;
			case 4: 
			printf("\nEven array: \n");
					for(int i=0;i<n;i++)
					{
						if(char_numset[i]%2==0)
							printf("%d ",char_numset[i]);
					}
					printf("\nOdd array is: \n");
					for(int i=0;i<n;i++)
					{
						if(char_numset[i]%2!=0)
							printf("%d ",char_numset[i]);
					}
					printf("\n\n");
					break;
			case 5: printf("Client exited.\n"); break;
			default: break;
		}
	}
	close(client_sockfd);
	close(sockfd);
}
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
	int sockfd,retval,recvdbtyes,sentbytes,PORT,client_sockfd,a=0;
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

// socket binding
	retval=bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	if(retval==-1)
	{
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.");

// socket listening
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
	// receive string
	recvdbtyes=recv(client_sockfd,buff,sizeof(buff),0);
	if(recvdbtyes==-1)
	{
		printf("\nFailed to receive.");		
		close(sockfd);
		close(client_sockfd);
		exit(0);
	}	
	printf("\nMessage: ");
	printf("%s\n", buff);
		int pid=fork();

		// check the pid
	if(pid>0){
		//if parent
	char num_string[50]={0},alpha_string[50]={0};
	int i=0,j=0,k=0;
		int n=strlen(buff);
		// sort string
	for(i=0;i<n;i++)
		{
			if((buff[i]>=65 && buff[i]<=91)||(buff[i]>=97 && buff[i]<=123))
			{
				alpha_string[j]=buff[i];
				j++;
			}
			else
			{
				num_string[k]=buff[i];
				k++;
			}
		}
		alpha_string[j]='\0';
		num_string[k]='\0';
		for(i=0;i<j-1;i++)
		{
			for(int x=0;x<j-i-1;x++)
			{
				if(alpha_string[x]<alpha_string[x+1])
				{
					char temp=alpha_string[x];
					alpha_string[x]=alpha_string[x+1];
					alpha_string[x+1]=temp;
				}
			}
		}
		printf("\nSorted alphabetical string is(PARENT): \n");
		printf("%s\n",alpha_string );
		printf("\n\n");
	}
	else {
		//if child
		
	char num[50]={0},alpha_string[50]={0};
	int i=0,j=0,k=0;
		int n=strlen(buff);
		// sort string
	for(i=0;i<n;i++)
		{
			if((buff[i]>=65 && buff[i]<=91)||(buff[i]>=97 && buff[i]<=123))
			{
				alpha_string[j]=buff[i];
				j++;
			}
			else
			{
				num[k]=buff[i];
				k++;
			}
		}
		alpha_string[j]='\0';
		num[k]='\0';
		for(i=0;i<k-1;i++)
		{
			for(int x=0;x<k-i-1;x++)
			{
				if(num[x]>num[x+1])
				{
					char temp=num[x];
					num[x]=num[x+1];
					num[x+1]=temp;
				}
			}
		}
		printf("\nSorted numerical string is(CHILD): \n");
		printf("%s\n", num);
		printf("\n\n");
	
	}
	

	close(client_sockfd);
	close(sockfd);
}
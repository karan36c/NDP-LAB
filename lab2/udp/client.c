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
	int sockfd,retval,recvdbytes,sentbytes,x;
	int sa;
	socklen_t len;
	printf("PORT: ");
	scanf("%d", &x);
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
	server.sin_port=htons(x);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	sa=sizeof(server);
	len=sizeof(server);
	printf("\n\n");
	printf("File Name: ");
	scanf("%s", buff);
	sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&server, len);
	if(sentbytes==-1)
	{
		close(sockfd);
		printf("\nMessage sending Failed");
		exit(0);
	}
	recvdbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&server,&sa);
	if(recvdbytes==-1)
	{
		printf("\nFailed to receive.");	
		close(sockfd);
		exit(0);
	}
	printf("\n");
	printf("%s", buff);
	printf("\n\n");
	if(strcmp(buff,"File NOT found")==0)
	{
		close(sockfd);
		exit(0);
	}
	int ch=0;
	while(ch!=4)
	{
		printf("\n1.Search\n2.Replace\n3.Reorder\n4.Exit\nEnter your choice: ");
		scanf("%d",&ch);
		buff[0]=ch;
		char str1[50],str2[50];
		int n,i,j;
		switch(ch)
		{
			case 1:printf("\nString to be searched: ");
			scanf("%s",str1);
			n=strlen(str1);
			buff[1]=n;
			for(i=0;i<n;i++)
				buff[i+2]=str1[i];
			buff[i+2]='\0';
			sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&server, len);
	       if(sentbytes==-1)
	       {
	       	close(sockfd);
	       	printf("\nMessage sending Failed");
	       	exit(0);
	       }
			recvdbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&server,&sa);
	       if(recvdbytes==-1)
	       {
		      printf("\nFailed to receive.");	
		      close(sockfd);
		      exit(0);
	       }
			n=buff[0];
			printf("\nWord count: %d\n",n);
			break;

			case 2:printf("\nEnter string to be searched and replaced: ");
			scanf("%s",str1);
			n=strlen(str1);
			buff[1]=n;
			for(i=0;i<n;i++)
				buff[i+2]=str1[i];
			buff[i+2]='\0';
			
			sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&server, len);

	       if(sentbytes==-1)
	       {
	       	close(sockfd);
	       	printf("\nMessage sending Failed");
	       	exit(0);
	       }

		//    new string
			printf("\nEnter new string: ");
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
			sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&server, len);
	       if(sentbytes==-1)
	       {
	       	close(sockfd);
	       	printf("\nMessage sending Failed");
	       	exit(0);
	       }
			recvdbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&server,&sa);
	       if(recvdbytes==-1)
	       {
	       	printf("\nFailed to receive.");	
	       	close(sockfd);
	       	exit(0);
	       }
			printf("%s\n",buff);
			break;

			case 3:sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&server, len);
	       if(sentbytes==-1)
	       {
	          	close(sockfd);
	       	printf("\nMessage sending Failed");
	       	exit(0);
	       }
					recvdbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&server,&sa);
	       if(recvdbytes==-1)
	       {
	       	printf("\nFailed to receive.");	
	       	close(sockfd);
	       	exit(0);
	       }
			printf("%s\n",buff);
			break;
			case 4:sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&server, len);
	       if(sentbytes==-1)
	       {
	       	close(sockfd);
	              	printf("\nMessage sending Failed");
		      exit(0);
	       }
			break;
			default:
			break;
		}
	}
	close(sockfd);

}
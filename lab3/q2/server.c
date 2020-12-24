#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
void swap(char *a, char *b) 
{ 
    char temp; 
    temp = *a; 
    *a = *b; 
    *b = temp; 
} 
void permute(char *a, int left, int right) 
{ 
   int i; 
   if (left == right) 
     printf("%s\n", a); 
   else { 
       for (i = left; i <= right; i++) { 
          swap((a+left), (a+i)); 
          permute(a, left+1, right); 
          swap((a+left), (a+i)); 
       } 
   } 
} 
int main()
{
	int sockfd,retval,recvdbytes,sentbytes,PORT;
	int ca;
	printf("PORT: ");
	scanf("%d", &PORT);
	socklen_t socklen;
	struct sockaddr_in server,client;
	char buff[50];

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.\n");

	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	socklen=sizeof(client);
	ca=sizeof(client);

	retval=bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	if(retval==-1)
		{
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.\n");

while(1){

	recvdbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
	if(recvdbytes==-1)
	{
		printf("\nFailed to receive.");		
		close(sockfd);
		exit(0);
	}	
	
	printf("\nMessage: ");
	printf("%s", buff);

	if(!strcmp(buff,"stop"))
		break;

	printf("\nPermutations: \n");
	int n=strlen(buff);
	permute(buff, 0, n-1);

}
	close(sockfd);
}
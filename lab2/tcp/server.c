#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#define MAX_LEN 100
void replaceAll(char *str, const char *old, const char *new)
{
    char *pos, temp[1000];
    int index = 0;
    int old_len;

    old_len = strlen(old);
    while ((pos = strstr(str, old)) != NULL)
    {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, new);
        strcat(str, temp + index + old_len);
    }
}
int main()
{
	int sockfd,retval,recvdbytes,sentbytes,PORT,client_sockfd,a=0;
	printf("PORT: ");
	scanf("%d", &PORT);
	socklen_t socklen;
	struct sockaddr_in server,client;
	char buff[50];

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

	retval=listen(sockfd,1);
	if(retval==-1)
	{
		close(sockfd);
		exit(0);
	}
	printf("\nSocket listening.\n");

	socklen=sizeof(client);

	client_sockfd=accept(sockfd,(struct sockaddr*)&client, &socklen);
	if(client_sockfd==-1)
	{
		close(sockfd);
		exit(0);
	}
	printf("\nSocket accepting.\n");

	recvdbytes=recv(client_sockfd,buff,sizeof(buff),0);
	if(recvdbytes==-1)
	{
		printf("\nFailed to receive.");		
		close(sockfd);
		close(client_sockfd);
		exit(0);
	}	
	printf("\nFile Name received!\n");

	char file_name[50];
	// check if file is accessible
	if( access( buff, F_OK ) != -1 ) {
    // file exists
		strcpy(file_name,buff);
		strcpy(buff,"File found");
	} else {
    // file doesn't exist
		strcpy(buff,"File NOT found.");
	}

//  send file access message
	sentbytes=send(client_sockfd,buff,sizeof(buff),0);
	if(sentbytes==-1)
	{
		printf("\nMessage Sending Failed");
		close(sockfd);
		close(client_sockfd);
		exit(0);
	}
	if(strcmp(buff,"File NOT found")==0)
	{
		close(sockfd);
		close(client_sockfd);
		exit(0);
	}
	int choice=0;
	while(choice!=4){

		recvdbytes=recv(client_sockfd,buff,sizeof(buff),0);
		if(recvdbytes==-1)
		{
			printf("\nFailed to receive.");		
			close(sockfd);
			close(client_sockfd);
			exit(0);
		}	
		choice = buff[0];
		int i,n,first_len,second_len,j;
		char str[50],str1[50],str2[50];
		char strTempData[MAX_LEN];
		// string data
		char **str_data = NULL; 
		// number of lines
		int line_num = 0;

		switch(choice)
		{
			// SEARCH
			case 1:
			printf("\nSearching..\n");
			n=buff[1];
			for(i=0;i<n;i++)
				str[i]=buff[i+2];
			str[n]='\0';

			FILE *file_pointer;
			int line_count = 1;
			int word_count = 0;
			char temp[512];
			if((file_pointer = fopen(file_name, "r")) == NULL) {
				printf("\nFile not found");		
				close(sockfd);
				close(client_sockfd);
				exit(0);
			}
			while(fgets(temp, 512, file_pointer) != NULL) {
				if((strstr(temp, str)) != NULL) {
					word_count++;
				}
				// increment line count
				line_count++;
			}
			// close the file
			if(file_pointer) {
				fclose(file_pointer);
			}
			buff[0]=word_count;
			sentbytes=send(client_sockfd,buff,sizeof(buff),0);
			if(sentbytes==-1)
			{
				printf("\nMessage Sending Failed");
				close(sockfd);
				close(client_sockfd);
				exit(0);
			}
			break;

	// REPLACE
			case 2:
			first_len=buff[1];
			i=2;
			for(j=0;j<first_len;j++)
			{
				str1[j]=buff[i];
				i++;
			}
			str1[j]='\0';
			recvdbytes=recv(client_sockfd,buff,sizeof(buff),0);
			if(recvdbytes==-1)
			{
				printf("\nFailed to receive.");		
				close(sockfd);
				close(client_sockfd);
				exit(0);
			}	
			n=buff[1];
			i=2;
			for(j=0;j<n;j++)
			{
				str2[j]=buff[i];
				i++;
			}
			str2[j]='\0';
			printf("\nReplacing %s with %s..\n",str1,str2);
			FILE * f_ptr;
			FILE * f_temp;
			char buffer[1000];
			f_ptr  = fopen(file_name, "r");
			f_temp = fopen("replace.tmp", "w"); 
			if (f_ptr == NULL || f_temp == NULL)
			{
				printf("Please check whether file exists and you have read/write privilege.\n");
				exit(0);
			}
			while ((fgets(buffer, 1000, f_ptr)) != NULL)
			{
				// Replace all occurrence of word from current line
				replaceAll(buffer, str1, str2);

				// After replacing write it to temp file.
				fputs(buffer, f_temp);
			}
			fclose(f_ptr);
			fclose(f_temp);
			remove(file_name);
			rename("replace.tmp", file_name);
			strcpy(buff,"Replace done.");
			sentbytes=send(client_sockfd,buff,sizeof(buff),0);
			if(sentbytes==-1)
			{
				printf("\nMessage Sending Failed");
				close(sockfd);
				close(client_sockfd);
				exit(0);
			}
			break;

			case 3:
			printf("\nOrdering file..\n");
		
			FILE * file_log = NULL;
			FILE * file_summary = NULL;

			if ( (file_log = fopen(file_name, "r")) == NULL ) {
				fprintf(stderr,"Error: Could not open %s\n",file_name);
				return 1;
			}
			if ( (file_summary = fopen("temp.txt", "a")) == NULL ) {
				fprintf(stderr,"Error: Could not open temp.txt\n");
				return 1;
			}

			while(fgets(strTempData, MAX_LEN, file_log) != NULL) {
				if(strchr(strTempData,'\n'))
					strTempData[strlen(strTempData)-1] = '\0';
				str_data = (char**)realloc(str_data, sizeof(char**)*(line_count+1));
				str_data[line_count] = (char*)calloc(MAX_LEN,sizeof(char));
				strcpy(str_data[line_count], strTempData);
				line_count++;
			}
			// Sort the array.
			for(i= 0; i < (line_count - 1); ++i) {
				for(j = 0; j < ( line_count - i - 1); ++j) {
					if(strcmp(str_data[j], str_data[j+1]) > 0) {
						strcpy(strTempData, str_data[j]);
						strcpy(str_data[j], str_data[j+1]);
						strcpy(str_data[j+1], strTempData);
					}
				}
			}
			// Write it to output file.
			for(i = 0; i < line_count; i++)
				fprintf(file_summary,"%s\n",str_data[i]);
			for(i = 0; i < line_count; i++)
				free(str_data[i]);
			free(str_data);
			remove(file_name);
			rename("temp.txt",file_name);
			
			fclose(file_log);
			fclose(file_summary);
			strcpy(buff,"Ordering done!");
			sentbytes=send(client_sockfd,buff,sizeof(buff),0);
			if(sentbytes==-1)
			{
				printf("\nMessage Sending Failed");
				close(sockfd);
				close(client_sockfd);
				exit(0);
			}
			break;

			case 4: choice=4;
			break;
	}
}
	close(client_sockfd);
	close(sockfd);
}
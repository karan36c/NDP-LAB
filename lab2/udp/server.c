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
	int sockfd,retval,recvdbytes,sentbytes,PORT;
	int ca;
	printf("PORT: ");
	scanf("%d", &PORT);
	socklen_t socklen;
	struct sockaddr_in server,client;
	char buff[50];

	
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

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
	printf("\nSocket binded.");

	recvdbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
	if(recvdbytes==-1)
	{
		printf("\nFailed to receive");		
		close(sockfd);
		exit(0);
	}	
	
	printf("\nFile Name received\n");
	char fil[50];
	if( access( buff, F_OK ) != -1 ) {
    // file exists
		strcpy(fil,buff);
		strcpy(buff,"File exists");
	} else {
    // file doesn't exist
		strcpy(buff,"File does not exist!");
	}

	sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,socklen);
	if(sentbytes==-1)
	{
		printf("\nMessage Sending Failed");
		close(sockfd);
		exit(0);
	}
	if(strcmp(buff,"File does not exist!")==0)
	{
		close(sockfd);
		exit(0);
	}
	int ch=0;
	while(ch!=4){
		recvdbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
	if(recvdbytes==-1)
	{
		printf("\nFailed to receive");		
		close(sockfd);
		exit(0);
	}	
	ch = buff[0];
	int i,n,first_len,second_len,j;
	char str[50],str1[50],str2[50];
	char strTempData[MAX_LEN];
    char **strData = NULL; // String List
    int num_of_lines = 0;

    switch(ch)
	{
		// SEARCH
		case 1:
		printf("\nSearching..\n");
		n=buff[1];

		for(i=0;i<n;i++)
			str[i]=buff[i+2];

		str[n]='\0';
		FILE *fp;
		int line_num = 1;
		int find_result = 0;
		char temp[512];
		if((fp = fopen(fil, "r")) == NULL) {
			printf("\nFile not found");		
			close(sockfd);
			exit(0);
		}
		while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			find_result++;
		}
		line_num++;
		}
		if(fp) {
			fclose(fp);
		}
		buff[0]=find_result;
		sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,socklen);
		if(sentbytes==-1)
		{
			printf("\nFailed to send");
			close(sockfd);
			exit(0);
		}
		break;

		case 2:
		first_len=buff[1];
		i=2;
		for(j=0;j<first_len;j++)
		{
			str1[j]=buff[i];
			i++;
		}
		str1[j]='\0';
	recvdbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
	if(recvdbytes==-1)
	{
		printf("\nFailed to receive");		
		close(sockfd);
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
		FILE * fPtr;
    	FILE * fTemp;
    	char buffer[1000];
    	fPtr  = fopen(fil, "r");
    	fTemp = fopen("replace.tmp", "w"); 
    	if (fPtr == NULL || fTemp == NULL)
   		 {
        exit(0);
    	}
    	 while ((fgets(buffer, 1000, fPtr)) != NULL)
    	{
        // Replace all occurrence of word from current line
        replaceAll(buffer, str1, str2);

        fputs(buffer, fTemp);
    	}


    //  Close all files
    	fclose(fPtr);
    	fclose(fTemp);
    	remove(fil);
// rename file
    	rename("replace.tmp", fil);
    	strcpy(buff,"Replace finished!");
    	sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,socklen);

	if(sentbytes==-1)
	{
		printf("\nMessage Sending Failed");
		close(sockfd);
		exit(0);
	}
		break;
	case 3:	printf("\nOrdering file..\n");
		
    FILE * ptrFileLog = NULL;
    FILE * ptrSummary = NULL;

    if ( (ptrFileLog = fopen(fil, "r")) == NULL ) {
        fprintf(stderr,"Error: Could not open %s\n",fil);
        return 1;
    }
    if ( (ptrSummary = fopen("temp.txt", "a")) == NULL ) {
        fprintf(stderr,"Error: Could not open temp.txt\n");
        return 1;
    }

    // Read and store in a string list.
    while(fgets(strTempData, MAX_LEN, ptrFileLog) != NULL) {
        // Remove the trailing newline character
        if(strchr(strTempData,'\n'))
            strTempData[strlen(strTempData)-1] = '\0';
        strData = (char**)realloc(strData, sizeof(char**)*(num_of_lines+1));
        strData[num_of_lines] = (char*)calloc(MAX_LEN,sizeof(char));
        strcpy(strData[num_of_lines], strTempData);
        num_of_lines++;
    }
    // Sort the array.
    for(i= 0; i < (num_of_lines - 1); ++i) {
        for(j = 0; j < ( num_of_lines - i - 1); ++j) {
            if(strcmp(strData[j], strData[j+1]) > 0) {
                strcpy(strTempData, strData[j]);
                strcpy(strData[j], strData[j+1]);
                strcpy(strData[j+1], strTempData);
            }
        }
    }
    // Write it to outfile. file.
    for(i = 0; i < num_of_lines; i++)
        fprintf(ptrSummary,"%s\n",strData[i]);
    // free each string
    for(i = 0; i < num_of_lines; i++)
        free(strData[i]);
    // free string list.
    free(strData);
    remove(fil);
    rename("temp.txt",fil);
    fclose(ptrFileLog);
    fclose(ptrSummary);
		strcpy(buff,"Ordering done!");
		sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,socklen);
	if(sentbytes==-1)
	{
		printf("\nMessage Sending Failed");
		close(sockfd);
		exit(0);
	}
		break;

		case 4: ch=4;
		break;

	}
	}
	close(sockfd);
}
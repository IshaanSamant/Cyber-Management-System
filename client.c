#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4455

int main()
{
    FILE* pointer=fopen("detail.txt","r");
    char username[20],password[20];
    char data[50];
    int flag=0,flag1=0;
    int opt;
    printf("Option 1:Guest\n");
    printf("Option 2:Login\n");  
    scanf("%d",&opt);
    if(opt==2)
    {
    printf("Enter your Username:");
    scanf("%s",username);
    printf("Enter your Password:");
    scanf("%s",password);
    while(fgets(data,50,pointer)!=NULL)
    {
    char *a = strtok(data,",");
    if(!strcmp(a,username))
    {
        flag=1;
        a = strtok(NULL,",");
       if(!strcmp(a,password))
       {
           flag1=1;
       }
    } 
    }
    if(!flag)
    {
        printf("Wrong Username\n");
        exit(0);
    }
    if(!flag1)
    {
        printf("Wrong Password\n");
        exit(0);
    }
    printf("Login Succesful\n");
    fclose(pointer);
    }
int clientSocket;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	printf("[+]Client Socket Created Sucessfully.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	printf("[+]Connected to Server.\n");

	recv(clientSocket, buffer, 1024, 0);
	if(opt==1)
	{
	strcpy(buffer,"Guest request;");	
	send(clientSocket, buffer, strlen(buffer), 0);
	recv(clientSocket, buffer, 1024, 0);
	char *a = strtok(buffer,";");
	if(strcmp(buffer,"Deny")==0)
	{
	printf("[+]Access denied\n");
	exit(0);
	}
	printf("[+]Access granted\n");
	}
	if(opt==2)
	{
	strcpy(buffer,strcat(username,";"));	
	send(clientSocket, buffer, strlen(buffer), 0);
	recv(clientSocket, buffer, 1024, 0);
	}
	int num=1;	
	while(num)
	{
	printf("1 Print\n2 Scan\n3 Photocopy\n4 Logout\n");
	scanf("%d",&opt);
	switch(opt)
	{
	case 1: {strcpy(buffer,"Print;");
	printf("Print\n");
	send(clientSocket, buffer, strlen(buffer), 0);
	recv(clientSocket, buffer, 1024, 0);}
	break;
	case 2: {strcpy(buffer,"Scan;");
	printf("Scan\n");
	send(clientSocket, buffer, strlen(buffer), 0);
	recv(clientSocket, buffer, 1024, 0);}
	break;
	case 3: {strcpy(buffer,"Photocopy;");
	printf("Photocopy\n");
	send(clientSocket, buffer, strlen(buffer), 0);
	recv(clientSocket, buffer, 1024, 0);}
	break;
	case 4:{strcpy(buffer,"Logout;");
	printf("[+]Generating Bill\n");
	send(clientSocket, buffer, strlen(buffer), 0);
	recv(clientSocket, buffer, 1024, 0);
	num=0;
	}break;
	default: printf("Invalid Option");	
	}
	}
	char *a = strtok(buffer,";");
	printf("Print %s\n",a);
	a = strtok(NULL,";");
	printf("Scan %s\n",a);
	a = strtok(NULL,";");
	printf("Photocopy %s\n",a);
	printf("[+]Closing the connection.\n");
	

}

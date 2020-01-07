#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4455

void main(){

	int sockfd;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;
	char buffer[1024];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("[+]Server Socket Created Sucessfully.\n");
	memset(&serverAddr, '\0', sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	printf("[+]Bind to Port number %d.\n", 4455);

	listen(sockfd, 5);
	printf("[+]Listening...\n");

	newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);

	strcpy(buffer, "This is a test message");
	send(newSocket, buffer, strlen(buffer), 0);
	recv(newSocket,buffer,1024,0);
	char *a = strtok(buffer,";");
	
	int opt;	
	if(strcmp(a,"Guest request")==0)
	{
	printf("A user has asked for access to login as guest\n");
	printf("0 No\n");
	printf("1 Yes\n");
	scanf("%d",&opt);
	if(!opt)
	{
	printf("[+]Closing the connection.\n");
	strcpy(buffer,"Deny;");
	send(newSocket, buffer, strlen(buffer), 0);
	recv(newSocket,buffer,1024,0);	
	exit(0);
	}
	printf("[+]Access granted\n");	
	}
	else
	{
	printf("[+]Data Recv: %s\n", a);	
	printf("User %s has logged into a system\n",buffer);
	}
	int num=1;
	int print=0,scan=0,photocopy=0;
	while(num)
	{
		
	send(newSocket, buffer, strlen(buffer), 0);
	recv(newSocket,buffer,1024,0);	
	a = strtok(buffer,";");	
	if(strcmp(a,"Logout")==0)
	{
	num=0;
	printf("User logging out\n");	
	}
	else if(strcmp(a,"Print")==0)
	{
	print++;	
	}	
	else if(strcmp(a,"Scan")==0)
	{
	scan++;	
	}	
	else if(strcmp(a,"Photocopy")==0)
	{
	photocopy++;	
	}	
	}
	char c[100];
	char message[100]="";	
	c[0] = print +'0';
	c[1] = ';';	
	c[2] = scan + '0';
	c[3] = ';';
	c[4] = photocopy + '0';
	c[5] = ';';
	c[6] = '\0';	
	strcpy(buffer,c);
	send(newSocket, buffer, strlen(buffer), 0);
	recv(newSocket,buffer,1024,0);	
	printf("[+]Closing the connection.\n");



}

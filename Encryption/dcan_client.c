
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX 1024
#define PORT 8080
#define SA struct sockaddr

void encrypt(char *str,char *q){

	int n=0;
	char *p=str;
		 

	while(*p)
	{
	 if(islower(*p))
	 {
		 if((*p>='a')&&(*p<'x'))
			 *(q+n)=toupper(*p + (char)3);
		 else if(*p=='x')
			 *(q+n)='A';
		 else if(*p=='y')
			 *(q+n)='B';
		 else
			 *(q+n)='C';
	 }
	 else
	 {
		 *(q+n)=*p;
	 }
	 n++; p++;
	}
	*(q+n)='\0';
	n++;
}

void func(int sockfd) {
	char buff[MAX],q[MAX];
	int n,l;
	while (1) {
		bzero(buff, sizeof(buff));
		printf("Enter a string : ");
		n=0;
		//while((buff[n++] = getchar()) != '\n') ;
		fgets(buff,MAX,stdin);
		l=strlen(buff)-1;
		encrypt(buff,q);
		//printf("Encrypted text is -> %s",q);
		write(sockfd, q, sizeof(q));
		bzero(buff, sizeof(buff));
		bzero(q, sizeof(q));
		read(sockfd, buff, sizeof(buff));
		printf("From server : %s", buff);

		if (strncmp(buff, "exit", 4) == 0) {
			printf("Client Exit.\n");
			break;
		}
	}
}


int main() {
	int sockfd, confd, len;
	struct  sockaddr_in serveraddr, cli;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd == -1) {
		printf("Socket creation failed.\n");
		exit(0);
	}
	else printf("Socket created successfully.\n");

	bzero(&serveraddr, sizeof(serveraddr));

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("10.0.2.15");
	serveraddr.sin_port = htons(PORT);

	if (connect(sockfd, (SA*)&serveraddr, sizeof(serveraddr)) != 0) {
		printf("Connection with server failed.\n");
		exit(0);
	}
	else printf("Connected to the server.\n");

	func(sockfd);
	close(sockfd);
	return 0;

}

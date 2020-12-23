#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#define MAX 1024
#define PORT 8080
#define SA struct sockaddr

void decrypt(char *str, char *q){

	int   n=0;
	char *p=str;
		 

	while(*p)
	{
	 if(isupper(*p))
	 {
		 if((*p>='D')&&(*p<='Z'))
			 *(q+n)=tolower(*p - (char)3);
		 else if(*p=='A')
			 *(q+n)='x';
		 else if(*p=='B')
			 *(q+n)='y';
		 else
			 *(q+n)='z';
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
		bzero(buff, MAX);
		read(sockfd, buff, sizeof(buff));
		printf("\nEncrypted Data From client: %s\t ", buff);
		l=strlen(buff);
		decrypt(buff,q);
		
		printf("\nDecrypted data is: %s\t ",q);
		
		//write(sockfd,buff, sizeof(buff));
		
		bzero(buff, MAX);
		n = 0;
		printf("\nTo client: ");
		while ((buff[n++] = getchar()) != '\n') ;
		write(sockfd, buff, sizeof(buff));

		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit.\n");
			break;
		}
	}
}

int main() {
	int sockfd, confd, len;
	struct sockaddr_in serveraddr, cli;
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

	if ((bind(sockfd, (SA*)&serveraddr, sizeof(serveraddr))) != 0){
		printf("Socket bind failed.\n");
		exit(0);
	}
	else printf("Socket binded successfully.\n");

	
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed.\n");
		exit(0);
	}
	else printf("Server listening\n");

	len = sizeof(cli);

	confd = accept(sockfd, (SA*)&cli, &len);
	if (confd<0) {
		printf("Server accept failed\n");
		exit(0);
	}
	else printf("Server accepting from client\n");

	func(confd);
	close(sockfd);
	return 0;

}

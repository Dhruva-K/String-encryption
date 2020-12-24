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
char darr[MAX][MAX],retmessage[111];
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

/*void trans_decrypt(char *str, char *q,int l)
{
	char temp[MAX],temp2[MAX],key[MAX];
	int rows,k,r,i,j,klen,c,index;
	char *p=str;
	
	printf("Enter key\n");
	//fflush(stdin);
	fgets(key,MAX,stdin);
	strcpy(temp,key);
	klen = strlen(key)-1;
	rows=l/klen;
	rows;
	j=0;
	for (i=0,k=1;*(p + i)!=NULL;i++,k++) {
		//printf("\nEmlen=%d",emlen); 
		temp2[j++]=*(p+i);
		if((k%rows)==0) {
			temp2[j]='\0';
			index=findMin(temp);
			makeArray(index,rows,temp2);
			j=0;
		}
	}
	
	k=0;
	r=3;
	c=6;
	for (i=0;i<3;i++) {
		for (j=0;j<c;j++) {
			printf("%c ",darr[i][j]);
			//retrieving message 
			*(q+k)=darr[i][j];
			k++;
		}
		printf("\n");
	}
	*(q+k)='\0';
	printf("\nMessage retrieved is\n");
	for (i=0;*(q+i)!=NULL;i++) 
	     printf("%c",*(q+i));
}

void makeArray(int col,int row,char *temp2) {
	int i,j;
	for (i=0;i<row;i++) {
		darr[i][col]=*(temp2+i);
	}
}
int findMin(char *temp) {
	int i,j,min,index;
	min=*(temp);
	index=0;
	for (j=0;*(temp+j)!=NULL;j++) {
		if(*(temp+j)<min) {
			min=*(temp+j);
			index=j;
		}
	}
	temp[index]=123;
	return(index);
}*/
void decryptMsg(char *str, int l){
    int  i, j, k = -1, row = 0, col = 0, m = 0,key = 3;
    char railMatrix[key][l];
 
    for(i = 0; i < key; ++i)
        for(j = 0; j < l; ++j)
            railMatrix[i][j] = '\n';
 
    for(i = 0; i < l; ++i){
        railMatrix[row][col++] = '*';
 
        if(row == 0 || row == key-1)
            k= k * (-1);
 
        row = row + k;
    }
 
    for(i = 0; i < key; ++i)
        for(j = 0; j < l; ++j)
            if(railMatrix[i][j] == '*'){
                railMatrix[i][j] = *(str + m);
                m++;
                }
 
    row = col = 0;
    k = -1;
 
    printf("\nDecrypted Message: ");
  int x=0;
    for(i = 0; i < l; ++i){
        printf("%c",railMatrix[row][col++]);
 
        if(row == 0 || row == key-1)
            k= k * (-1);
 
        row = row + k;
        
    }
   
}
void func(int sockfd) {
	char buff[MAX],q[MAX];
	int n,l,x;
	while (1) {
		bzero(buff, MAX);
		read(sockfd, buff, sizeof(buff));
		printf("\nEncrypted Data From client: %s\t ", buff);
		l=strlen(buff);
		printf("\nSelect the type of encryption\n");
		scanf("%d",&x);
		
		switch(x){
			case 1: decrypt(buff,q);
				printf("\nDecrypted data is: %s\t ",q);
				bzero(buff, MAX);
				n = 0;
				printf("\nTo client: ");
				while ((buff[n++] = getchar()) != '\n') ;
				write(sockfd, buff, sizeof(buff));

				if (strncmp("exit", buff, 4) == 0) {
					printf("Server Exit.\n");
					break;
				}
				break;
			case 2: decryptMsg(buff,l);
				bzero(buff, MAX);
				n = 0;
				printf("\nTo client: ");
				while ((buff[n++] = getchar()) != '\n') ;
				write(sockfd, buff, sizeof(buff));

				if (strncmp("exit", buff, 4) == 0) {
					printf("Server Exit.\n");
					break;
				}
				break;
			default: printf("Wrong input");
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

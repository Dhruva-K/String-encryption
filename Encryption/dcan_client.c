
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
/*void transposition(char *str, char *q){
	int i,j,klen,emlen,flag=0;
	int r,c,index,min,rows;
	char temp[55],arr[22][22],key[MAX];
	char *p=str;
	
	printf("Enter key\n");
	//fflush(stdin);
	fgets(key,MAX,stdin);
	key[strlen(key)]='\0';
	strcpy(temp,key);
	klen = strlen(key)-1;
	//printf("\n%d",klen);
	int k =0;
	for (i=0; ;i++) {
		if(flag==1) 
		    break;
		for (j=0;j<5;j++) {
			if(*(p+k)==NULL) {
				flag=1;
				arr[i][j]='-';
			} else {
				arr[i][j]=*(p+k);
				//printf("%d %c",j,key[j]);
				k++;
			}
		}
	}
	r=i;
	c=j;
	printf("%d %d",r,c);
	for (i=0;i<r;i++) {
		for (j=0;j<c;j++) {
			printf("%c ",arr[i][j]);
		}
		printf("\n");
	}
	k=0;
	for (i=0;i<klen;i++) {
		index=findMin(temp);
		//cipher(index,r);
		for(j=0;j<r;j++)
		{
			*(q+k)=arr[j][index];
			k++;
		}
	}
	*(q+k) = '\0';
	/*printf("\nEncrypted message is\n");
	for (i=0;*(q+i)!=NULL;i++) 
	   printf("%c",*(q+i));
	printf("\n\n");
	
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
	*(temp+index)=123;
	return(index);
}*/
void encryptMsg(char *str, char *q,int l){
    int  i, j, k = -1, row = 0, col = 0,key = 3,x;
    char railMatrix[key][l];
 
    for(i = 0; i < key; ++i)
        for(j = 0; j < l; ++j)
            railMatrix[i][j] = '\n';
 
    for(i = 0; i < l; ++i){
        railMatrix[row][col++] = *(str +i);
 
        if(row == 0 || row == key-1)
            k= k * (-1);
 
        row = row + k;
    }
    x=0;
    //printf("\nEncrypted Message: ");
 	
    for(i = 0; i < key; ++i){
        for(j = 0; j < l; ++j){
            if(railMatrix[i][j] != '\n'){
                *(q+x)=railMatrix[i][j];
                x++;
                }
          }
    }
    *(q+x) = '\0';
}
void func(int sockfd) {
	char buff[MAX],q[MAX];
	int n,l,x;
	while (1) {
		bzero(buff, sizeof(buff));
		printf("Enter a string : ");
		n=0;
		//while((buff[n++] = getchar()) != '\n') ;
		fgets(buff,MAX,stdin);
		l=strlen(buff)-1;
		printf("\nSelect the type of encryption\n");
		printf("Press 1 for caesar encryption\n");
		printf("Press 2 for Rail fence encryption\n");
		scanf("%d",&x);
		/*switch(x){
			case 1: encrypt(buff,q);
				write(sockfd, q, sizeof(q));
				bzero(buff, sizeof(buff));
				bzero(q, sizeof(q));
				read(sockfd, buff, sizeof(buff));
				printf("From server : %s", buff);

				if (strncmp(buff, "exit", 4) == 0) {
					printf("Client Exit.\n");
					break;
				}
				break;
			case 2: encryptMsg(buff,q,l);
				write(sockfd, q, sizeof(q));
				bzero(buff, sizeof(buff));
				bzero(q, sizeof(q));
				read(sockfd, buff, sizeof(buff));
				printf("From server : %s", buff);

				if (strncmp(buff, "exit", 4) == 0) {
					printf("Client Exit.\n");
					break;
				}
				break;*/
			//}
			if(x==1){
			encrypt(buff,q);
			}
			else if(x==2){
			encryptMsg(buff,q,l);
			}
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

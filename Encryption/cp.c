//C Program to Encrypt or Decrypt any string
#include <stdio.h>
#include <ctype.h>  //including header files

#define MAXSIZE 1024  

void encrypt(char*);
void decrypt(char*);
int menu();  //function declaration

int main(void) //main function
{
    char c,
    choice[2],
    s[MAXSIZE];  

    while(1)
    {
        menu();
        gets(choice);

        if((choice[0]=='e')||(choice[0]=='E'))
        {
            printf("Input text to encrypt:");
            gets(s);
            encrypt(s);  //calling encrypt function
        }
        else if((choice[0]=='d')||(choice[0]=='D'))
        {
            printf("Input text to decrypt:");
            gets(s);
            decrypt(s);  //calling decrypt function
        }
        else
            break;
    }

    return 0;
}

int menu()
{
    printf("\n\nTo encrypt, input e or E\n");
    printf("To decrypt, input d or D\n");
    printf("To exit, input any other letter\n");
    printf("Your choice:\n");
    return 0;
}

void encrypt(char*str) //defining encrypt function
{
	int n=0;
	char *p=str,
		 q[MAXSIZE];

	while(*p)
	{
	 if(islower(*p))
	 {
		 if((*p>='a')&&(*p<'x'))
			 q[n]=toupper(*p + (char)3);
		 else if(*p=='x')
			 q[n]='A';
		 else if(*p=='y')
			 q[n]='B';
		 else
			 q[n]='C';
	 }
	 else
	 {
		 q[n]=*p;
	 }
	 n++; p++;
	}
	q[n++]='\0';
    printf("Encrypted text is -> %s",q);

}

void decrypt(char*str) //defining decrypt function
{
	int   n=0;
	char *p=str,
		 q[MAXSIZE];

	while(*p)
	{
	 if(isupper(*p))
	 {
		 if((*p>='D')&&(*p<='Z'))
			 q[n]=tolower(*p - (char)3);
		 else if(*p=='A')
			 q[n]='x';
		 else if(*p=='B')
			 q[n]='y';
		 else
			 q[n]='z';
	 }
	 else
	 {
		 q[n]=*p;
	 }
	 n++; p++;
	}
	q[n++]='\0';
	printf("Decrypted text is -> %s",q);
}


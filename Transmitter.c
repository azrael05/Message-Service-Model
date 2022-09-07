#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
void encr(char *message,int n)                           //Function code for encryption (Caeser shift)
{
	if((*message>=65&&*message<=90-n)||(*message>=97&&*message<=122-n))
    *message=*message+n;
	else if((*message>90-n&&*message<=90)||(*message>122-n&&*message<=122))
	*message=*message-26+n;
}

void initialize_and_permute(char code[], unsigned n)
{
    int i;
    for (i = 0; i <= n-1; i++) {
        unsigned j = i+rand()%(n-i);
        char temp=code[i];
	    code[i]=code[j];
	    code[j]=temp;
    }
}
void albertidisk(char msg[],char code[])
{
	int n=rand()%26;
	initialize_and_permute(code,52);
	int len=strlen(msg);
	int i;
	for(i=0;i<len-1;i++)
	{
		if(msg[i]>=97&&msg[i]<=122)
		msg[i]=code[(int)(msg[i])-97];
		else if(msg[i]>=65&&msg[i]<=90)
		msg[i]=	code[(int)(msg[i])-65+26];
		
	}
}

int main()
{
	int n,ch;
	char code[55]={"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	srand(time(0));
	FILE* trans=fopen("transmitter.txt","w"),*encryption=fopen("encryption.txt","w");
	char str[3000];
	printf("\t\t WELCOME TO SENDER'S END\n");                                         //in seconds
 	printf("ENTER THE MESSAGE TO BE SENT:-\n");
	fgets(str,3000,stdin);                  //taking message as input
	int len=strlen(str)-1,i=0;
	fputs(str,trans);      //storing message in transmitter.txt
	printf("\nMessage stored successfully\n\n");
	printf("Select Encryption Type:- \n1->Julius Caeser Shift \n2->Alberti Disk\n");
	scanf("%d",&ch);
	switch(ch)
	{
	    case 1:{int choice;
	    	    printf("\n Select option \n1. User Defined Key \n 2. System Generated Key\n ");
	    	    scanf("%d",&choice);
	    	    if(choice==1)
		        {
				    printf("\n Enter the shift key (number greater than or equal to 0):- ");
	                do{
					    scanf("%d",&n);
	                    if(n<0)
	                    {
	                	    printf("INVALID KEY ENTERED \n Enter a valid key:-\n");
					    }
				      }while(n<0);
	            }
	            if(choice==2)
	            n=rand()%26;
	            int x=n%26;
	            while(i<len)                            //encryption
                {
                    encr(&str[i],x);
                    i++;
                }
			    break;
		        }
		case 2:{albertidisk(str,code);
			break;
		}
    }
    fseek(encryption,0,SEEK_SET);
	i=0;
	int done=0,l;                           //storing encrypted and byte stuffed message in encrypted.txt
	do{
	    do{
		    l=rand()%10;
	    }while(l<2);
	    if(done+l<len)
	        done=done+l;
	    else
	    {
	    	l=len-done;
	    	 done=len;
		}
		fprintf(encryption,"z");
		fprintf(encryption,"%d",l);
	    while(i<done)
        {
            if(str[i]=='z'||str[i]=='x')
            {
     	        fprintf(encryption,"x%c",str[i]);
	        }
	        else
	        {
		        fprintf(encryption,"%c",str[i]);
	        }
	        i++;
	    }
	    fprintf(encryption,"z\n");
    }while(done!=len);
    fclose(encryption);
    FILE* coding=fopen("code.txt","w");
    printf("\n\nYour Key code \n Type:-");
    switch(ch)
    {
    	case 1:{printf("\tJulius Caeser Shift\n Key is %d",n);
    	fprintf(coding,"%d",n);
			break;
		}
		case 2:{printf("\tAlberti Disk \n code is %s",code);
		fprintf(coding,"\t%s",code);
			break;
		}
	}
	fclose(coding);
}

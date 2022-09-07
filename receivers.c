#include<stdio.h>
#include<string.h>
#include"noise.c"
void del(char msg[],int i,int len)
{
	for(i;i<len+1;i++)
	{
		msg[i]=msg[i+1];
	}	
}
void dead(char msg[],char code[],int len)
{
	int i,j;
	for(i=1;i<len;i++)
	{
		if((msg[i]>=97&&msg[i]<=122)||(msg[i]>=65&&msg[i]<=90))
		{   
		    for(j=0;j<52;j++)
		    {
			    if(msg[i]==code[j])
			    {
			        if(j<26)
			        {
					    msg[i]=(char)(j+97);	
			            break;
			        }
			        else
			        {
					    msg[i]=(char)(j+65-26);	
			            break;
			        }
			    }
		    }
		}					
	}
}
void dejcs(char msge[],int len,int n)
{
	int i;
	for(i=1;i<len;i++)    //reverse caeser shift to get original mesaage
	{
	    if((msge[i]>=65+n&&msge[i]<=90)||(msge[i]>=97+n&&msge[i]<=122))
        {
		    msge[i]=msge[i]-n;
        }
	    else if((msge[i]<65+n&&msge[i]>=65)||(msge[i]>=97&&msge[i]<95+n))
	    {
	        msge[i]=msge[i]+26-n;	
        }	
	}
}

int main()
{
	int ch,shift;
	char code[52];
	noise_add();
	FILE *rec;
	rec=fopen("reciever.txt","r");	
	int line=1,loc;
	printf("\t\t\t WELCOME TO RECEIVERS END\n\n");
	printf("Enter Encryption type:- \n 1. JULIUS CAESER SHIFT \n2. ALBERTI DISK\n");
	scanf("%d",&ch);
	printf("\n ENTER KEY :-\n ");
	switch(ch){
		case 1:{scanf("%d",&shift);
			break;
		}
		case 2:{scanf("%s",code);
		        if(strlen(code)!=52)
		        {
		        	printf("\nINVALID KEY\n");
		        	exit(0);
				}
			break;
		}
		
	}
	printf("WITHOUT NOISE REMOVAL:-\n\t");
    do
	{
	char* msgn=(char*)malloc(25);
	fseek(rec,-1,SEEK_CUR);	
	loc=ftell(rec);
	fgets(msgn,25,rec);
	int len=strlen(msgn),i;
    for(i=2;i<len-2;i++)
		{
			    if(msgn[i]=='x')
		{
			del(msgn,i,len);
			len--;
		}	
		}
		del(msgn,0,len);
		len--;
		del(msgn,len-2,len);
		len--;  
		del(msgn,len-1,len);
		len--;
		switch(ch){
		     case 1:{dejcs(msgn,len,shift);
				break;
			 }
			 case 2:{dead(msgn,code,len);
				break;
			 }		
	    }	
			del(msgn,0,len);
			fputs(msgn,stdout);
    free(msgn);
    }while(getc(rec)!=EOF);
    fclose(rec);
	rec=fopen("reciever.txt","r");
	printf("\n\nAFTER NOISE REMOVAL\n\t");
	do
	{
	char* msge=(char*)malloc(25);
	fseek(rec,-1,SEEK_CUR);	
	loc=ftell(rec);
	fgets(msge,25,rec);
	int len=strlen(msge);
	if(msge[0]!='z'||msge[len-2]!='z')
	    {
		    fclose(rec);
		    resend(line);
		    rec=fopen("reciever.txt","r");
		    fseek(rec,loc,SEEK_SET);
		    continue;
	    }
int i;
	    for(i=2;i<len-2;i++)
		{
			    if(msge[i]=='x')
		{
			if(msge[i+1]=='x'||msge[i+1]=='z')
			{
			    del(msge,i,len);
			    len--;
		    }
		    else
		    {
		        fclose(rec);
		        resend(line);
		        rec=fopen("reciever.txt","r");
		        fseek(rec,loc,SEEK_SET);
		        continue;	
			}
		}	
		}
		del(msge,0,len);
		len--;
		del(msge,len-2,len);
		len--;  
		del(msge,len-1,len);
		len--;
		if((int)msge[0]-48!=len-1)
		{
		    fclose(rec);
		    resend(line);
		    rec=fopen("reciever.txt","r");
		    fseek(rec,loc,SEEK_SET);
		    continue;
	    }
		switch(ch){
		     case 1:{dejcs(msge,len,shift);
				break;
			 }
			 case 2:{dead(msge,code,len);
				break;
			 }		
	    }	
			del(msge,0,len);
			fputs(msge,stdout);
    line++;
    free(msge);
    }while(getc(rec)!=EOF);
    fclose(rec);
}

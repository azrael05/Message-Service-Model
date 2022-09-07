#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
int resend(int line)
{
	FILE* temp,*rec,*enc=fopen("encryption.txt","r");
	rec=fopen("reciever.txt","r");
	temp=fopen("temp.txt","w");
	char t[25];
	int i,j;
	for(i=1;i<line;i++)
	{
		char* msg=(char*)malloc(30);
		for(j=0;j<30;j++)
	    	msg[j]='\0';
		fgets(msg,30,rec);
		fgets(t,25,enc);
		fputs(msg,temp);
		free(msg);
	}
	    int num=rand()%2,len;
        char* msg=(char*)malloc(30);
		for(i=0;i<30;i++)
	    {
	    	msg[i]='\0';
		}
	    fgets(msg,30,enc);
	    len=strlen(msg);
	    for(j=0;j<num;j++)
	    {
		    int pos=rand()%len;
		    int val=rand()%26;
		    for(i=len-1;i>=pos;i--)
		    {
			    msg[i+1]=msg[i];
		    }
		    char ch=(char)(val+65);
		    msg[pos]=ch;
		    len++;	
	    }
	fputs(msg,temp);
	fgets(msg,25,rec);
	free(msg);
	char ch[20];
	while(fgets(ch,20,rec)!=NULL)
	fputs(ch,temp);
    fclose(rec);
	fclose(temp);
	fclose(enc);
	rec=fopen("reciever.txt","w");
	temp=fopen("temp.txt","r");
	while(fgets(ch,20,temp)!=NULL)
	fputs(ch,rec);
    fclose(temp);
	fclose(enc);
	temp=fopen("temp.txt","w");
	fclose(temp);
}
int noise_add()
{
	srand(time(0));
	FILE* noise,*rec;
	noise=fopen("encryption.txt","r");
	rec=fopen("reciever.txt","w");
	int line=1,i,j;
	do{
		fseek(noise,-1,SEEK_CUR);
	    int num=rand()%3,len;
        char* encr=(char*)malloc(30);
        for(i=0;i<30;i++)
	    	encr[i]='\0';
	    fgets(encr,30,noise);
	    len=strlen(encr);
	    for(j=0;j<num;j++)
	    {
	    	if(j%3!=2)                         //adding element
		    {
		        int pos=rand()%len;
			    int val=rand()%26;
		        for(i=len-1;i>=pos;i--)
		        {
			        encr[i+1]=encr[i];
		        }
		        char ch=(char)(val+65);
		        encr[pos]=ch;
		        len++;
		    }
		    else
		    {
		    	int pos;
		    	do{
				pos=rand()%(len-1);
		    	}while(pos!=0&&pos!=1);
		    	for(i=pos;i<len-1;i++)                //delete element
		    	encr[pos]=encr[pos+1];
		    	len--;
			}
	    }
	fputs(encr,rec);
	line++;
	free(encr);		
	}while(fgetc(noise)!=EOF);
	fclose(noise);
	fclose(rec); 
}

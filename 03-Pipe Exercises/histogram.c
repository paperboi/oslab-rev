#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
	
	char ch;
	pid_t pid;
	FILE *f;
	
	
	
	pid=fork();
	
	if(pid==0)
	{
		int count_star=0;
		f=fopen("Histogram.txt","r");
		ch=getc(f);
		while(ch!=EOF)
		{
			if(ch=='*')
			 count_star++;
			ch=getc(f);
		}
		fclose(f);
		printf("Count of * : %d\n",count_star);
		exit(0);
		
	}
	else if(pid>0)
	{
		wait(NULL);
		int count_hash=0;
		f=fopen("Histogram.txt","r");
		ch=getc(f);
		while(ch!=EOF)
		{
			if(ch=='#')
			 count_hash++;
			ch=getc(f);
		}
		fclose(f);
		printf("Count of # : %d\n",count_hash);	
		
	}
	return 0;
	
}

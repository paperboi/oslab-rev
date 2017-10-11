#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int main()
{
	int pip[2];
	pid_t pid;
	char st2[100];	
	
	if(pipe(pip) == -1)
	{
		printf("\n Error : Pipe creation failed\n");
		exit(1);
	}
	
	pid=fork();
	
	if(pid==0)
	{
		char st[100];
		close(pip[0]);
		printf("Enter a string : ");
		gets(st);
		//char st[]={"malayalam"};
		write(pip[1],st,strlen(st)+1);
		exit(0);
		
	}
	else
		if(pid>0)
		{
			wait(NULL);
			close(pip[1]);
			char rev[100];
			int k=0;
			
			read(pip[0],st2,sizeof(st2));
			for(int i=strlen(st2)-1; i>=0; i--)
			  rev[k++]=st2[i];
			
			if(strcmp(rev,st2)==0)
			printf("%s is a palindrome\n",st2);
			else
			printf("%s is not a palindrome\n",st2);	
		}

	
	return 0;
}
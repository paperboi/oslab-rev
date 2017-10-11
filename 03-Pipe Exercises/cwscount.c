#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<ctype.h>

int main()
{
	int fd[2];
	pid_t pid;
	char par[100];	
	
	if(pipe(fd) == -1)
	{
		printf("\n Error : Pipe creation failed\n");
		exit(1);
	}
	
	pid=fork();
	
	if(pid==0)
	{
		close(fd[0]);
		char s[]={"String sharing. Test string to count the number of words and sentences."};
		write(fd[1],s,strlen(s)+1);
		exit(0);
		
	}
	else if(pid>0)
	{
		wait(NULL);
		close(fd[1]);
		int w=1,s=0,c=0;
		read(fd[0],par,sizeof(par));
		for(int i=0; i<strlen(par); i++)
		{
		  if(par[i]==' ')
		  w++;
		  
		  else if(par[i]=='.')
		  s++;
		  
		  c++;
		}
		printf("Word count : %d\n",w);
		printf("Sentence count : %d\n",s);
		printf("Character count : %d\n",c);
			
		
	}
	else
	{
		printf("\n Error : Fork failed\n");
		exit(1);
	}
	
	return 0;
}

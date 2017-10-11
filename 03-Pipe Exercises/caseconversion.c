#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

int main()
{
	pid_t pid; 
	int pip[2];

	pipe(pip);
	char st[20];

	if( (pid=fork()) == 0)
	{
		close(pip[0]);

		printf("Writing 'Hello World!' to the pipe (in child process %d)\n", getpid());
		write(pip[1], "Hello World!", 12);
		close(pip[1]);
		
		exit(0);
	}
	else
	{
		close(pip[1]);

		wait(NULL);
		read(pip[0], st, sizeof(st));
		
		for (int i = 0; i < strlen(st); ++i)
		{
			if (isalpha(st[i]))
			{
				if (isupper(st[i]))
					st[i]=tolower(st[i]);
				else
					st[i]=toupper(st[i]);
			}
		}

		printf("Given string after case conversion: '%s' (in parent process %d)\n", st, getpid());
		
		close(pip[0]);
		exit(0);
	}

}
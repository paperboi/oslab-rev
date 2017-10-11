#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	pid_t pid; 
	int pip[2];

	pipe(pip);
	char str[20];

	if( (pid=fork()) == 0)
	{
		close(pip[0]);

		printf("Writing 'Hello World!' to the pipe in child process %d\n", getpid());
		write(pip[1], "Hello World!", 11);
		close(pip[1]);
		
		exit(0);
	}
	else
	{
		close(pip[1]);

		wait(NULL);
		read(pip[0], str, sizeof(str));
		printf("Recieved the string '%s' in parent process %d\n", str, getpid());
		
		close(pip[0]);
		exit(0);
	}

	return 0;
}
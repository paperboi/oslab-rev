#include <stdio.h>
<<<<<<< HEAD
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char s[20], res[20];
int rescnt[20];

void histogram()
{
	int k=0;
	for (int i = 0; i < strlen(s); ++i)
	{
		int count=0;
		for (int j = 0; j < i; ++j)
			if (s[i]==res[j])
			{
				count++;
				rescnt[j]++;
			}
		if (count==0)
		{
			res[k]=s[i];
			rescnt[k]=++count;
			k++;
		}
	}
	printf("%s%13s%19s\n", "Element/Index", "Value", "Histogram");
	for (int i = 0; i < strlen(res); ++i)
	{
		printf("%8c%16d\t\t", res[i], rescnt[i]);
		for (int j = 0; j < rescnt[i]; ++j)
			printf("*");
		printf("\n");
	}
}

int main()
{
	pid_t pid;
	pid=vfork();
	if (pid==0)
	{
		printf("\nEnter the string: ");
		gets(s);
		exit(0);
	}
	else
	{
		if (pid>0)
		{
			wait(NULL);
			histogram();
		}
		else
		{
			printf("\nError: Forking failed.");
			exit(1);
		}
	}

	printf("\n");
	return 0;
=======
#include <fstream.h>

int main()
{
   printf("%s%13s%17s\n","Element/index", "Value", "Histogram");
   for (int i = 0; i < n; ++i)
   {
   	printf("%s\n", );
   }
>>>>>>> 6a9b68666e2f82d3a894dc986c5458ffff700822
}
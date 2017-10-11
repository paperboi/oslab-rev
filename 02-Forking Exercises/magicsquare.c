#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int M[5][5], n;
int rsum[5], csum[5], dsum[2];

void Minput()
{
	printf("\nEnter the size of the matrix: ");
	scanf("%d", &n);
	printf("\nEnter the elements: \n");
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			scanf("%d", &M[i][j]);
}

void Mcheck()
{
	memset(rsum, 0, sizeof(rsum));
	memset(csum, 0, sizeof(csum));
	memset(dsum, 0, sizeof(dsum));

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			rsum[i]+=M[i][j];
			csum[i]+=M[j][i];
			if (i==j)
				dsum[0]+=M[i][j];
			if (i+j==n-1)
				dsum[1]+=M[i][j];
		}

	int rowflag=0, colflag=0, diaflag=0;

	for (int i = 0; i < n; ++i)
		printf("\nRow %d\t\t:\t%d", i+1, rsum[i]);

	for (int i = 0; i < n; ++i)
		printf("\nColumn %d\t:\t%d", i+1, csum[i]);

	for (int i = 0; i < 2; ++i)
		printf("\nDiagonal %d\t:\t%d", i+1, dsum[i]);

	for (int i = 0; i < n-1; ++i)
	{
		if (rsum[i]!=rsum[i+1])
			rowflag=1;
		if (csum[i]!=csum[i+1])
			colflag=1;
	}

	if (dsum[0]!=dsum[1])
		diaflag=1;

	if ((rowflag==0) && (colflag==0) && (diaflag==0) && (rsum[0]==csum[0]) && (csum[0]==dsum[0]) && (dsum[0]==rsum[0]))
		printf("\nIt is a magic square matrix!");
	else
		printf("\nIt is not a magic square matrix!");
}

int main(int argc, char const *argv[])
{
	pid_t pid;

	pid=vfork();
	
	if (pid==0)
	{
		Minput();
		exit(0);
	}
	else
	{
		if (pid>0)
		{
			wait(NULL);
			Mcheck();
		}
		else
		{
			printf("\nError: forking failed");
			exit(0);
		}
	}

	printf("\n");
	return 0;
}
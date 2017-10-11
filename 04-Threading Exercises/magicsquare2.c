#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

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

void* sumgen()
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
}

void* sumcheck()
{
	int rowflag=0, colflag=0, diaflag=0;
	for (int i = 0; i < n-1; ++i)
	{
		if (rsum[i]!=rsum[i+1])
			rowflag=1;
		if (csum[i]!=csum[i+1])
			colflag=1;
	}

	if (dsum[0] != dsum[1])
		diaflag = 1;
}

int main(int argc, char const *argv[])
{
	pid_t pid;
	
	printf("\nEnter the size of the matrix: ");
	scanf("%d", &n);
	printf("\nEnter the elements: \n");
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			scanf("%d", &M[i][j]);
	
	Mcheck();
	if ((rowflag == 0) && (colflag == 0) && (diaflag == 0) && (rsum[0] == csum[0]) && (csum[0] == dsum[0]) && (dsum[0] == rsum[0]))
		printf("\nIt is a magic square matrix!");
	else
		printf("\nIt is not a magic square matrix!");
	printf("\n");
	return 0;
}
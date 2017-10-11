#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

struct matrix
{
	float M[5][5];
	int Msize;
};

struct matrix Minput(struct matrix A)
{
	printf("\nEnter the size of the matrix: ");
	scanf("%d", &A.Msize);
	printf("\nEnter the elements: \n");
	for (int i = 0; i < A.Msize; ++i)
		for (int j = 0; j < A.Msize; ++j)
			scanf("%f", &A.M[i][j]);
	return A;
}

void Mdisplay(struct matrix A)
{
	for (int i = 0; i < A.Msize; ++i)
	{
		for (int j = 0; j < A.Msize; ++j)
			printf("%f\t", A.M[i][j]);
		printf("\n");
	}
}

struct matrix MiniMatrix(struct matrix A, int r, int c)
{
	struct matrix B;
	B.Msize=A.Msize-1;

	int Nr=0, Nc=0;
	for (int i = 0; i < A.Msize; ++i)
		for (int j = 0; j < A.Msize; ++j)
			if (i!=r && j!=c)
			{
				B.M[Nr][Nc++]=A.M[i][j];
				if (Nc==B.Msize)
				{
					Nr++;
					Nc=0;
				}
			}
	return B;
}

float Determinant(struct matrix A)
{
	if (A.Msize==2)
		return A.M[0][0]*A.M[1][1]-A.M[0][1]*A.M[1][0];
	else
	{
		float det=0; int sign=1;
		for (int i = 0; i < A.Msize; ++i)
		{
				det+=sign*A.M[0][i]*Determinant(MiniMatrix(A, 0, i));
				sign=-1*sign;
		}
		return det;
	}
}

struct matrix Adjugate(struct matrix A)
{
	struct matrix C;
	C.Msize=A.Msize;
	int sign=1;

	printf("\nCofactor matrix:\n");
	for (int i = 0; i < C.Msize; ++i)
		for (int j = 0; j < C.Msize; ++j)
		{
			C.M[i][j]=sign*Determinant(MiniMatrix(A, i, j));
			sign=-1*sign;
		}
	Mdisplay(C);

	printf("\nAdjugate Matrix:\n");
	for (int i = 0; i < C.Msize; ++i)
		for (int j = 0; j < C.Msize; ++j)
			if(i<j)
			{
				int temp=C.M[i][j];
				C.M[i][j]=C.M[j][i];
				C.M[j][i]=temp;
			}
	Mdisplay(C);
	return C;
}

struct matrix Inverse(struct matrix A, float det, struct matrix Adj)
{
	struct matrix D;
	D.Msize=A.Msize;
	float onebydet=1/det;
	for (int i = 0; i < D.Msize; ++i)
		for (int j = 0; j < D.Msize; ++j)
			D.M[i][j]=onebydet*Adj.M[i][j];
	return D;
}

int main()
{
	float det;
	pid_t pid;
	struct matrix A, Adj, Inv;
	A=Minput(A);
	printf("\nGiven matrix:\n");
	Mdisplay(A);

	pid=vfork();
	
	if (pid==0)
	{
		printf("\nChild Process %d: ", getpid());
		det=Determinant(A);
		printf("\nDeterminant of the matrix: %f\n", det);
		exit(0);
	}
	else
	{
		if (pid>0)
		{
			wait(NULL);
			printf("\nParent Process %d: ", getpid());
			Adj=Adjugate(A);
		}
		else
		{
			printf("\nError: forking failed");
			exit(0);
		}
	}

	printf("\nInverse of the matrix:\n");
	Inv=Inverse(A, det, Adj);
	Mdisplay(Inv);
	printf("\n");
	
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sign=1, i, j;

struct matrix
{
	float M[5][5];
	int Msize;
}A, Adj, Inv;

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
	B.Msize = A.Msize-1;

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
		float det=0;
		for (int i = 0; i < A.Msize; ++i)
		{
				det += sign*A.M[0][i]*Determinant(MiniMatrix(A, 0, i));
				sign = -1*sign;
		}
		return det;
	}
}

void* Cofactor()
{
	Adj.M[i][j] = sign*Determinant(MiniMatrix(A, i, j));
	sign = -1*sign;
	
	if (j == Adj.Msize-1)
	{
		i++;
		j = 0;
	}
	else
		j++;

	pthread_exit(NULL);
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
	A = Minput(A);
	printf("\nGiven matrix:\n");
	Mdisplay(A);

	sign = 1;
	det = Determinant(A);
	printf("\nDeterminant of the matrix: %f\n", det);
	
	Adj.Msize = A.Msize;
	sign = 1;
	i = 0;
	j = 0;
	pthread_t th[Adj.Msize*Adj.Msize];
	
	printf("\nCofactor matrix:\n");
	for (int i = 0; i < Adj.Msize*Adj.Msize; ++i)
		pthread_create(&th[i], NULL, Cofactor, NULL);
	for (int i = 0; i < Adj.Msize*Adj.Msize; ++i)
		pthread_join(th[i], NULL);

	Mdisplay(Adj);

	printf("\nAdjugate Matrix:\n");
	for (int i = 0; i < Adj.Msize; ++i)
		for (int j = 0; j < Adj.Msize; ++j)
			if(i<j)
			{
				int temp = Adj.M[i][j];
				Adj.M[i][j] = Adj.M[j][i];
				Adj.M[j][i] = temp;
			}
	Mdisplay(Adj);

	printf("\nInverse of the matrix:\n");
	Inv = Inverse(A, det, Adj);
	Mdisplay(Inv);
	printf("\n");
	
	return 0;
}
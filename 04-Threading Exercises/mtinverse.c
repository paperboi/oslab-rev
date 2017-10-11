#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct matrix
{
	float M[5][5];
	int Msize;
}A, Adj, Inv;

float det;

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

float DeterminantREC(struct matrix A)
{
	if (A.Msize==2)
		return A.M[0][0]*A.M[1][1]-A.M[0][1]*A.M[1][0];
	else
	{
		float Det=0; int sign=1;
		for (int i = 0; i < A.Msize; ++i)
		{
				Det+=sign*A.M[0][i]*DeterminantREC(MiniMatrix(A, 0, i));
				sign=-1*sign;
		}
		return Det;
	}
}

void* Determinant()
{
	det = DeterminantREC(A);
	printf("\nDeterminant of the matrix: %f\n", det);
	pthread_exit(NULL);
}

void* Adjugate()
{
	Adj.Msize=A.Msize;
	int sign=1;

	printf("\nCofactor matrix:\n");
	for (int i = 0; i < Adj.Msize; ++i)
		for (int j = 0; j < Adj.Msize; ++j)
		{
			Adj.M[i][j]=sign*DeterminantREC(MiniMatrix(A, i, j));
			sign=-1*sign;
		}
	Mdisplay(Adj);

	printf("\nAdjugate Matrix:\n");
	for (int i = 0; i < Adj.Msize; ++i)
		for (int j = 0; j < Adj.Msize; ++j)
			if(i<j)
			{
				int temp=Adj.M[i][j];
				Adj.M[i][j]=Adj.M[j][i];
				Adj.M[j][i]=temp;
			}
	Mdisplay(Adj);
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
	pthread_t th1, th2;

	A=Minput(A);
	printf("\nGiven matrix:\n");
	Mdisplay(A);

	pthread_create (&th1, NULL, Determinant, NULL);
	pthread_create (&th2, NULL, Adjugate, NULL);

    pthread_join (th1, NULL);
    pthread_join (th2, NULL);

	printf("\nInverse of the matrix:\n");
	Inv=Inverse(A, det, Adj);
	Mdisplay(Inv);
	printf("\n");
	
	return 0;
}
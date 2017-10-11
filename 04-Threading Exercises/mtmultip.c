#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct matrix
{
	float M[5][5];
	int row, col;
}A, B, C;

int count=65, i=0, j=0;
float det;

struct matrix Minput(struct matrix P)
{
	printf("\nMatrix %c: ", count++);
	printf("\nEnter the no.of rows of the matrix: ");
	scanf("%d", &P.row);
	printf("\nEnter the no.of columns of the matrix: ");
	scanf("%d", &P.col);
	printf("\nEnter the elements: \n");
	for (int i = 0; i < P.row; ++i)
		for (int j = 0; j < P.col; ++j)
			scanf("%f", &P.M[i][j]);
	return P;
}

void Mdisplay(struct matrix P)
{
	printf("\nMatrix %c: \n", count++);
	for (int i = 0; i < P.row; ++i)
	{
		for (int j = 0; j < P.col; ++j)
			printf("%f\t", P.M[i][j]);
		printf("\n");
	}
}

void* MUL()
{
	// printf("i=%d j=%d\n", i, j);

	C.M[i][j] = 0;
	
	for (int k = 0; k < A.col; ++k)
		C.M[i][j]+=A.M[i][k]*B.M[k][j];

	if (j==C.col-1)
	{
		i++; j=0;
	}
	else
		j++;

	pthread_exit(NULL);
}

int main()
{
	A = Minput(A);
	B = Minput(B);
	printf("\nGiven matrices:\n");
	count=65;
	Mdisplay(A);
	Mdisplay(B);

	if (A.col != B.row)
	{
		printf("\nMatrix multiplication between A and B not possible!");
		exit(1);
	}

	C.row = A.row;
	C.col = B.col;

	pthread_t th[C.row*C.col];

	for (int i = 0; i < C.row*C.col; ++i)
			pthread_create(&th[i], NULL, MUL, NULL);

	for (int i = 0; i < C.row*C.col; ++i)
		pthread_join(th[i], NULL);

	printf("\nA * B = C:\n");
	Mdisplay(C);
	printf("\n");
	
	return 0;
}
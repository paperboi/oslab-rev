#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int x=0, y=0;

void merge(int a[], int l, int m, int r)
{
	int n1, n2;
	n1=m+1-l;
	n2=r-m;
	int L[n1], R[n2];
	for (int i = 0; i < n1; ++i)
		L[i]=a[l+i];
	for (int j = 0; j < n2; ++j)
		R[j]=a[m+1+j];
	
	int i=0, j=0, k=l;
	while(i<n1 && j<n2)
	{
		if (L[i]<=R[j])
			a[k]=L[i++];
		else
			a[k]=R[j++];
		k++;
	}
	while(i<n1)
	{
		a[k]=L[i++];
		k++;
	}
	while(j<n2)
	{
		a[k]=R[j++];
		k++;
	}

}

void mergeSort(int a[], int l, int r)
{
	if (l<r)
	{
		int m=l+(r-l)/2;
		mergeSort(a, 0, m);
   		mergeSort(a, m+1, r);
		merge(a, l, m ,r);
	}
}

int main()
{
    int a[20], n, m;

    printf("\nEnter the size of the array: ");
    scanf("%d", &n);
    printf("\nEnter the elements of the array: ");
    for (int i = 0; i < n; ++i)
    	scanf("%d", &a[i]);
   
    m=n/2;
   
   	pid_t pid=fork();
   	if(pid==0)
		mergeSort(a, 0, m);
   	else
   	{
   		wait(NULL);
   		mergeSort(a, m+1, n-1);
   	}
   	
   	merge(a, 0, m, n-1);
   
    if(pid>0)
    {
    	printf("\nSorted array: ");
        for (int i = 0; i < n; ++i)
        	printf("%d, ", a[i]);
        printf("\n");
    }
	return 0;
}
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include "scheduler.h"
using namespace std;

int n, gantt=0;
float avgwt=0;
scheduler p[10];

// void merge(scheduler p[], int l, int m, int r)
// {
// 	int n1=l+m-1, n2=r-m;
// 	scheduler L[n1], R[n2];
// 	for (int i = 0; i < n1; ++i)
// 		L[i]=p[l+i];
// 	for (int i = 0; i < n2; ++i)
// 		R[i]=p[m+1+i];
// 	int i=0, j=0, k=1;
// 	while(i<n1 && j<n2) 
// 	{
// 		if (L[i].at<=R[j].at)
// 			p[k]=L[i++];
// 		else
// 			p[k]=R[j++];
// 		k++;
// 	}
// 	while(i<n1)
// 	{
// 		p[k]=L[i++];
// 		k++;
// 	}
// 	while(j<n2)
// 	{
// 		p[k]=R[j++];
// 		k++;
// 	}
// }

// void mergesort(scheduler p[], int l, int r)
// {
// 	int m=(l+r)/2;
// 	mergesort(p, l, m);
// 	mergesort(p, m+1, r);
// 	merge(p, l, m, r);
// }

int main()
{
	cout<<"\nEnter the no. of processes: ";
	cin>>n;
	for (int i = 0; i < n; ++i)
		p[i].pinput();

	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
			if (p[j].at < p[i].at)
				swap(p[i], p[j]);

	gantt=p[0].at;
	for (int i = 0; i < n; ++i)
	{
		gantt+=p[i].bt;
		p[i].ct=gantt;
		p[i].tat=p[i].ct-p[i].at;
		p[i].wt=p[i].tat-p[i].bt;
		avgwt+=p[i].wt;
	}

	pid_t pid = fork();

	if (pid>0)
	{
		cout<<"\nParent process: \n\tMerge sort:";
		mergesort(p, 0, n-1);

	}
	else
	{
		cout<<"\nChild process: \n\tQuick sort:";
		quicksort();
	}
	// cout<<"\nFirst Come First Serve Processing Schedule: ";
	// cout<<"\n------------------------------------------";
	// for (int i = 0; i < n; ++i)
	// 	p[i].pdisplay();
	// cout<<"\nAverage wait time: "<<avgwt/n<<endl;
	return 0;
}
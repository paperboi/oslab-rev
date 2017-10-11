#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "scheduler.h"
using namespace std;

int n, gantt=0;
float avgwt=0;
scheduler p[10];

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
	cout<<"\nFirst Come First Serve Processing Schedule: ";
	cout<<"\n------------------------------------------";
	for (int i = 0; i < n; ++i)
		p[i].pdisplay();
	cout<<"\nAverage wait time: "<<avgwt/n<<endl;
	return 0;
}
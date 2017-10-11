#include <iostream>
#include <algorithm>
#include "scheduler.h"
using namespace std;

int n, gantt=0, avgwt=0, btsum=0, maxpty, item, found;
bool done[10];
scheduler2 p[10];

int checkfornextrun(int i)
{
	found=0;
	maxpty=p[i].pty;
	item=i;
	for (int j = 0; j < n; ++j)
		if (p[j].pty>maxpty && p[j].at<=gantt && done[j]==false)
		{
			item=j;
			maxpty=p[j].pty;
			found=1;
		}
	if (found==0)
	{
		int prevmaxpty=maxpty;
		maxpty=p[0].pty;
		for (int j = 0; j < n; ++j)
			if (p[j].pty>maxpty && p[j].at<=gantt && done[j]==false)
			{
				item=j;
				maxpty=p[j].pty;
				found=1;
			}
	}
	return item;
}

void run(int i)
{
	if(i==n || gantt>=btsum)
		return;
	else
	{	gantt+=p[i].bt;
		p[i].ct=gantt;
		p[i].tat=p[i].ct-p[i].at;
		p[i].wt=p[i].tat-p[i].bt;
		avgwt+=p[i].wt;
		done[i]=true;
		p[i].pdisplay();
		run(checkfornextrun(i));
	}
}

int main()
{	
	cout<<"\nEnter the no. of processes: ";
	cin>>n;
	for (int i = 0; i < n; ++i)
	{	
		p[i].pinput();
		done[i]=false;
		btsum+=p[i].bt;
	}

	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
			if (p[j].at < p[i].at)
				swap(p[i], p[j]);

	cout<<"\nNon-premptive Priority Processing Schedule: ";
	cout<<"\n------------------------------------------";
	gantt=p[0].at;
	run(0);
	cout<<"\nAverage wait time: "<<avgwt/n<<endl;
	return 0;
}
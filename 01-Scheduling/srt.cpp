#include <iostream>
#include "scheduler.h"
using namespace std;

int n, gantt=0, min_rt, min_i, btsum=0;
scheduler p[10], temp;

void run(int i)
{
	if (i >= n || gantt==btsum)
		return;
	else
	{
		p[i].rt=p[i].rt-1;
		gantt++;
		min_rt=p[i].rt;
		// cout<<"\npid="<<p[i].pid<<"\tgantt="<<gantt<<"\trt: "<<p[i].rt<<"\tmin_rt: "<<min_rt;
		if (min_rt == 0)	//If process i is completed
		{
			p[i].ct=gantt;
			min_i=0;
			min_rt=p[0].rt;
			for (int j = 0; j < n; ++j)
				if (p[j].at <= gantt && p[j].rt<min_rt && p[j].rt!=0 && j!=i)
				{
					min_i=j;
					min_rt=p[j].rt;
					// cout<<"loop runs "<<j+1;
				}
		}
		else	//If process i is not completed
		{
			for (int j = 0; j < n; ++j)
				if (p[j].at <= gantt && 0<p[j].rt<=min_rt && p[j].rt!=0)
				{
					if (p[j].rt == min_rt && p[j].at>p[min_i].at)
					{
						
					}
					else
					{
						min_i=j;
						min_rt=p[j].rt;
					}
				}
		}
		run(min_i);
	}
}

int main()
{
	cout<<"\nEnter the no. of processes: ";
	cin>>n;
	for (int i = 0; i < n; ++i)
	{
		p[i].pid=i+1;
		cout<<"\nProcess ID: "<<p[i].pid;
		cout<<"\nEnter the arrival time: ";
		cin>>p[i].at;
		cout<<"Enter the burst time: ";
		cin>>p[i].bt;

		p[i].rt=p[i].bt;
		btsum+=p[i].bt;
	}
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
		{
			if (p[j].at < p[i].at)
			{
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
 			}
		}
	min_rt=p[0].rt, min_i=0;
	run(0);

	for (int i = 0; i < n; ++i)
	{
		p[i].tat=p[i].ct-p[i].at;
		p[i].wt=p[i].tat-p[i].bt;
	}
	cout<<"\nShortest Job First First Processing Schedule (Premptive): ";
	cout<<"\n--------------------------------------------------------";
	for (int i = 0; i < n; ++i)
	{
		cout<<"\nProcess ID: "<<p[i].pid;
		cout<<"\tArrival Time: "<<p[i].at;
		cout<<"\tBurst Time: "<<p[i].bt;
		cout<<"\tCompletion Time: "<<p[i].ct;
		cout<<"\tTurn-around Time: "<<p[i].tat;
		cout<<"\tWaiting Time: "<<p[i].wt;
	}
	cout<<endl;
	return 0;
}
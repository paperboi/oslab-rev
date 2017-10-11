#include <iostream>
#include "scheduler.h"
using namespace std;

int n, gantt=0, minrt, item, btsum=0;
float avgwt=0;
bool done[10];
scheduler p[10], temp[10];

void tempsort()
{
	for (int i = 0; i < n; ++i)
	{
		temp[i]=p[i];
	}
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
		{
			if (temp[j].bt==temp[i].bt)
			{
				if (temp[j].at<temp[i].at)
					swap(temp[i], temp[j]);
			}
			else
			{
				if (temp[j].rt < temp[i].rt)
					swap(temp[i], temp[j]);
			}
		}
}

int checkfornextrun(int i)
{
	int found=0;
	minrt=p[i].rt;
	item=i;
	for (int j = 0; j < n; ++j)
		if (p[j].rt<minrt && p[j].at<=gantt && done[j]==false)
		{
			item=j;
			minrt=p[j].rt;
			found=1;
		}
	if (found==0)
	{
		int prevminrt=minrt;
		minrt=temp[n-1].rt; item=n-1;
		for (int j = 0; j < n; ++j)
			if (p[j].rt<minrt && p[j].at<=gantt && done[j]==false && minrt!=prevminrt)
			{
				item=j;
				minrt=p[j].rt;
				found=1;
			}
	}
	if (found==0)
		for (int j = 0; j < n; ++j)
			if (p[j].at<=gantt && done[j]==false)
			{
				minrt=p[j].rt;
				item=j;
				found=1;
			}

	return item;
}

void run(int i)
{
	if(gantt>=btsum)
		return;
	else
	{	gantt++;
		p[i].rt--;
		cout<<"\npid="<<p[i].pid<<"\tgantt="<<gantt<<"\trt: "<<p[i].rt;
		if (p[i].rt==0)
		{
			p[i].ct=gantt;
			p[i].tat=p[i].ct-p[i].at;
			p[i].wt=p[i].tat-p[i].bt;
			avgwt+=p[i].wt;
			done[i]=true;
			// p[i].pdisplay();
		}
		tempsort();
		run(checkfornextrun(i));
	}
}

int main()
{
	cout<<"\nEnter the no. of processes: ";
	cin>>n;
	for (int i = 0; i < n; ++i)
	{	p[i].pinput();
		btsum+=p[i].bt;
		done[i]=false;
	}
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
		{
			if (p[i].at==p[j].at)
			{
				if (p[j].bt<p[i].bt)
					swap(p[i], p[j]);
			}
			else
			{
				if (p[j].at < p[i].at)
					swap(p[i], p[j]);
			}
		}
	tempsort();
	cout<<"\nShortest Remaining Time First Processing Schedule (Premptive): ";
	cout<<"\n-------------------------------------------------------------";
	gantt=p[0].at;
	run(0);
	for (int i = 0; i < n; ++i)
		p[i].pdisplay();
	cout<<"\nAverage wait time: "<<avgwt/n<<endl;
	return 0;
}
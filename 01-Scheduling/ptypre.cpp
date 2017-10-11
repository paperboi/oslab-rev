#include <iostream>
#include <algorithm>
#include "scheduler.h"
using namespace std;

int n, gantt=0, btsum=0, maxpty, item, found;
float avgwt=0;
bool done[10];
scheduler2 p[10], temp[10];

void tempsort()
{
	for (int i = 0; i < n; ++i)
	{
		temp[i]=p[i];
	}
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
		{
			if (temp[j].pty==temp[i].pty)
			{
				if (temp[j].at==temp[i].at)
				{
					if (temp[j].bt==temp[i].bt)
					{
						if (temp[j].pid<temp[i].pid)
							swap(temp[i], temp[j]);								
					}
					else
					{
						if (temp[j].bt<temp[i].bt)
							swap(temp[i], temp[j]);	
					}
				}
				else
				{
					if (temp[j].at<temp[i].at)
						swap(temp[i], temp[j]);
				}
			}
			else
			{
				if (temp[j].pty > temp[i].pty)
					swap(temp[i], temp[j]);
			}
		}
}

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
		maxpty=temp[n-1].pty;
		item=n-1;
		for (int j = 0; j < n; ++j)
			if (p[j].pty>maxpty && p[j].at<=gantt && done[j]==false && p[j].pty!=prevmaxpty)
			{
				item=j;
				maxpty=p[j].pty;
				found=1;
			}
		if (found==0)
			for (int j = 0; j < n; ++j)
				if (p[j].at<=gantt && done[j]==false)
				{
					maxpty=p[j].pty;
					item=j;
					found=1;
				}
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
	{	
		p[i].pinput();
		done[i]=false;
		btsum+=p[i].bt;
	}

	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
		{
			if (p[j].at==p[i].at)
			{
				if (p[j].bt==p[i].bt)
				{
					if (p[j].pty==p[i].pty)
					{
						if (p[j].pid<p[i].pid)
							swap(p[i], p[j]);
					}
					else
					{
						if (p[j].pty>p[i].pty)
							swap(p[i], p[j]);
					}	
				}
				else
				{
					if (p[j].bt<p[i].bt)
						swap(p[i], p[j]);
				}
			}
			else
			{
				if (p[j].at < p[i].at)
					swap(p[i], p[j]);
			}
		}

	tempsort();

	cout<<"\nPremptive Priority Processing Schedule: ";
	cout<<"\n--------------------------------------";
	gantt=p[0].at;
	run(0);
	for (int i = 0; i < n; ++i)
		p[i].pdisplay();		
	cout<<"\nAverage wait time: "<<avgwt/n<<endl;
	return 0;
}
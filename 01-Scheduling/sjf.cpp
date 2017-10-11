#include <iostream>
#include <algorithm>
#include "scheduler.h"
using namespace std;

int n, gantt=0, btsum=0;
float avgwt=0;
bool done[10];
scheduler p[10], temp[10];

int checkfornext(int i)
{
	int minbt=p[i].bt, item=i, found=0;
	for (int j = 0; j < n; ++j)
		if (p[j].at<=gantt && p[j].bt<minbt && done[j]==false)
		{
			minbt=p[j].bt;
			item=j;
			found=1;
		}
	if (found==0)
	{
		int prevminbt=minbt;
		minbt=temp[n-1].bt; item=n-1;
		for (int j = 0; j < n; ++j)
			if (p[j].at<=gantt && p[j].bt<=minbt && done[j]==false && p[j].bt!=prevminbt)
			{
				minbt=p[j].bt;
				item=j;
				found=1;
			}
		if (found==0)
			for (int j = 0; j < n; ++j)
				if (p[j].at<=gantt && done[j]==false)
				{
					minbt=p[j].bt;
					item=j;
					found=1;
				}
	}
	return item;
}

void run(int i)
{
	if (gantt>=btsum)
		return;
	else
	{
		gantt+=p[i].bt;
		p[i].ct=gantt;
		p[i].tat=p[i].ct-p[i].at;
		p[i].wt=p[i].tat-p[i].bt;
		avgwt+=p[i].wt;
		done[i]=true;
		p[i].pdisplay();

		// cout<<"\npid: "<<p[i].pid<<"\tgantt: "<<gantt;

		run(checkfornext(i));
	}
}

int main()
{
	cout<<"\nEnter the no. of processes: ";
	cin>>n;
	for (int i = 0; i < n; ++i)
	{
		p[i].pinput();
		btsum+=p[i].bt;
		done[i]=false;
		temp[i]=p[i];
	}
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
		{
			if (p[j].at==p[i].at)
			{
				if (p[j].bt==p[i].bt)
				{
					if (p[j].pid<p[i].pid)
						swap(p[i], p[j]);	
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
				if (temp[j].bt==temp[i].bt)
				{
					if (temp[j].pid<temp[i].pid)
						swap(temp[i], temp[j]);
				}
				else
				{
					if (temp[j].bt < temp[i].bt)
						swap(temp[i], temp[j]);
				}
			}
		}

	cout<<"\nShortest Job First Processing Schedule (Non-premptive): ";
	cout<<"\n------------------------------------------------------";
	gantt=p[0].at;
	run(0);
	// for (int i = 0; i < n; ++i)
		// p[i].pdisplay();
	cout<<"\nAverage wait time: "<<avgwt/n<<endl;
	return 0;
}
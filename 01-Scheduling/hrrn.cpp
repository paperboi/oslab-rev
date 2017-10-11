#include <iostream>
#include <algorithm>
#include "scheduler.h"
using namespace std;

int n, btsum=0;
float rr[10], avgwt=0, gantt=0;
bool done[10];
scheduler3 p[10];

void run(int i)
{
	if (i==n || gantt>=btsum)
		return;
	else
	{
		done[i]=true;
		p[i].rspt=gantt;
		gantt+=p[i].bt;
		p[i].ct=gantt;
		p[i].tat=p[i].ct-p[i].at;
		p[i].wt=p[i].tat-p[i].bt;
		p[i].rspt-=p[i].at;
		avgwt+=p[i].wt;
		p[i].pdisplay();
		// cout<<"\ngantt= "<<gantt;
	
		for (int j = 0; j < n; ++j)
		{	
			rr[j]=0;
			if (p[j].at<=gantt && done[j]==false)
			{	
				rr[j]=(gantt-p[j].at + p[j].bt)/p[j].bt;
				cout<<"\trr "<<p[j].pid<<": "<<rr[j];
			}
		}
		int max=0;
		for (int j = 0; j < n; ++j)
			if (rr[j]>rr[max])
				max=j;
		run(max);
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
	
	cout<<"\nHighest Response Ratio Next Processing Schedule: ";
	cout<<"\n-----------------------------------------------";
	gantt=p[0].at;
	run(0);
	cout<<"\nAverage wait time: "<<avgwt/n<<endl;
	return 0;
}
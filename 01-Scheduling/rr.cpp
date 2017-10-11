#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include "scheduler.h"
using namespace std;

int n, tq, gantt=0;
float avgwt=0;
scheduler p[10];
bool pushed[10];

queue <int> rq;

void arrivalcheck()
{
	for (int i = rq.front()+1; i < n; ++i)
		if (p[i].at<=gantt && p[i].rt!=0 && pushed[i]==false)
			{
				rq.push(i);
				pushed[i]=true;
				// cout<<"\tpushed "<<p[i].pid;
			}
}

void run()
{
	while(!rq.empty()) 
	{
		cout<<"\nPid "<<p[rq.front()].pid<<"\tGantt "<<gantt<<"\tRT: "<<p[rq.front()].rt;
		if (p[rq.front()].rt>tq)
		{
			gantt+=tq;
			p[rq.front()].rt-=tq;
			int t=rq.front();
			arrivalcheck();
			rq.push(t); 
			// cout<<"\tpushed "<<p[t].pid;
			rq.pop();
		}
		else
		{
			gantt+=p[rq.front()].rt;
			p[rq.front()].rt=0;
			
			p[rq.front()].ct=gantt;
			p[rq.front()].tat=p[rq.front()].ct-p[rq.front()].at;
			p[rq.front()].wt=p[rq.front()].tat-p[rq.front()].bt;
			avgwt+=p[rq.front()].wt;
			
			// p[rq.front()].pdisplay();

			arrivalcheck();
			rq.pop();
		}
	}
}

int main()
{	
	cout<<"\nEnter the no. of processes: ";
	cin>>n;
	cout<<"\nEnter the time quantum: ";
	cin>>tq;
	for (int i = 0; i < n; ++i)
	{	
		p[i].pinput();
		pushed[i]=false;
	}
	
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
			if (p[j].at < p[i].at)
				swap(p[i], p[j]);

	gantt=p[0].at;
	cout<<"\nRound Robin Processing Schedule: ";
	cout<<"\n-------------------------------";
	rq.push(0);
	run();
	for (int i = 0; i < n; ++i)
		p[i].pdisplay();
	cout<<"\nAverage wait time: "<<avgwt/n<<endl;
	return 0;
}
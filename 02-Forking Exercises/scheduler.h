#include <iostream>
using namespace std;

int cnt=1;

class scheduler 						//For FCFS, SJF, SRTF and RR scheduling
{
	public:
		int pid, at, bt, rt, ct, tat, wt;

		void pinput()
		{
			this->pid=cnt++;
			cout<<"\nProcess ID: "<<this->pid;
			cout<<"\nEnter the arrival time: ";
			cin>>this->at;
			cout<<"Enter the burst time: ";
			cin>>this->bt;
			this->rt=this->bt;
		}

		void pdisplay()
		{
			cout<<"\nProcess ID: "<<this->pid;
			cout<<"\tArrival Time: "<<this->at;
			cout<<"\tBurst Time: "<<this->bt;
			cout<<"\tCompletion Time: "<<this->ct;
			// cout<<"\tRemaining Time: "<<this->rt;
			cout<<"\tTurn-around Time: "<<this->tat;
			cout<<"\tWaiting Time: "<<this->wt;
		}
};

class scheduler2						//For Priority scheduling
{
	public:
		int pid, pty, at, bt, rt, ct, tat, wt;

		void pinput()
		{
			this->pid=cnt++;
			cout<<"\nProcess ID: "<<this->pid;
			cout<<"\nEnter the priority value: ";
			cin>>this->pty;
			cout<<"Enter the arrival time: ";
			cin>>this->at;
			cout<<"Enter the burst time: ";
			cin>>this->bt;
			this->rt=this->bt;
		}
		void pdisplay()
		{
			cout<<"\nProcess ID: "<<this->pid;
			cout<<"\tPriority: "<<this->pty;	
			cout<<"\tArrival Time: "<<this->at;
			cout<<"\tBurst Time: "<<this->bt;
			cout<<"\tCompletion Time: "<<this->ct;
			cout<<"\tTurn-around Time: "<<this->tat;
			cout<<"\tWaiting Time: "<<this->wt;
		}
};

class scheduler3						//For HRRN
{
	public:
		int pid, at, bt, rt, ct, tat, wt, rspt;

		void pinput()
		{
			this->pid=cnt++;
			cout<<"\nProcess ID: "<<this->pid;
			cout<<"\nEnter the arrival time: ";
			cin>>this->at;
			cout<<"Enter the burst time: ";
			cin>>this->bt;
			this->rt=this->bt;
		}

		void pdisplay()
		{
			cout<<"\nProcess ID: "<<this->pid;
			cout<<"\tArrival Time: "<<this->at;
			cout<<"\tBurst Time: "<<this->bt;
			cout<<"\tCompletion Time: "<<this->ct;
			cout<<"\tTurn-around Time: "<<this->tat;
			cout<<"\tWaiting Time: "<<this->wt;
			cout<<"\tResponse Time: "<<this->rspt;
		}
};
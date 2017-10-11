#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

void zombie()
{
	cout<<"\nZombie Process";
	cout<<"\n--------------\n";
	pid_t pid=fork();
	if (pid>0)
	{
		sleep(5);
		cout<<"Parent process terminated\n";
	}
	else
		cout<<"Child process terminated\n";
}

void orphan()
{
	cout<<"\nOrphan Process";
	cout<<"\n--------------\n";
	pid_t pid=fork();
	if (pid>0)
	{
		sleep(5);
		cout<<"Child process terminated\n";
	}
	else
		cout<<"Parent process terminated\n";
}

int main()
{
	int n;
	cout<<"\nChoose the process: \n1. Zombie\t2. Orphan\n";
	cin>>n;
	switch(n)
	{
		case 1:
			zombie();
			break;
		case 2:
			orphan();
			break;
		default:
			cout<<"\nWrong option!";
	}
	return 0;
}
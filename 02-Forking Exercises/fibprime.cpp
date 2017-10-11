#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int n;

int main()
{
	cout<<"\nEnter the number: ";
	cin>>n;
	pid_t pid=fork();

	if (pid>0)
	{
		cout<<"\nParent: \n\tFibonacci series: ";
		int f=0, s=1, t=1;
		cout<<f<<", "<<s<<", ";
		while(t<=n) 
		{
			cout<<t<<", ";
			f=s;
			s=t;
			t=f+s;
		}
	}
	else
	{
		cout<<"\nChild: \n\tPrime number series: ";
		for (int i = 2; i <=n; ++i)
		{
			int flag=0;
			for (int j = 2; j < i; ++j)
			{
				if (i%j==0)
				{
					flag=1;
				}
			}
			if (flag==0)
			{
				cout<<i<<", ";
			}
		}
	}
	cout<<endl;
	return 0;
}
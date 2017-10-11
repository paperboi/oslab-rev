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
		cout<<"\nParent: \n\tOdd series: ";
		for (int i = 1; i <=n; ++i)
			if (i%2!=0)
				cout<<i<<", ";
	}
	else
	{
		cout<<"\nChild: \n\tEven series: ";
		for (int i = 1; i <=n; ++i)
			if (i%2==0)
				cout<<i<<", ";
	}
	cout<<endl;
	return 0;
}
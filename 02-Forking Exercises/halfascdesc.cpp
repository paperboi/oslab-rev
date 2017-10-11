#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <vector>

using namespace std;

int n, a[20];

int main()
{
	cout<<"\nEnter the size of the array: ";
	cin>>n;
	for (int i = 0; i < n; ++i)
	{
		cout<<"\nEnter the "<<i+1<<"th number: ";
		cin>>a[i];
	}
	sort(a, a+n);

	pid_t pid=fork();
	if (pid>0)
	{
		cout<<"\nParent: \n\tAscending order series: ";
		for (int i = 0; i <n; ++i)
			cout<<a[i]<<", ";
	}
	else
	{
		cout<<"\nChild: \n\tDescending order series: ";
		for (int i = n-1; i >=0; i--)
			cout<<a[i]<<", ";
	}
	cout<<endl;
	return 0;
}
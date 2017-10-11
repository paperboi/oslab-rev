#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>

using namespace std;

int n, a[30];

int main()
{
	cout<<"\nEnter the size of the array: ";
	cin>>n;
	for (int i = 0; i < n; ++i)
	{
		cout<<"\nEnter the "<<i+1<<"th number: ";
		cin>>ip;
		v.push_back(ip);
	}
	// sort(a, a+n);

	pid_t pid=fork();
	if (pid>0)
	{
		cout<<"\nParent: \n\tAscending order series: ";
		
		vector<int> v(a, a+n/2);
		sort(v.begin(), v.begin()+n/2);
		for (vector<int>::iterator i=v.begin(); i<=v.begin()+n/2; ++i)
			cout<< *i <<", ";
	}
	else
	{
		cout<<"\nChild: \n\tDescending order series: ";
		
		vector<int> v(a+n/2+1, a+n);
		sort(v.begin()+n/2+1, v.end());
		for (vector<int>::iterator i=v.begin()+n/2+1; i<v.end(); ++i)
			cout<< *i <<", ";
	}
	cout<<endl;
	return 0;
}
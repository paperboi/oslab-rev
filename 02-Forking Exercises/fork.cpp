#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace  std;

int n, count;

int main()
{
	pid_t pid=fork();
	if (pid>0)
		cout<<"This is the parent process.\n";
	else
		cout<<"This is the child process.\n";
	return 0;
}
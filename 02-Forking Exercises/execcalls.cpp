#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

void execvpcall()
{
    cout<<"\nExecvp call for 'pwd'";
    char *args[]={"-L",NULL};
    execvp("pwd", args);
    cout<<"\nThis statement should not be displayed!";
}

void execvcall()
{
    cout<<"\nExecv call for 'pwd'";
	char *args[]={"/bin/pwd", "-L", NULL};
    execv("/bin/pwd", args);
    cout<<"\nThis statement should not be displayed!";
}

void execlpcall()
{
    cout<<"\nExeclp call for 'pwd'";
    execlp("pwd", "pwd", "-L", NULL);
    cout<<"\nThis statement should not be displayed!";
}

void execlcall()
{
    cout<<"\nExecl call for 'pwd'";
    execl("/bin/pwd", "/bin/pwd", "-L", NULL);
    cout<<"\nThis statement should not be displayed!";
}

int main()
{
	int n;
	cout<<"1. execvp\t2. execv\t3. execlp\t4. execl\n";
	cin>>n;
	switch(n)
	{
		case 1:	execvpcall(); break;
		case 2: execvcall(); break;
		case 3: execlpcall(); break;
		case 4: execlcall(); break;
		default: cout<<"\nWrong choice!";
	}
	return 0;
}
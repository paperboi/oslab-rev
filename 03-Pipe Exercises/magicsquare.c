#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>

int ms[10][10];

void generate(int n)
{
    int i,j,num;

    for(i=0;i<n;i++)
     for(j=0;j<n;j++)
      ms[i][j]=0;

    i = n/2;
    j = n-1;
 
    for (num=1; num <= n*n; )
    {
        if (i==-1 && j==n) 
        {
            j = n-2;
            i = 0;
        }
        else
        {
            if (j == n)
                j = 0;

            if (i < 0)
                i=n-1;
        }
        if (ms[i][j]) 
        {
            j -= 2;
            i++;
            continue;
        }
        else
            ms[i][j] = num++; 
 
        j++; 
        i--; 
    }
}

void check(int n)
{
	int i,j,sum_t=0,sum=0,flag=0;
    
	for(i=0; i<n; i++)
         sum+=ms[i][0];
     
	for(i=0; i<n; i++)
	{
		sum_t=0;
		for(j=0; j<n; j++)
		 sum_t+=ms[i][j];
		 
		if(sum_t!=sum)
		{
		 flag=1;
		 break;
		}
	}
	for(i=0; i<n; i++)
	{
		sum_t=0;
		for(j=0; j<n; j++)
		 sum_t+=ms[j][i];
		 
		if(sum_t!=sum)
		{
		 flag=1;
		 break;
		}
	}
	
	sum_t=0;
	
	for(i=0; i<n; i++)
		sum_t+=ms[i][i];
		
	if(sum_t!=sum)
	 flag=1;

	if(flag==1)
	printf("It is not a magic square");
	
	else
	for(i=0; i<n; i++)
    	{
        	for(j=0; j<n; j++)
            	 printf("%d ", ms[i][j]);
        	printf("\n");
    	}
	
}
 
int main()
{
    int n = 5;
    pid_t pid;
    
    pid=vfork();
    
    if(pid==0)
    {
	    generate(n);
	    exit(0);
    }
    
    else if(pid>0)
    {
    	wait(pid);
    	check(n);
    }
    return 0;
}

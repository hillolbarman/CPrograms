#include<stdio.h>
#include<sys/types.h>
//#include<unistd.h>
void child()
{
	printf("I am the child.\n");
	int i;
	pid_t pid = getpid();
	//for(i=0;i<200;i++)
	//	printf("Process id: %d\tValue: %d\n",pid,i);
	for(i=0;i<100;i++)
		printf("Process id: %d\tValue: %d\n",pid,i);
}

void parent()
{
	printf("I am the parent.\n");
	wait();
	pid_t pid = getpid();	
	int i;
	//for(i=0;i<200;i++)
	//	printf("Process id: %d\tValue: %d\n",pid,i);
	for(i=0;i<10;i++)
	{
		printf("Process id: %d\tValue: %d\n",pid,i);
		/*if(i==5)
		{
			printf("Parent sleeps.\n");
			wait();
			printf("Parent revives.\n");
		}*/
	}
}
int main()
{
	pid_t pid;
	pid=fork();
		//printf("Pid: %d\n",pid);
		//printf("My pid: %d\n",getpid());
		//pid = getpid();
		if(pid == 0)
			child();
		else if(pid < 0)
			printf("Error\n");
		else
			parent();
	return 0;
}


#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
void parent()
{
	printf("I am the parent.\n");
	pid_t pid = getpid();
	int i;
	for(i=0;i<1;i++)
	{
		printf("Process id: %d\tValue: %d\n",pid,i);
	}
}

int main()
{
	pid_t pid;
	pid=fork();
		if(pid == 0)
			execlp( "/bin/date", "date", NULL);
		else if(pid < 0)
			printf("Error\n");
		else
			parent();
	return 0;
}

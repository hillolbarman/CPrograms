#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
void parent()
{
	printf("I am the parent.\n");
	pid_t pid = getpid();
	int i;
	for(i=0;i<10;i++)
	{
		printf("Process id: %d\tValue: %d\n",pid,i);
	}
}

int main()
{
	pid_t pid;
	char* argv[3]={"command-line", "-l", NULL};
	pid=fork();
		if(pid == 0)
			execvp("ls",argv);
		else if(pid < 0)
			printf("Error\n");
		else
			parent();
	return 0;
}

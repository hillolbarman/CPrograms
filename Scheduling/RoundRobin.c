/*
 * RoundRobin.c
 *
 *  Created on: 28-Jul-2017
 *      Author: Hillol
 */
/*
 * SJF.c
 *
 *  Created on: 28-Jul-2017
 *      Author: Hillol
 */

#include<stdio.h>
#include<string.h>
typedef struct Process
{
	int pId;
	int arrivalTime,burstTime,turnAroundTime,responseTime,waitingTime;
	float normalisedTAT;
} process;

typedef struct Status
{
	int pId;
	int remTime;
	int startTime;
	int endTime;
	int isDone;
} status;

typedef struct Gnatt
{
	int pId;
	int slotNo;
	int slotStart;
	int slotEnd;
}gnatt;

int n;
process proc[10];
status st[10];
gnatt gn[100];
int queue[100],rear=-1;
int quantum;

void getInput()
{
	int i=0;
	printf("Enter the number of processes: ");
	scanf("%d", &n);
	for(i=0;i<n;i++)
	{
		proc[i].pId=i+1;
		printf("P%d\nBurst time= ",i+1);	scanf("%d", &proc[i].burstTime);
		printf("Arrival time= ");	scanf("%d", &proc[i].arrivalTime);
	}
	for(i=0;i<n;i++)
	{
		st[i].isDone=0;
		st[i].pId=proc[i].pId;
		st[i].remTime=proc[i].burstTime;
		st[i].startTime=-1;
	}
	printf("Enter the time Quantum: ");		scanf("%d", &quantum);
}

void sortArrival()
{
	process temp;
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(proc[j].arrivalTime>proc[j+1].arrivalTime)
			{
				temp=proc[j];
				proc[j]=proc[j+1];
				proc[j+1]=temp;
			}
		}
	}
}

void push(int a)
{
	queue[++rear]=a;
}

void pop()
{
	int i;
	for(i=0;i<rear;i++)
		queue[i]=queue[i+1];
	queue[rear]='\0';
	rear--;
}

void prepareQueue(int time)
{
	int i;
	for(i=0;i<n;i++)
	{
		if( proc[i].arrivalTime >= time-quantum+1 && proc[i].arrivalTime <= time)
		{
			push(proc[i].pId);
		}
	}
}

void generateGnatt()
{
	int time=0,i,loop=1,slot=0,p=0;
	prepareQueue(time);
		while(loop)
		{
			loop=0;
					for(i=0;i<n;i++)
					{
						if(!st[i].isDone)
							loop=1;
					}
			gn[slot].pId=st[queue[0]-1].pId;
			gn[slot].slotNo=slot;
			gn[slot].slotStart=time;
			if(st[queue[0]-1].startTime==-1)
				st[queue[0]-1].startTime=time;
			if(st[queue[0]-1].remTime<quantum&&st[queue[0]-1].remTime>0)
			{
				st[queue[0]-1].isDone=1;
				st[queue[0]-1].endTime=time+st[queue[0]-1].remTime;
				time+=st[queue[0]-1].remTime;
			}
			if(st[queue[0]-1].remTime>=quantum)
			{
				if(st[queue[0]-1].remTime!=quantum)
					p=1;
				st[queue[0]-1].remTime-=quantum;
				time+=quantum;
			}
			if(st[queue[0]-1].remTime==0)
			{
				st[queue[0]-1].isDone=1;
				st[queue[0]-1].endTime=time;
			}
			prepareQueue(time);
			if(p)
				push(st[queue[0]-1].pId);
			p=0;
			pop();
			gn[slot].slotEnd=time;
			slot++;
		}
}

void getTAT()
{
	int i;
	for(i=0;i<n;i++)
		proc[i].turnAroundTime=st[proc[i].pId-1].endTime-proc[i].arrivalTime;
}

void getResponse()
{
	int i;
	for(i=0;i<n;i++)
		proc[i].responseTime=st[proc[i].pId-1].startTime-proc[i].arrivalTime;
}

void getWait()
{
	int i;
	for(i=0;i<n;i++)
		proc[i].waitingTime=(st[proc[i].pId-1].endTime-st[proc[i].pId-1].startTime-proc[i].burstTime)
							 + (st[proc[i].pId-1].startTime-proc[i].arrivalTime);
}

void getNormTAT()
{
	int i;
	for(i=0;i<n;i++)
		proc[i].normalisedTAT=(float)proc[i].turnAroundTime/proc[i].burstTime;
}

float getAvgTAT()
{
	int i;float sum=0;
	for(i=0;i<n;i++)
		sum+=proc[i].turnAroundTime;
	return sum/n;
}

float getAvgWT()
{
	int i;float sum=0;
	for(i=0;i<n;i++)
		sum+=proc[i].waitingTime;
	return sum/n;
}

float getAvgRT()
{
	int i;float sum=0;
	for(i=0;i<n;i++)
		sum+=proc[i].responseTime;
	return sum/n;
}

float getAvgNTAT()
{
	int i;float sum=0;
	for(i=0;i<n;i++)
		sum+=proc[i].normalisedTAT;
	return sum/n;
}

void printOutput()
{
	int i;
	for(i=0;i<100&&gn[i].pId!='\0';i++)
		{
			printf("    P%d\t",gn[i].pId);
		}
		printf("\n0");
		for(i=0;i<100&&gn[i].pId!='\0';i++)
		{
			printf("\t%d",gn[i].slotEnd);
		}
		printf("\n\n\tTAT\tRT\tWT\tNTAT\n");
		for(i=0;i<n;i++)
		{
			printf("\nP%d\t",proc[i].pId);
			printf("%d\t",proc[i].turnAroundTime);
			printf("%d\t",proc[i].responseTime);
			printf("%d\t",proc[i].waitingTime);
			printf("%f\t",proc[i].normalisedTAT);
			printf("\n");
		}
		printf("\nAverage Turn around time= %f",getAvgTAT());
		printf("\nAverage Waiting time= %f",getAvgWT());
		printf("\nAverage Response time= %f",getAvgRT());
		printf("\nAverage Normalized Turn around time= %f\n",getAvgNTAT());
}

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	getInput();
	sortArrival();
	generateGnatt();
	getTAT();
	getResponse();
	getWait();
	getNormTAT();
	printOutput();

	return(0);
}





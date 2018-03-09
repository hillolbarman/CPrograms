/*
 * SJF.c
 *
 *  Created on: 28-Jul-2017
 *      Author: Hillol
 */

#include<stdio.h>
#include<stdbool.h>
#include<string.h>
typedef struct Process
{
	int pId;
	int arrivalTime,burstTime,turnAroundTime,responseTime,waitingTime;
	float normalisedTAT;
} process;

typedef struct Gnatt
{
	int pId;
	int startTime;
	int endTime;
	int isDone;
} gnatt;

int n;
process proc[10];
gnatt gc[100];

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
		gc[i].isDone=0;
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

void sortSJF(int time)
{
	int i,j,s;
	process temp;
	for(i=0;i<n;i++)
		{
			if(gc[i].isDone)
			{	s=i; continue;}
			for(j=s+1;j<n-1;j++)
			{
				if(proc[j].burstTime>proc[j+1].burstTime&&proc[j].arrivalTime<=time&&proc[j+1].arrivalTime<=time)
				{
					temp=proc[j];
					proc[j]=proc[j+1];
					proc[j+1]=temp;
				}
			}
		}
}

void generateGnatt()
{
	int time=0,x;
	{
		for(x=0;x<n;x++)
		{
			sortSJF(time);
			gc[x].pId=proc[x].pId;
			if(time<proc[x].arrivalTime)
				time=proc[x].arrivalTime;
			gc[x].startTime=time;
			time+=proc[x].burstTime;
			gc[x].endTime=time;
			gc[x].isDone=1;
		}
	}
}

void getTAT()
{
	int i;
	for(i=0;i<n;i++)
		proc[i].turnAroundTime=gc[i].endTime-proc[i].arrivalTime;
}

void getResponse()
{
	int i;
	for(i=0;i<n;i++)
		proc[i].responseTime=gc[i].startTime-proc[i].arrivalTime;
}

void getWait()
{
	int i;
	for(i=0;i<n;i++)
		proc[i].waitingTime=gc[i].startTime-proc[i].arrivalTime;
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
	for(i=0;i<n;i++)
		{
			printf("\tP%d",gc[i].pId);
		}
		printf("\n0");
		for(i=0;i<n;i++)
		{
			if(i!=0&&gc[i].startTime!=gc[i-1].endTime)
				printf("---%d",gc[i].startTime);
			printf("\t%d",gc[i].endTime);

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





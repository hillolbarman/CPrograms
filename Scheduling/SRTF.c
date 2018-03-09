/*
 * SRTF.c
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
	int remTime,start,end;
} process;

typedef struct Gnatt
{
	int pId;
	int startTime;
	int endTime;
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
		proc[i].remTime=proc[i].burstTime;
		proc[i].start=-1;
	}
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

int checkShort(int time)
{
	int r=0;
	while(proc[r].remTime==0)
	{	r++;
		if(r==n)
			break;
	}
	int i;
		for(i=0;i<n;i++)
		{
			if(proc[i].remTime==0)
				continue;
			if(proc[i].remTime<proc[r].remTime&&proc[i].arrivalTime<=time)
				r=i;
		}
		return r;
}

void generateGnatt()
{
	int time=0,current=checkShort(time),x=0,loop=1,i;
	gc[0].startTime=0;
	gc[0].pId=proc[current].pId;
	proc[current].start=time;
	while(loop)
	{
		loop=0;
		time++;
		proc[current].remTime--;
		for(i=0;i<n;i++)
					if(proc[i].remTime>0)
						loop=1;
		if(proc[current].remTime==0)
		{
			proc[current].end=time;
			gc[x].endTime=time;
			x++;
			if(loop)
			{
			current=checkShort(time);
			if(time<proc[current].arrivalTime)
				time=proc[current].arrivalTime;
			gc[x].pId=proc[current].pId;
			gc[x].startTime=time;
			if(proc[current].burstTime==proc[current].remTime)
				proc[current].start=time;
			}
		}
		int c=checkShort(time);
		if(c!=current)
		{
			gc[x].endTime=time;
			x++;
			if(loop)
			{
			current=c;
			if(time<proc[current].arrivalTime)
				time=proc[current].arrivalTime;
			gc[x].pId=proc[current].pId;
			gc[x].startTime=time;
			if(proc[current].burstTime==proc[current].remTime)
					proc[current].start=time;
			}
		}
	}
	printf("\n");
}

void getTAT()
{
	int i;
	for(i=0;i<n;i++)
		proc[i].turnAroundTime=proc[i].end-proc[i].arrivalTime;
}

void getResponse()
{
	int i;
	for(i=0;i<n;i++)
		proc[i].responseTime=proc[i].start-proc[i].arrivalTime;
}

void getWait()
{
	int i;
	for(i=0;i<n;i++)
		proc[i].waitingTime=proc[i].end-proc[i].start-proc[i].burstTime+proc[i].start-proc[i].arrivalTime;
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
	for(i=0;i<100&&gc[i].pId!='\0';i++)
	{
		if(i!=0&&gc[i].startTime!=gc[i-1].endTime)
			printf("    -\t");
		else
			printf("    P%d\t",gc[i].pId);
		}
		printf("\n0");
		for(i=0;i<100&&gc[i].pId!='\0';i++)
			printf("\t%d",gc[i].endTime);
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



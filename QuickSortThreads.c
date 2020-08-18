#include<stdio.h>
#include<time.h>
#include<pthread.h>
#include<stdlib.h>
#define MAX 10000
int a[MAX];
int k;
int thread =0;
int lock=1;
int partition(int p, int r)
{
	int temp;	
	int x=a[r];
	int i = p-1;
	for(int j=p;j<r;j++)
	{
		if(a[j]<=x)
			{
				i++;
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}		
	}
	temp=a[i+1];
	a[i+1]= a[r];
	a[r]=temp;
	return i+1;
}

void qksort(int p, int q)
{
	
	int r;
	if(p<q)
		{
			r= partition(p,q);
			qksort(p,r-1);
			qksort(r+1,q);
		}
	
}

void *qsort123(void *arg)
{
	int *data = (int*)arg;	
	
	
	int p= data[0];
	int q= data[1];
	
	lock=0;
	qksort(p,q);
	
}

void main()
{
	int i;
	pthread_t thread[2];
	int data[2];
	clock_t start, end;
	double cpu_time_used;
	
	for(i=0;i<MAX;i++)
		a[i]=rand()%100;

	
	printf("\n");
	
	start = clock();
	k= partition(0, MAX-1);
	
	data[0]=0;
	data[1]=k-1;
	
	pthread_create(&thread[0], NULL, qsort123, (void*)data);
	while(lock);
	data[0]=k+1;
	data[1]=MAX-1;
	

	pthread_create(&thread[1], NULL, qsort123, (void*)data);

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	
	end = clock();

	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	/*for(i=0;i<MAX;i++)
		printf("%d ",a[i]);*/
	printf("\nwith threads: %f", cpu_time_used);

	
}

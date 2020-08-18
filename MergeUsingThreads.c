//gcc -pthread MergeUsingThreads.c
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

#define MAX 1000000
#define THREAD_MAX 8
int array[MAX];
int part=0;
void insertionSort(int a[], int n)
{
	int i,key,j;
	for(i=1;i<n;i++)
	{
		key=a[i];
		j=i-1;
		while(j>= 0 && a[j]>key)
		{
			a[j+1]=a[j];
			j=j-1;
		}
		a[j+1]=key;
	}
}

void merge(int a[], int low, int high1, int high2)
{
	int count=high2-low+1;
	int sorted[count];
	int i=low,k=high1+1,m=0;
	while(i<=high1 && k<=high2)
	{
		if(a[i]<a[k])
			sorted[m++]=a[i++];
		else if(a[k]<a[i])
			sorted[m++]=a[k++];
		else if(a[i]==a[k])
		{
			sorted[m++]=a[i++];
			sorted[m++]=a[k++];
		}
	}
	while (i<=high1)
		sorted[m++]=a[i++];
	while (k<=high2)
		sorted[m++]=a[k++];
	
	for(i=0;i<count;i++,low++)
		a[low]=sorted[i];
}

void mergeSort( int a[], int low, int high)
{
	int i, len=high-low+1;
	/*if(len<=5)
	{
		insertionSort(a,len);
		return;
	}*/
	//printf("%d,%d\n",low,high);
	if(low<high)
	{
		mergeSort(a,low,low+len/2-1);
		mergeSort(a,low+len/2,high);
		merge(a,low,low+len/2-1,high);
	}
}


void* merge_Sort(void* arg)
{
	int thread_part = part++;
	int low=thread_part*(MAX/THREAD_MAX);
	int high=(thread_part+1)*(MAX/THREAD_MAX)-1;
	if(low<high)
	{
		int mid=low+(high-low)/2;
		mergeSort(array,low,mid);
		mergeSort(array,mid+1,high);
		merge(array,low,mid,high);
	}
}

int main()
{
	int a[MAX];
	int i;
	for(i=0;i<MAX;i++)
	{
		a[i]=rand()%100;
		array[i]=a[i];
		//printf("%d ",array[i]);
	}
	
	clock_t t1,t2;
	t1=clock();
	pthread_t threads[THREAD_MAX];
	
	for(i=0;i<THREAD_MAX;i++)
		pthread_create(&threads[i],NULL,merge_Sort,(void*)NULL);
	
	for(i=0;i<THREAD_MAX;i++)
		pthread_join(threads[i],NULL);	
	
	merge(array,0,(MAX/2-1)/2,MAX/2-1);
	merge(array,MAX/2,MAX/2+(MAX-1-MAX/2)/2,MAX-1);
	merge(array,0,(MAX-1)/2,MAX-1);

	t2=clock();
	printf("\nTime Taken: %ld \n",t2-t1);
	
	for(i=0;i<MAX;i++)
		array[i]=a[i];	
	t1=clock();
	mergeSort( array, 0, MAX-1);
	t2=clock();
	
	printf("\nTime Taken: %ld \n",t2-t1);
	return 0;
	
}

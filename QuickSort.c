#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define N 1000000
int A[N];

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void initialize() {
	for (int i = 0; i < N; i++) {
		A[i]=rand()%100;
	}
}

int main()
{
	clock_t timeStamp1,timeStamp2,timeStamp3;
    timeStamp1=clock();
	initialize();
	timeStamp2=clock();
	printf("Time taken for initialization: %f seconds.\n",((double) (timeStamp2-timeStamp1)) / CLOCKS_PER_SEC);

	quickSort(A, 0, N-1);
  	timeStamp3=clock();
  	printf("Time taken for sorting: %f seconds.\n",((double) (timeStamp3-timeStamp2)) / CLOCKS_PER_SEC);

    return 0;
}

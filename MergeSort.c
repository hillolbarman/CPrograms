#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define N 1000000
int A[N];

// Merges two subarrays of arr[] First subarray is arr[l..m] Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i=0, j=0, k=l;
    int n1 = m - l + 1;
    int n2 =  r - m;

    int L[n1], R[n2]; //Temp arrays

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
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

	mergeSort(A, 0, N-1);
  	timeStamp3=clock();
  	printf("Time taken for sorting: %f seconds.\n",((double) (timeStamp3-timeStamp2)) / CLOCKS_PER_SEC);

    return 0;
}

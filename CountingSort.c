#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>

#define N 100
int A[N],B[N];
time_t tStart,tInitialization,tSorting;

void initialize() {
	for (int i = 0; i < N; i++) {
		A[i]=rand()%100;
	}
}

int getMax(int array[], int n)
{
  int max = array[0];
  for (int i = 1; i < n; i++)
    if (array[i] > max)
      max = array[i];
  return max;
}

void counting_sort(int A[], int n)
{
    int k = getMax(A,n);
    int i, j;
    int C[100];
    for (i = 0; i <= k; i++)
        C[i] = 0;
    for (j = 1; j <= n; j++)
        C[A[j]] = C[A[j]] + 1;
    for (i = 1; i <= k; i++)
        C[i] = C[i] + C[i-1];
    for (j = n; j >= 1; j--)
    {
        B[C[A[j]]] = A[j];
        C[A[j]] = C[A[j]] - 1;
    }
}

void printArray(int array[], int size)
{
  for (int i = 0; i < size; ++i){
    printf("%d  ", array[i]);
  }
  printf("\n");
}

int main() {

	tStart=time(NULL);
	initialize();
	tInitialization=time(NULL);
  printf("\nOriginal Array generated:-\n");
  printArray(A,N);
  printf("Time taken for initialization: %ld seconds.\n",tInitialization-tStart);

	counting_sort(A,N);
  tSorting=time(NULL);
  printf("\nSorted Array generated:-\n");
  printArray(B,N);
  printf("Time taken for sorting: %ld seconds.\n",tSorting-tInitialization);

	return 0;
}
/*
Original Array generated:-
7  49  73  58  30  72  44  78  23  9  40  65  92  42  87  3  27  29  40  12  3  69  9  57  60  33  99  78  16  35  97  26  12  67  10  33  79  49  79  21  67  72  93  36  85  45  28  91  94  57  1  53  8  44  68  90  24  96  30  3  22  66  49  24  1  53  77  8  28  33  98  81  35  13  65  14  63  36  25  69  15  94  29  1  17  95  5  4  51  98  88  23  5  82  52  66  16  37  38  44  
Time taken for initialization: 0 seconds.

Sorted Array generated:-
0  0  1  1  1  3  3  3  4  5  5  8  8  9  9  10  12  12  13  14  15  16  16  17  21  22  23  23  24  24  25  26  27  28  28  29  29  30  30  33  33  33  35  35  36  36  37  38  40  40  42  44  44  44  45  49  49  49  51  52  53  53  57  57  58  60  63  65  65  66  66  67  67  68  69  69  72  72  73  77  78  78  79  79  81  82  85  87  88  90  91  92  93  94  94  95  96  97  98  98  
Time taken for sorting: 1578932957 seconds.
*/
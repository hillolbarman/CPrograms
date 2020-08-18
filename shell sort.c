#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define N 100000
int A[N];

void initialize() {
	int i;
	for (i = 0; i < N; i++) {
		A[i]=rand()%100;
	}
}


int shellSort(int arr[], int n) 
{ 
  int gap,i,j;
     
    for (gap = n/2; gap > 0; gap /= 2) 
    { 
        
        for ( i = gap; i < n; i += 1) 
        { 
            
            int temp = arr[i]; 
                      
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) 
                arr[j] = arr[j - gap]; 
              
            arr[j] = temp; 
        } 
    } 
    return 0; 
} 
  
int main(int argc, char const *argv[]) 
{  
   
    clock_t t1,t2,t3,t4;
	double init_time,exec_time;
	t1 = clock();
	initialize();
  	t2 = clock();
	init_time = (double)(t2-t1)/CLOCKS_PER_SEC;
	t3 = clock();
	shellSort(A,N);
	t4 = clock();
	exec_time = (double)(t4-t3)/CLOCKS_PER_SEC;
     
	printf("Initialization time %.7f seconds\nExecution Time - %.7f seconds\n",init_time,exec_time); 
  
} 

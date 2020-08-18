#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>

#define N 100000
float A[N];
time_t tStart,tInitialization,tSorting;

void initialize() {
	for (int i = 0; i < N; i++) {
		A[i]=rand()%100;
	}
}

void bubbleSort(float a[N], int n) {
	bool updated=false;
	for(int i=0;i<n-1;i++) {
		for(int j=0;j<n-i-1;j++) {
			if(a[j]>a[j+1]) {
				float temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
				updated=true;
			}
		}
		if(!updated) break;
		updated=false;
	}
}

int main(int argc, char const *argv[]) {

	tStart=time(NULL);
	initialize();
	tInitialization=time(NULL);
	printf("Time taken for initialization: %ld seconds.\n",tInitialization-tStart);

	bubbleSort(A,N);
  	tSorting=time(NULL);
  	printf("Time taken for sorting: %ld seconds.\n",tSorting-tInitialization);

	return 0;
}

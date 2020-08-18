#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define N 100000
float A[N];
time_t tStart,tInitialization,tSorting;

void initialize() {
	for (int i = 0; i < N; i++) {
		A[i]=rand()%100;
	}
}

void oddEvenTransposition(float a[N], int n) {
	for(int i=0;i<n;i++) {
		if(i%2==0) {
			for(int j=0;j<n/2;j++) {
				if(a[2*j]>a[2*j+1]) {
					float temp=a[2*j];
					a[2*j]=a[2*j+1];
					a[2*j+1]=temp;
				}
			}
		}
		else {
			for(int j=1;j<n/2;j++) {
				if(a[2*j-1]>a[2*j]) {
					float temp=a[2*j-1];
					a[2*j-1]=a[2*j];
					a[2*j]=temp;
				}
			}
		}
	}
}

int main(int argc, char const *argv[]) {

	tStart=time(NULL);
	initialize();
	tInitialization=time(NULL);
	printf("Time taken for initialization: %ld seconds.\n",tInitialization-tStart);

	oddEvenTransposition(A,N);
  	tSorting=time(NULL);
  	printf("Time taken for sorting: %ld seconds.\n",tSorting-tInitialization);

	return 0;
}

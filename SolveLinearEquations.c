#include <stdio.h>
#include <stdlib.h>

#define N 1024

float A[N][N],U[N][N];
float Y[N],B[N];

void initialize() {
  //int i,j;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      A[i][j]=rand()%10;
    }
    B[i]=rand()%10;
  }
}

void swapColumn(float a[N][N], float y[N], int c, int n) {
  for (size_t i = c+1; i < n; i++)  {
    if (a[i][c]!=0.0) {
      for (size_t j = 0; j < n; j++) {
        float temp=a[j][c];
        a[j][c]=a[j][i];
        a[j][i]=temp;
      }
      float temp=y[i];
      y[i]=y[c];
      y[c]=temp;
      return;
    }
  }
}

void gaussinaElemination(float a[N][N], float u[N][N], float b[N], float y[N], int n) {
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      u[i][j]=a[i][j];
    }
    y[i]=b[i];
  }

  for (size_t k = 0; k < n; k++) {
    //Normalization of kth equation
    if (u[k][k]==0.0) {
      swapColumn(u,y,k,n);
    }
    for (size_t i = k+1; i < n; i++) {
      u[k][i]=u[k][i]/u[k][k];
    }
    y[k]=y[k]/u[k][k];
    u[k][k]=1.0;

    //Elimination
    for (size_t i = k+1; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        u[i][j]=u[i][j]-u[i][k]*u[k][j];
      }
      y[i]=y[i]-u[i][k]*y[k];
      u[i][k]=0.0;
    }
  }
}

void backSubstitute(float u[N][N], float y[N], int n) {
  for (int i = n-1; i >= 0; i--) {
    y[i]/=u[i][i];
    for (int j = i-1; j >= 0; j--) {
      y[j]=y[j]-u[j][i]*y[i];
    }
  }
}

void print_mat(float m[N][N]) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      printf("%f\t", m[i][j] );
    }
    printf("\n");
  }
  printf("\n");
}

void print_vec(float v[N]) {
  for (size_t i = 0; i < N; i++) {
      printf("%f\t", v[i]);
  }
  printf("\n\n");
}

int main(int argc, char const *argv[]) {
  initialize();
  print_mat(A);
  print_vec(B);

  gaussinaElemination(A,U,B,Y,N);

  backSubstitute(U,Y,N);
  print_vec(Y);
  return 0;
}

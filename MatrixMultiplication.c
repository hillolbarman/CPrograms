#include <stdio.h>
#include <stdlib.h>

#define N 1024

float A[N][N],B[N][N],C[N][N];
float V[N],Z[N];

void initialize() {
  //int i,j;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      A[i][j]=rand()%10;
      B[i][j]=rand()%10;
    }
    V[i]=rand()%10;
  }
}

void mat_vec(float m[N][N], float x[], float y[]) {
  //int i,j;
  for (size_t i = 0; i < N; i++) {
    y[i]=0.0;
    for (size_t j = 0; j < N; j++) {
      y[i]+=m[i][j]*x[j];
    }
  }
}

void mat_mat(float a[N][N], float b[N][N], float c[N][N]) {
  //int i,j,k;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      c[i][j]=0.0;
      for (size_t k = 0; k < N; k++) {
        c[i][j]+=a[i][k]*b[k][j];
      }
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
  print_mat(B);
  print_vec(V);

  mat_mat(A,B,C);
  print_mat(C);

  mat_vec(A,V,Z);
  print_vec(Z);
  return 0;
}

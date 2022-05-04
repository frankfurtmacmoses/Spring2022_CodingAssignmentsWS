
#include <stdio.h>   
#include <stdlib.h> 
#include <omp.h>
#include "2DArray.h" 
#include <iostream>
using namespace std;


// define sizes of matrices to be used

#define MM 100000000
#define NN 100000000
#define PP 100000000

double dabs(double d){return (d<0.0?d:(-d));}

// Default triple-nested loop for matrix-matrix multiplication
void matmult1(int m, int n, int p, double **A, double **B, double **C)   
{   
	int i, j, k; 

	for (i = 0; i < m; i++)   
		for (j = 0; j < n; j++){          
			C[i][j]=0; 
			for (k = 0; k < p; k++)   
				C[i][j] += A[i][k]*B[k][j]; 
				cout<<"\n Matrix A "<<A[i][k]; 
				cout<<"\n Matrix B "<<B[k][j];
				cout<<"\n Matrix C "<<C[i][j];

		}
	//Printing the matrix values 
	//printf(C[i][j]);  
	
} 

int main(int argc, char* argv[])   
{      
	int i, j; 
	double start, time1, time2;

   int M = MM;
   int N = NN;
   int P = PP;
 
//
// If 3 values on command line, use those for matrix sizes
//
   if (argc != 4) {
      printf("Suggested Usage: %s <M> <N> <P> \n", argv[0]);
      printf("Using default values\n");
   }
   else {
      M = atoi(argv[1]);
      N = atoi(argv[2]);
      P = atoi(argv[3]);
   }

	double  **A = Allocate2DArray< double >(M, P);
	double  **B = Allocate2DArray< double >(P, N);

	double **C1 = Allocate2DArray< double >(M, N);
	double **C4 = Allocate2DArray< double >(M, N);

//
// Initialize with random values
//
	for (i = 0; i < M; i++) {   
		for (j = 0; j < P; j++) {   
			A[i][j] = (double)(rand()%100) / 10.0;   
		}      
	}   

	for (i = 0; i < P; i++) {   
		for (j = 0; j < N; j++) {   
			B[i][j] = (double)(rand()%100) / 10.0;   
		}      
	}   

   printf("Matrix Dimensions: M = %d  P = %d  N = %d\n\n", M, P, N);
	printf("Execute matmult1\n");
	matmult1(M, N, P, A, B, C1);
	return 0;
}
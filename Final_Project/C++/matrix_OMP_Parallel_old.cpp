/* Compute matrix A multiplied by matrix B; the final outcome of is stored in C */

#include <stdio.h>   
#include <stdlib.h> 
#include <omp.h>
#include <iostream>
using namespace std;

#define N 100
#define P 100
#define M 100

int main(int argc, char *argv[]) 
{
    int tid, nthreads, i, j, k;
    double a[N][P], b[P][M], c[N][M];

/** Create a parallel region explicilty scoping all variables **/
#pragma omp parallel shared(a,b,c,nthreads) private(tid, i, j, k)
    {
        //tid = omp_get_thread_num();
        #pragma omp for
        for (i =0;i<N; i++)
            for(j=0; j<P; j++)
                a[i][j]=i+j;
        #pragma omp for
        for (i=0; i<P; i++)
            for(j=0;j<M; j++)
                b[i][j] = i*j;
        #pragma omp for 
        for (i=0;i<N; i++)
            for (j=0; j<M; j++)
            c[i][j]=0;   
   
            printf("Thread %d starting matrix multiply ...\n , tid");
            #pragma omp for 
            for (i=0; i<N; i++)
            {
                printf("Thread=%d did row=%d\n", i);
                for(j=0; j<M; j++)
                for (k=0;k<P; k++)
                c[i][j] += a[i][k] * b[k][j];
                cout<<"\n Matrix C "<<c[i][j];
            }
            cout<<"\n Matrix C "<<c[i][j];

    }
    cout<<"\n Matrix C "<<c[i][j];
}
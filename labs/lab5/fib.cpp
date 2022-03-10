#include <iostream>
#include <omp.h>

using namespace std;


int fib(int num)
{
	int x,y;
	if (num<2) return num;
#pragma omp task //task 1
	x = fib(num-1);
#pragma omp task //2
	y = fib(num-2);
#pragma omp taskwait
	return x+y;
}


int main()
{
	int N=30;
	#pragma omp parallel 
	{
	int f ;
	#pragma omp single
	{
		f = fib(N);
		cout << "Fibonacci number " << N << " is " << f << endl;
	}
	}
	
	return 0;
}



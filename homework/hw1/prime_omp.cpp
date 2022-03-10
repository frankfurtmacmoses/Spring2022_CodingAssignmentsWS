#include <iostream>
#include <cmath>
#include <omp.h>
void omp_set_num_threads (int num_threads);
using namespace std;

int validate(int n) {
  //#pragma omp for
    for(int i=2;i<= sqrt(n);i++) {
        if(n%i==0) {
            return 0;
        }  
    }
    return 1;
}

int main() {
    int begin = 2;
    int end = 50000000;
    int final_result = 0;

// if line 25 is uncommented, the number of threads will be determined by 
// the value of integer specified in the call to the method: omp_set_num_threads()

omp_set_num_threads(1);
int result = 0; int i;
#pragma omp parallel for reduction(+:final_result)
    for(int i=begin;i<end;i++) {
        if(validate(i) && validate(i+2)) {
           final_result +=  1;
        }
    }
    cout << final_result << endl;
}
#include <iostream>
#include <cmath>

using namespace std;

int validate(int n) {
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
    int result = 0;


    for(int i=begin;i<end;i++) {
        if(validate(i) && validate(i+2)) {
            result = result + 1;
        }
    }
    cout << result << endl;
}
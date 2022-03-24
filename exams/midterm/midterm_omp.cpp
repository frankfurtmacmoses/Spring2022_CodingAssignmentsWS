#include <iostream>
#include <omp.h>

using namespace std;

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

struct node {
   int data;
   int fibdata;
   struct node* next;
};

int fib(int n) {

   int x, y;
   if (n < 2) {
      return (n);
   } else {
    // #pragma omp task shared(x)
      x = fib(n - 1);
   //   #pragma omp task shared(y)
      y = fib(n - 2);
	  return (x + y);
   }
}

void processwork(struct node* p) 
{
   int n;
   n = p->data;
   p->fibdata = fib(n);
}

struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;
    
    head = new node;
    p = head;
    p->data = FS;
    p->fibdata = 0;
    #pragma omp parallel for schedule(dynamic,1500)
    for (i=0; i< N; i++) {
       temp  =  new node;
       p->next = temp;
       p = temp;
       p->data = FS + i + 1;
       p->fibdata = i+1;
    }
    
    p->next = NULL;
    return head;
}

int main(int argc, char *argv[]) {
     double start, end;
     struct node *p=NULL;
     struct node *temp=NULL;
     struct node *head=NULL;
     
     printf("Process linked list\n");
     printf("  Each linked list node will be processed by function 'processwork()'\n");
     printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n",N,FS);      
    #pragma omp parallel
    #pragma omp single
     p = init_list(p);
     head = p;
      
     start = omp_get_wtime();
     { 
        while (p != NULL) {
      #pragma omp task firstprivate(p)    
		   processwork(p); 
		   p = p->next;
        }
     }

     end = omp_get_wtime();
     p = head;
     while (p != NULL) {
       
        printf("%d : %d\n",p->data, p->fibdata);
        temp = p->next;
        delete p;
        p = temp;
     }  
     delete p;

     printf("Compute Time: %f seconds\n", end - start);

     return 0;
}


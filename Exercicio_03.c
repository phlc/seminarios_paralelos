#include<stdio.h>
#include<omp.h>

int main(){
  #pragma omp parallel
  for(int i = 1; i <= 4; i++)
    printf("I = %d -- %d\n", i, omp_get_thread_num());
}

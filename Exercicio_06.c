#include<stdio.h>
#include<omp.h>

void print1();
void print2();
void print3();

int main(){
   print1();
   printf("==============\n");
   print2();
   printf("==============\n");
   print3();
}

void print1(){
	int i;
	for(i = 0; i < 3; i ++)
		printf("I = %d\n", i);
}

void print2(){
	int i;
	#pragma omp parallel
	for(int i = 0; i < 3; i ++)
		printf("I = %d -- %d\n", i, omp_get_thread_num());
}

void print3(){
	int i;
	#pragma omp parallel for
      for(i = 0; i < 3; i ++)
		printf("I = %d -- %d\n", i, omp_get_thread_num());
}



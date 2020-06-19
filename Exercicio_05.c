#include<stdio.h>
#include<omp.h>

int main(){
	int i;
	#pragma omp parallel for num_threads(3)
	for(i = 0; i < 9; i++)
		printf("ID:%d, I: %d \n", omp_get_thread_num(), i);
}


#include<stdio.h>
#include<omp.h>

int main(){
	printf("Sequencial %d\n", omp_get_num_threads());
	#pragma omp parallel
	{
		printf("Paralela %d\n", omp_get_num_threads());
	}
	printf("Sequencial %d\n", omp_get_num_threads());
}


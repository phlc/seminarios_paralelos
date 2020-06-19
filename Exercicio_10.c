#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include<omp.h>

#define SIZE 10000

void matriz(int**, int);
void matriz2(int**, int);
void matriz3(int**, int);

int main(){
   int size = SIZE;
   int **m = malloc (SIZE * sizeof(int*));

   for (int i = 0; i < SIZE; ++i){
      m[i] = malloc (SIZE * sizeof(int));
   }

   matriz(m, size);
   matriz2(m, size);
   matriz3(m, size);
}


void matriz(int** mat, int size){
   int i, j;
   clock_t comeco = clock();
	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++){
			mat[i][j] = rand();
		   //printf("mat[%i][%i] (%i) <-- %i\n", i, j, omp_get_thread_num(), mat[i][j]);
      }

   double total = (clock() - comeco) / (double)CLOCKS_PER_SEC;
   printf("Tempo (seq): %f s.\n", total);
}


void matriz2(int **mat, int size){
   clock_t comeco = clock();
   int i, j;
	for(i = 0; i < size; i++){
      //printf("i(%i)>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n", i);
		#pragma omp parallel for
		for(j = 0; j < size; j++){
			mat[i][j] = rand();
		   //printf("mat2[%i][%i] (%i) <-- %i\n", i, j, omp_get_thread_num(), mat[i][j]);
      }
      //printf("i(%i)<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", i);
   }

   double total = (clock() - comeco) / (double)CLOCKS_PER_SEC;
   printf("Tempo (par1): %f s.\n", total);
}


void matriz3(int **mat, int size){
	int i, j;
   clock_t comeco = clock();
	#pragma omp parallel for private(j)
	for(i = 0; i < size; i++){
      //printf("i(%i)>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n", i);
		for(j = 0; j < size; j++){
			mat[i][j] = rand();
		   //printf("mat3[%i][%i] (%i) <-- %i\n", i, j, omp_get_thread_num(), mat[i][j]);
      }
      //printf("i(%i)<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", i);
   }

   double total = (clock() - comeco) / (double)CLOCKS_PER_SEC;
   printf("Tempo (par2): %f s.\n", total);
}

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

#define SIZE 10000

void matriz(int**, int);
void matriz4(int**, int);

int main(){
   int size = SIZE;
   int **m = malloc (SIZE * sizeof(int*));

   for (int i = 0; i < SIZE; ++i){
      m[i] = malloc (SIZE * sizeof(int));
   }

   matriz(m, size);
   matriz4(m, size);
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


void matriz4(int **mat, int size){
   
   omp_set_num_threads(4);
   clock_t comeco = clock();
	#pragma omp parallel
	{
		int size_local = size / omp_get_num_threads();
		int deslocamento = omp_get_thread_num()*size_local;
      int inicio = deslocamento;
      int fim = deslocamento + size_local;
		for(int i = inicio; i < fim; i++){
         //printf("i(%i)(%d)>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>(%d/%d)\n", i, omp_get_thread_num(), size_local, deslocamento);
			for(int j=0; j < size; j++){
				mat[i][j] = rand();
		      //printf("mat4[%i][%i] (%i) <-- %i\n", i, j, omp_get_thread_num(), mat[i][j]);
         }
         //printf("i(%i)<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", i);
      }
	}

   double total = (clock() - comeco) / (double)CLOCKS_PER_SEC;
   printf("Tempo (par4): %f s.\n", total);
}

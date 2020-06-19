#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

#define SIZE 20

void matriz(int**, int);
int atividadeSeq(int**, int, int);
int atividadePar(int**, int, int);
int atividadeParCrit(int**, int, int);

int main(){
   int size = SIZE;
   int **m = malloc (SIZE * sizeof(int*));

   for (int i = 0; i < SIZE; ++i){
      m[i] = malloc (SIZE * sizeof(int));
   }

   matriz(m, size);

   clock_t comeco = clock();
   int a = atividadeSeq(m, size, 1);
   double ta = (clock() - comeco) / (double)CLOCKS_PER_SEC;
   
   comeco = clock();
   int b = atividadePar(m, size, 1);
   double tb = (clock() - comeco) / (double)CLOCKS_PER_SEC;

   comeco = clock();
   int c = atividadeParCrit(m, size, 1);
   double tc = (clock() - comeco) / (double)CLOCKS_PER_SEC;	

   printf("Tempo Sequncial: %lf. Cont: %i\n", ta, a);
   printf("Tempo Paralelo : %lf. Cont: %i\n", tb, b);
   printf("Tempo Critical : %lf. Cont: %i\n", tc, c);

   printf("Speedup: %lf\n", ta/tb);
}


void matriz(int** mat, int size){
   int i, j;
	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++){
			mat[i][j] = 1;
      }
}


int atividadeSeq(int** mat, int size, int x){
	int i, j, cont;
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			if(mat[i][j]==x)
				cont++;
	return cont;
}

int atividadePar(int** mat, int size, int x){
	int i, j, cont;
	#pragma omp parallel for private(j)
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			if(mat[i][j]==x)
				cont++;
	return cont;
}

int atividadeParCrit(int** mat, int size, int x){
	int i, j, cont;
	#pragma omp parallel for private(j)
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			if(mat[i][j]==x)
				#pragma omp critical
				cont++;
	return cont;
}

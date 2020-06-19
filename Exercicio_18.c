#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#include<string.h>

#define SIZE   100
#define bool   int
#define true   1
#define false  0

void swap(int a[], int i, int j){
      int temp = a[i];
      a[i] = a[j];
      a[j] = temp;
}

void quickSortSeq(int vet[], int esq, int dir){
   int i = esq;
   int j = dir;
   int pivo = vet[(i+j)/2];

   while(i<=j){
      while(vet[i]<pivo){
         i++;
      }
      while(vet[j]>pivo){
         j--;
      }
      if(i<=j){
         swap(vet, i, j);
         i++; j--;
      }
   }
   if(esq<j){
      quickSortSeq(vet, esq, j);
   }
   if(i<dir){
      quickSortSeq(vet, i, dir);
   }
}

void quickSortPar(int vet[], int esq, int dir){
   int i = esq;
   int j = dir;
   int pivo = vet[(i+j)/2];

   while(i<=j){
      while(vet[i]<pivo){
         i++;
      }
      while(vet[j]>pivo){
         j--;
      }
      if(i<=j){
         swap(vet, i, j);
         i++; j--;
      }
   }
   omp_set_num_threads(2);
   #pragma omp parallel sections
   {
      #pragma omp section
      if(esq<j){
         quickSortPar(vet, esq, j);
      }
      #pragma omp section
      if(i<dir){
         quickSortPar(vet, i, dir);
      }
   }
}

void mostrar(int a[], int size){
   printf("%s", "[ ");
   for(int i=0; i<size; i++){
      printf("%i ", a[i]);
   }
   printf("%s\n", "]");
}

int main(){
   int arr1[SIZE];
   int arr2[SIZE];

   for (int i=0; i<SIZE; i++){
      arr1[i] = arr2[i] = rand()%100;
   }
  
   mostrar(arr1, SIZE);
   mostrar(arr2, SIZE);

   clock_t comeco = clock();
   quickSortSeq(arr1, 0, SIZE-1);
   double totala = (clock() - comeco) / (double)CLOCKS_PER_SEC; 

   comeco = clock();
   quickSortPar(arr2, 0, SIZE-1);
   double totalb = (clock() - comeco) / (double)CLOCKS_PER_SEC;

   mostrar(arr1, SIZE);
   mostrar(arr2, SIZE);

   printf("Tempo (seq): %lf\n", totala);
   printf("Tempo (par): %lf\n", totalb);
   printf("Speedup: %lf\n", totala/totalb);

   if(0<totala/totalb)
      printf("%s\n", "Algoritmo Paralelo Nao Eficiente");
   else
      printf("Eficiencia: %lf%\n", (totala/totalb)/2);

}

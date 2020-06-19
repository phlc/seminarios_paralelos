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

void oddEvenSortSeq(int a[], int size){
   for(int i=0; i<size; i++){
      if(i%2==1)
         for(int j=1; j<size-1; j+=2){
            if(a[j] > a[j+1])
               swap(a, j, j+1);
         }
      else
         for(int j=0; j<size-1; j+=2){
            if(a[j]>a[j+1])
               swap(a, j, j+1);
         }
   }
}


void oddEvenSortPar(int a[], int size){
   omp_set_num_threads(4);
   for(int i=0; i<size; i++){
      if(i%2==1)
         #pragma omp parallel for
         for(int j=1; j<size-1; j+=2){
            if(a[j] > a[j+1])
               swap(a, j, j+1);
         }
      else
         #pragma omp parallel for
         for(int j=0; j<size-1; j+=2){
            if(a[j]>a[j+1])
               swap(a, j, j+1);
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
      arr1[i] = arr2[i] = SIZE-i;
   }
  
   mostrar(arr1, SIZE);
   mostrar(arr2, SIZE);

   clock_t comeco = clock();
   oddEvenSortSeq(arr1, SIZE);
   double totala = (clock() - comeco) / (double)CLOCKS_PER_SEC; 

   comeco = clock();
   oddEvenSortPar(arr2, SIZE);
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

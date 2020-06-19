#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#include<string.h>

#define SIZE   50000
#define bool   int
#define true   1
#define false  0

bool compareTo(char* s1, char* s2){
   bool resp = true, sair = false;

   for(int i = 0; sair == false; i++){
      if(s1[i] == '\0'){
         sair = true;
         resp = (s2[i] == '\0');
      } else if(s1[i] != s2[i]){
         sair = true;
         resp = false;
      }
   }

   return resp;
}

int main(){
   int size;
   int soma = 0;
   char **vet = malloc (SIZE * sizeof(char*));
   char* str = (char*) malloc(100 * sizeof(char));
   strcpy(str, "Página");

   for (int i = 0; i < SIZE; ++i){
      vet[i] = malloc (100 * sizeof(char));
   }

   while(size < SIZE && strcmp(vet[size++], "</html>")){
      scanf("%s", vet[size]);
 //     printf("(%i): %s\n", size, vet[size]);
   }


   clock_t comeco = clock();

	for(int i = 0; i < size; i++){
      if(compareTo(vet[i], str)){
         soma++;
      }
   }

   double totala = (clock() - comeco) / (double)CLOCKS_PER_SEC;
   printf("Tempo (seq): %f s e encontrei(%d).\n", totala, soma);

   soma = 0;

   omp_set_num_threads(2);
   comeco = clock();

	#pragma omp parallel for reduction(+:soma) 
	for(int i = 0; i < size; i++){
        	 if(compareTo(vet[i], str)){
			soma++;
         	}
      	}

   double totalb = (clock() - comeco) / (double)CLOCKS_PER_SEC;
   printf("Tempo (par): %f s e encontrei(%d).\n", totalb, soma);
   printf("Speedup: %lf\n", totala/totalb);

}

/*
Autor: Frederico Gomes e Lucas Marques
Versao: 0.14
*/

#include <stdio.h>
#include <pthread.h>

//variaveis globais
int i, j, k, **m1, **m2, **m3;

//struct necessario para "troca de mensagens" entre os processos
struct  Data {
	int tam;
	int max;
	int min;
};

//aloca a matriz
int **aloca(int tam){
   int **matriz, i;
   matriz = calloc(tam, sizeof (int *));
   
   for(i=0; i< tam; i++){
      matriz[i] = calloc(tam, sizeof(int *));
   }
   printf("alocado\n");   
   return(matriz);
}

//preenche matriz
int **preenche(int **m, int tam){
   int i, j;
   for(i =0; i < tam; i++){
      for(j =0; j < tam; j++){
           m[i][j] = tam;      
      }
   }
   return(m);
}

//multiplica a matriz, o argumento a ser passado é a struct Data
void **Multiplica(void *arg){
	struct Data *d;
	d = (struct Data*)arg;

   	int i, j;
	for(i = 0; i < d->tam; i++){
		for(j = d->min; j < d->max; j++){
			m3[i][j] = 0;
			for(k=0; k < d->tam; k++){
			 m3[i][j] = m3[i][j]+ (m1[i][k] * m2[k][j]);
			}
	      	}
   	}
}

//lista a matriz de acordo com o tamanho
void **listar(int **m, int tam){
   int i, j;
   for(i =0; i < tam; i++){
    printf(" ");
      for(j =0; j < tam; j++){
           printf("%d\t", m[i][j]);      
      }
      printf("\n");
   }
}

int main(int argc, char const *argv[]){

	int NThreads;
	int tam, min, max;
	tam = atoi(argv[1]);
	NThreads = atoi(argv[2]);
	pthread_t  tid;

	m1 = aloca(tam);
	m2 = aloca(tam);
	m3 = aloca(tam);

	m1 = preenche(m1, tam);
 	m2 = preenche(m2, tam);

  //cria a struct Data	
	struct Data d;
	d.tam = tam;
	
	int num = tam /NThreads;

	for(i = 0; i < NThreads; ++i){
		d.min = i * num;
		d.max = num * (i+1);    		
		//cria a thread e passa o metodo multiplica e como argumento a struct Data
		pthread_create(&tid, NULL, Multiplica, (void *)&d);
  	pthread_join(tid,NULL);
	}
	
	return 0;

	free(m1);
	free(m2);
	free(m3);
}

/*
Autor: Frederico Gomes e Lucas Marques
Versao: 0.14
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>


//prototipos das funcoes

//Aloca a matriz de acordo com o tamanho passado
int **aloca(int tam);

//Preenche uma matriz de acordo com o tamanho
int **preenche(int **m, int tam);

//Lista uma matriz de acordo com o tamanho
void listar(int **m, int tam);

//Multiplica a 3º matriz de acordo com o tamanho e o numero de processos
void multiplica(int **m1, int **m2, int **m3, int tam, int nthreads);

main(int argc, char *argv[]){

	int TAMMATRIZ = atoi(argv[1]);
	int NPROCESSOS = atoi(argv[2]);

	if(TAMMATRIZ < NPROCESSOS){
		printf("TAM MATRIZ < NUM PROCESSOS nao e valido\n");
		exit(0);
	}

  //declara as matrizes
	int **m1, **m2, **m3;
	
	//aloca as matrizes
	m1 = aloca(TAMMATRIZ);
	m2 = aloca(TAMMATRIZ);
	m3 = aloca(TAMMATRIZ);

	//preenche
	m1 = preenche(m1, TAMMATRIZ);
	m2 = preenche(m2, TAMMATRIZ);

	//multiplica
	multiplica(m1, m2, m3, TAMMATRIZ, NPROCESSOS);
}

//aloca uma matriz de acordo com o tamanho (tam)
int **aloca(int tam){
	int **m, i;
	m = calloc(tam, sizeof(int *));
	for (i = 0; i < tam; i++)
		m[i] = calloc(tam, sizeof(int *));
	return (m);
}

//preeche uma matriz (m) de tamanho (tam) com os valores iguais a (tam)
int **preenche(int **m, int tam){
	int i, j;
	for(i = 0; i < tam; i++)
		for (j = 0; j < tam; j++)
			m[i][j] = tam;
	return (m);
}

//lista uma matriz (m)
void listar(int **m, int tam){
	int i, j;
	for (i = 0; i < tam; i++){
		for (j = 0; j < tam; j++)
			printf("%d \t",m[i][j]);
		printf("\n");
	}
	printf("\n");
}

//executa a multiplicacao
void multiplica(int **m1, int **m2, int **m3, int tam, int nthreads){

	//declara o valor (min) e (max) que devem ser percorridos na multiplicacao
	int min, *max, i, l, c; 	

	//coloca na memoria compartilhada as variaveis (max e m3)
	int mrId = shmget(IPC_PRIVATE, 1000, 0600);
	for(i =0; i <tam; i++)
		m3[i] = shmat(mrId, NULL, NULL);
	int maxId = shmget(IPC_PRIVATE, sizeof(int), 0600);
	max = shmat(maxId, NULL, NULL);

	int num = tam /nthreads;
	int resto = tam % nthreads;

	if(nthreads == tam || nthreads < tam){
		//para i < numero de processos a serem feitos
		for (l = 0; l < nthreads; l++)
		{
			//cria um novo processo
			int thread = fork();
			if (thread == 0)
			{
				min = l * num;
				*max = num * (l+1);

				//calculo da multiplicacao de matriz
				for(c = min; c < *max; c++)
					for (i = 0; i < tam; i++)
						m3[l][c] = m3[l][c] + (m1[l][i] * m2[i][c]);
	
				exit(1);
			}
		}
		if(resto != 0)
			for(c = *max; c < tam; c++)
				for (i = 0; i < tam; i++)
					m3[l][c] = m3[l][c] + (m1[l][i] * m2[i][c]);

		for(l = 0; l < nthreads; l++)
			wait(NULL);
	}
}

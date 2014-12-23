

//basicamente este trabalho temos de criar 3 funçoes 
// 1. uma para o algoritmo de pesquisa local, neste caso eu sugeria em escolhermos o trepa-colinas
// 2. algoritmo evolutivo, isto ainda nao sei o que é
// 3. metodo hibrido que segundo o que aqui diz serve para combinar as abordagens anteriores


// isto ainda está uma confusao, mas o algoritmo do trepa colinas é mais ou menos isto
// isto foi retirado da aula em que fizemos experiencia com o trepa colinas



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "utils.h"

#define DEFAULT_RUNS 10

int main(int argc, char *argv[])
{
    char nome_fich[100];
    int *grafo, *sol, *best;
    int vert, num_iter, i, k, runs, custo, best_custo;
	float mbf = 0.0;
        
	if(argc == 3)
	{
		runs = atoi(argv[2]);
		strcpy(nome_fich, argv[1]);
	}
	else if(argc == 2)
	{
		runs = DEFAULT_RUNS;
        strcpy(nome_fich, argv[1]);
    }
	else
    {
		runs = DEFAULT_RUNS;
        printf("Nome do Ficheiro: ");
        gets(nome_fich);
    }
  
	if(runs <= 0)
		return 0;
	
	init_rand();
	
    // Preenche matriz de adjacencias 
    grafo = init_dados(nome_fich, &vert, &num_iter);
  	
	sol = (int)malloc(sizeof(int)*vert);
	best = (int)malloc(sizeof(int)*vert);
	
	if(sol == NULL || best == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}
	
	for(k=0; k<runs; k++)
	{
		// Gerar solucao inicial
		gera_sol_inicial(sol, vert);
    
		// Trepa colinas
		custo = trepa_colinas(sol, grafo, vert, num_iter);
    
		// Escreve resultados da repeticao k
		printf("\nRepeticao %d:", k);
		escreve_sol(sol, vert);
		printf("Custo final: %2d\n", custo);    
		
		mbf += custo;
		if(k==0 || best_custo > custo)
		{
			best_custo = custo;
			substitui(best, sol, vert);
		}
    } 
	
	// Escreve eresultados globais
	printf("\n\nMBF: %f\n", mbf/k);
	printf("\nMelhor solucao encontrada");
	escreve_sol(best, vert);
	printf("Custo final: %2d\n", best_custo);    
	
	free(grafo);
    free(sol);    
	free(best);
    return 0;    
}



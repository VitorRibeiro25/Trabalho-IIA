#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "utils.h"

using namespace std;

// Leitura do ficheiro de input
// Recebe: nome do ficheiro, numero de vertices (ptr), numero de iteracoes (ptr)
// Devolve a matriz de adjacencias
int** init_dados(char *nome, int *n, int *iter)
{
	int **p;
	int i, j, l, contador = 0;
	int dim_x, dim_y;
	string fn(nome), temp;

	ifstream myfile;
	myfile.open(fn);

	if(myfile.is_open()){
		getline(myfile, temp);
		istringstream string_a_separar(temp);
		string_a_separar >> temp;
		dim_x = stoi(temp, nullptr);
		string_a_separar >> temp;
		dim_y = stoi(temp, nullptr);
		cout << "Dimensoes da matriz " << dim_x << " " << dim_y << endl;

		for (int a = 0; a < 3; a++){
			getline(myfile, temp);
		}

		p = new int*[dim_y];
		for (l = 0; l < dim_y; l++)
			p[l] = new int[dim_x];

		for (i = 0; i < dim_x; i++){
			for (j = 0; j < dim_y; j++){
				p[i][j] = 0;
			}
		}
		myfile.close();
	}

	

	// Preenchimento da matriz
	do{
		int int_temp;
		string temp2;
		streamoff linha_actual;
		contador++;

		myfile.open(fn);
		getline(myfile, temp);
		myfile.clear();
		linha_actual = myfile.tellg();

		if (contador % 2 != 0){
			int_temp = stoi(temp, nullptr);
			cout << "Linha " << contador << " com " << int_temp << " elementos" << endl;
			
			//getline(myfile, temp2);
			istringstream sstream(temp2);

			do
			{
				string sub;
				sstream >> sub;
			} while (sstream);
		}

	} while (getline(myfile, temp));
	

	myfile.close();
	return p;
}



// Gera a solucao inicial
// Parametros: solucao, numero de vertices
void gera_sol_inicial(int *sol, int v)
{
	int i, x;
	
	for(i=0; i<v; i++)
	 sol[i]=0;
	 
	for(i=0; i<v/2; i++)
    {
        do
			x = random_l_h(0, v-1);
        while(sol[x] != 0);
        sol[x]=1;
    }	
}

// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_sol(int *sol, int vert)
{
	int i;
	
	printf("\nConjunto A: ");
	for(i=0; i<vert; i++)
		if(sol[i]==0)
			printf("%2d  ", i);
	printf("\nConjunto B: ");
	for(i=0; i<vert; i++)
		if(sol[i]==1)
			printf("%2d  ", i);
	printf("\n");
}


// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i]=b[i];
}


// Inicializa o gerador de numeros aleatorios
void init_rand()
{
	srand((unsigned)time(NULL));
}


// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max-min+1);
}


// Devolve um valor real aleatorio do intervalo [0, 1]  
float rand_01()
{
	return ((float)rand())/RAND_MAX;
}


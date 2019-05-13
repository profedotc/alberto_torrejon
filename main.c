#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define X 10
#define Y 10

void gol_init(int ini[X][Y]);
void gol_print(int ini[X][Y]);
void gol_step(int ini[X][Y],int fin[X][Y]);
int gol_count_neighbors(int ini[X][Y],int i,int j);
bool gol_get_cell(int ini[X][Y],int i,int j);
void gol_copy(int ini[X][Y],int fin[X][Y]);

int main(){
	int i = 0;
	// Declara dos mundos
	int ini[X][Y];
	int fin[X][Y];

	// Inicializa el mundo
	gol_init(ini);
	
	do {
		printf("\033cIteration %d\n", i++);
		// Imprime el mundo
		gol_print(ini);
		// Itera
		gol_step(ini,fin);
		
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}

void gol_init(int ini[X][Y]){
	// Poner el mundo a false
	int	i,j;
	for (i=0; i<X; i++) 
		for (j=0; j<Y; j++) 
			ini[i][j] = 0;
	// Inicializar con un patrón
	ini[5][5]=1;
	ini[5][6]=1;
	ini[5][7]=1;
}

void gol_print(int ini[X][Y]){
	// Imprimir el mundo por consola
	int	i,j;
	for (i=0;i<X;i++){
		for (j=0; j<Y; j++){
			printf("%c",ini[i][j]?'x':' ');
		}
		printf("\n");
	}
}

void gol_step(int ini[X][Y],int fin[X][Y]){
	int	i,j;
	for (i=1;i<X-1;i++){
		for (j=1;j<Y-1;j++){
		fin[i][j]=gol_get_cell(ini,i,j);
	}}
	gol_copy(ini,fin);
}

int gol_count_neighbors(int ini[X][Y],int i,int j){
	// Devuelve el número de vecinos
	int contador = -ini[i][j];
	for (int k = i-1; k < i+2; k++)
	{
		for (int l = j-1; l < j+2; l++)
		{
			contador += ini[k][l];
		}
		
	}
	return contador;
}

bool gol_get_cell(int ini[X][Y],int i,int j){
	switch (gol_count_neighbors(ini, i, j))
	{
	case 2: return ini[i][j];
	case 3: return 1;
	default: return 0;
	}
}

void gol_copy(int ini[X][Y],int fin[X][Y]){
	// Copia el mundo segundo mundo sobre el primero
	int	i,j;
	for (i=1;i<X-1;i++){
		for (j=1;j<Y-1;j++){
			ini[i][j]=fin[i][j];
	}}
}
